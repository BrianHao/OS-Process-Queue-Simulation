//
//  FrameTable.hpp
//  AethyrOS.cpp
//
//  Created by Brian Hao on 11/20/17.
//  CSCI340
//  Prof Shostak
//  Operating Systems Project
//  Copyright © 2017 Brian Hao. All rights reserved.
//
// The FrameTable manages Frames, held by a vector of Frame Pointers
// This vector size is determined by (Memory Size / Page Size) provided
// by the user at the start of program execution, and will not change.
//

#ifndef FrameTable_hpp
#define FrameTable_hpp

#include <memory>
#include <vector>
#include "Frame.hpp"
using namespace std;

class FrameTable {
public:
    FrameTable() {};
    
    // Initialize Frame Table with null pointers
    void initialize(unsigned int tableSize) {
        for (unsigned int i = 0; i < tableSize; i++) {
            tableVec.push_back(nullptr);
        }
    };
    
    // Add a Frame to the Frame Table
    void addFrame(shared_ptr<Frame> inFrame);
    
    // Clear all Frames from a given Process ID, used when terminating a process
    void clearFramesByPid(unsigned int pid);
    
    // Returns if Frame Table contains all Frames
    bool isFull();
    
    // Returns if Frame Table contains no Frames
    bool isEmpty();
    
    // If the Frame with the given PageNum and PID exists, return the position, if not, return -1
    int contains(unsigned int inPageNum, unsigned int inPid);
    
    // Returns Frame at given position
    shared_ptr<Frame> at(unsigned int pos) { return tableVec.at(pos); };
    
private:
    // Vector container for Frame pointers
    vector<shared_ptr<Frame>> tableVec;
    
    // Returns the position of the Frame that's Least Recently Used
    unsigned int findLRU();
    
};

#endif /* FrameTable_hpp */
