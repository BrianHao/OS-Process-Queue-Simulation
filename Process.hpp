//
//  Process.hpp
//
//  Created by Brian Hao on 11/4/17.
//  CSCI340
//  Prof Shostak
//  Operating Systems Project
//  Copyright © 2017 Brian Hao. All rights reserved.
//
//  An individual process. Each process has its own parameters such as
//  Process ID and Priority.
//

#ifndef Process_hpp
#define Process_hpp

#include <iostream>
#include <string>
using namespace std;

class Process {
public:
    Process(unsigned int inPid, unsigned int inPriority) { pid = inPid; priority = inPriority; };
    
    // Getters and Setters
    unsigned int getPid() { return pid; };
    unsigned int getPriority() { return priority; };
    string getAccessedFile() { return accessedFile; };
    void setAccessedFile(string inFile) { accessedFile = inFile; };
    
private:
    // Process Parameters
    unsigned int pid = 0;
    unsigned int priority = 0;
    string accessedFile = "";
};

#endif /* Process_hpp */
