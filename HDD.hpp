//
//  HDD.hpp
//
//  Created by Brian Hao on 11/6/17.
//  CSCI340
//  Prof Shostak
//  Operating Systems Project
//  Copyright © 2017 Brian Hao. All rights reserved.
//
//  A single Hard Disk Drive. Has its own IO Queue.
//

#ifndef HDD_hpp
#define HDD_hpp

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include "Process.hpp"
using namespace std;

class HDD {
public:
    HDD() {};
    
    // Adds a process to this HDD's IO Queue
    void addProcessToIOQueue(shared_ptr<Process> inProcess) { ioQueue.push_back(inProcess); };
    
    // Removes a process from this HDD's IO Queue
    shared_ptr<Process> dequeue() {
        shared_ptr<Process> temp = ioQueue.front();
        ioQueue.erase(ioQueue.begin());
        return temp;
    };
    
    // Get HDD Information
    unsigned int size() { return ioQueue.size(); };
    shared_ptr<Process> at(unsigned int pos) { return ioQueue.at(pos); };
    bool empty() { return ioQueue.empty(); };
    
private:
    // Vector container for Process pointers
    vector<shared_ptr<Process>> ioQueue;
};

#endif /* HDD_hpp */
