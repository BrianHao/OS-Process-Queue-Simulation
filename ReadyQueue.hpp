//
//  ReadyQueue.hpp
//
//  Created by Brian Hao on 11/7/17.
//  CSCI340
//  Prof Shostak
//  Operating Systems Project
//  Copyright © 2017 Brian Hao. All rights reserved.
//
//  A Ready Queue is a wrapper for a vector of Process pointers
//  that manages sortedness during insertion by their priority.
//
//  We assume that the first item in the queue (position 0) is
//  currently using CPU time.
//

#ifndef ReadyQueue_hpp
#define ReadyQueue_hpp

#include <iostream>
#include <vector>
#include <memory>
#include "Process.hpp"
using namespace std;

class ReadyQueue {
public:
    ReadyQueue() {};
    
    // Add a new process to Ready Queue
    void add(shared_ptr<Process> inProcess);
    
    // Removes the Process in the front of the queue (currently using CPU)
    shared_ptr<Process> popFront();
    
    // Returns emptiness of Ready Queue
    bool empty() { return vec.empty(); };
    
    // Returns size of Ready Queue
    unsigned int size() { return (unsigned int) vec.size(); };
    
    // Returns Process at position given
    shared_ptr<Process> at(unsigned int pos) { return vec.at(pos); };
    
    // Returns whether Ready Queue currently contains a process with the given priority
    bool contains(unsigned int priority);
    
private:
    // Vector container for Process pointers
    vector<shared_ptr<Process>> vec;
};

#endif /* ReadyQueue_hpp */
