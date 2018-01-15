//
//  ReadyQueue.cpp
//
//  Created by Brian Hao on 11/7/17.
//  CSCI340
//  Prof Shostak
//  Operating Systems Project
//  Copyright © 2017 Brian Hao. All rights reserved.
//
//

#include "ReadyQueue.hpp"

void ReadyQueue::add(shared_ptr<Process> inProcess) {
    // Temp Process for swapping
    shared_ptr<Process> temp;
    
    // Adds the Process to the end of the Ready Queue
    vec.push_back(inProcess);
    
    // If it's the only process in the queue, return
    if (vec.size() == 1) {
        return;
    }
    
    // Else, place it in the correct position in the queue
    for (unsigned int i = vec.size()-1; i > 0; i--) {
        if (vec.at(i)->getPriority() > vec.at(i-1)->getPriority()) {
            temp = vec.at(i);
            vec.at(i) = vec.at(i-1);
            vec.at(i-1) = temp;
        }
    }
}

shared_ptr<Process>  ReadyQueue::popFront() {
    // Saves Process at front of queue
    shared_ptr<Process> firstProcess = vec.at(0);
    
    // Removes the saved front Process, moves the remaining processes up
    if (vec.size() == 1) {
        vec.pop_back();
    } else {
        for (unsigned int i = 0; i < vec.size()-1; i++) {
            vec.at(i) = vec.at(i+1);
        }
        vec.pop_back();
    }
    
    
    // Returns formerly saved front process
    return firstProcess;
}

bool ReadyQueue::contains(unsigned int priority) {
    bool contains = false;
    
    // Checks if Ready Queue contains a process with the given priority
    for (unsigned int i = 0; i < vec.size(); i++) {
        if (priority == vec.at(i)->getPriority()) {
            contains = true;
            break;
        }
    }
    
    return contains;
}
