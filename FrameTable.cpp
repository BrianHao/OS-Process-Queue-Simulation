//
//  FrameTable.cpp
//  AethyrOS.cpp
//
//  Created by Brian Hao on 11/20/17.
//  CSCI340
//  Prof Shostak
//  Operating Systems Project
//  Copyright © 2017 Brian Hao. All rights reserved.
//
//

#include "FrameTable.hpp"
using namespace std;

// Add a Frame to the Frame Table
void FrameTable::addFrame(shared_ptr<Frame> inFrame) {
    // If there is an empty slot in the Frame Table (not full), insert the Frame in the first empty position
    if (!isFull()) {
        for (unsigned int i = 0; i < tableVec.size(); i++) {
            if (tableVec.at(i) == nullptr) {
                tableVec.at(i) = inFrame;
                break;
            }
        }
    // If the Frame Table is full, find the LRU Frame and "Swap" it
    } else {
        unsigned int posLRU = findLRU();
        tableVec.at(posLRU) = inFrame;
    }
}

// Clear all Frames from a given Process ID, used when terminating a process
void FrameTable::clearFramesByPid(unsigned int pid) {
    for (unsigned int i = 0; i < tableVec.size(); i++) {
	if (tableVec.at(i) != nullptr) {
       		if (tableVec.at(i)->getPid() == pid) {
            	tableVec.at(i) = nullptr;
        	}
	}
    }
}

bool FrameTable::isFull() {
    bool full = true;
    
    for (unsigned int i = 0; i < tableVec.size(); i++) {
        if (tableVec.at(i) == nullptr) {
            full = false;
            break;
        }
    }
    return full;
}

bool FrameTable::isEmpty() {
    bool empty = true;
    
    for (unsigned int i = 0; i < tableVec.size(); i++) {
        if (tableVec.at(i) != nullptr) {
            empty = false;
            break;
        }
    }
    return empty;
}

int FrameTable::contains(unsigned int inPageNum, unsigned int inPid) {
    int pos = -1;
    
    for (unsigned int i = 0; i < tableVec.size(); i++) {
	if (tableVec.at(i) != nullptr) {
        	if ((tableVec.at(i)->getPageNum() == inPageNum) && (tableVec.at(i)->getPid() == inPid)) {
            	pos = i;
            	break;
        	}
	}
    }
    
    return pos;
}

unsigned int FrameTable::findLRU() {
    unsigned int lowestTime = tableVec.at(0)->getTimestamp();
    unsigned int posLRU = 0;
    
    if (tableVec.size() > 1) {
        for (unsigned int i = 0; i < tableVec.size(); i++) {
            if (tableVec.at(i)->getTimestamp() < lowestTime) {
                lowestTime = tableVec.at(i)->getTimestamp();
                posLRU = i;
            }
        }
    }
    return posLRU;
}
