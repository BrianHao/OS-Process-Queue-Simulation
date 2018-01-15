//
//  OS.hpp
//
//  Created by Brian Hao on 11/4/17.
//  CSCI340
//  Prof Shostak
//  Operating Systems Project
//  Copyright © 2017 Brian Hao. All rights reserved.
//
//  Main OS program. Manages all command inputs from user, as well as
//  manages IO Devices, and Ready Queue.
//

#ifndef OS_hpp
#define OS_hpp

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <memory>
#include "Process.hpp"
#include "HDD.hpp"
#include "ReadyQueue.hpp"
#include "FrameTable.hpp"
#include "Frame.hpp"
using namespace std;

class OS {
public:
    OS(unsigned int inMemorySize, unsigned int inPageSize, unsigned int inNumHardDisks) {
        memorySize = inMemorySize; pageSize = inPageSize; numHardDisks = inNumHardDisks; numFrames = inMemorySize / inPageSize; };
    
    // Starts running the Operating System
    // Continually gets input from the user
    void run();
    
private:
    // Operating System Parameters
    unsigned int memorySize = 1;
    unsigned int pageSize = 1;
    unsigned int numHardDisks = 1;
    unsigned int pidCounter = 1;
    unsigned int numFrames = 1;
    unsigned int timestamp = 1;
    // Holds list of IO Devices (In this case, HDDs)
    vector<shared_ptr<HDD>> ioDevices;
    // Ready Queue to hold processes
    ReadyQueue readyQueue;
    // Frame Table to manage memory
    FrameTable frameTable;
    
    // Gets input from user, converts it into a vector command, and executes it
    string getLine();
    vector<string> getCommand();
    void execute(vector<string> inCommand);
    
    // Command Execution Functions
    void addProcess(unsigned int pid, unsigned int priority);
    void terminateProcess();
    void hddAccessFile(unsigned int hddNumber, string fileName);
    void hddCompleteTask(unsigned int hddNumber);
    void memoryAccess(unsigned int memAddress);
    void snapshot(char sMode);
    
    // Helper Functions
    vector<string> stringToVector(string inString);
};

#endif /* OS_hpp */
