//
//  OS.cpp
//
//  Created by Brian Hao on 11/4/17.
//  CSCI340
//  Prof Shostak
//  Operating Systems Project
//  Copyright © 2017 Brian Hao. All rights reserved.
//
//

#include "OS.hpp"
using namespace std;

// Starts running the Operating System
// Continually gets input from the user
void OS::run() {
    vector<string> command;
    
    cout << "\nStarting Operating System with the following parameters:\n" <<
    "Memory Size: " << memorySize << " Bytes\n" <<
    "Page Size: " << pageSize << " Bytes\n" <<
    "I/O Devices: " << numHardDisks << " Hard Disk Drive(s)\n" <<
    "Frame Table contains: " << numFrames << " Frames\n";
    
    // Creates Hard Disk Drives for OS
    for (unsigned int i = 0; i < numHardDisks; i++) {
        shared_ptr<HDD> newHDD(new HDD);
        ioDevices.push_back(newHDD);
    }
    
    // Initialize Frame Table with proper number of Frames
    frameTable.initialize(numFrames);
    
    // Endlessly get a user command
    while(true) {
        cout << "\nPlease enter a command:\n";
        command = getCommand();
        
        // If command is x or X, shut down OS
        if (command.at(0).at(0) == 'x' || command.at(0).at(0) == 'X') {
            cout << "\nShutting down Operating System.\n";
            return;
        }
        
        // Execute the command
        execute(command);
    }
}

// Gets a string input fron the user
string OS::getLine() {
    string input = "";
    cout << "> ";
    getline(cin, input);
    
    while (true) {
        bool valid = false;
        for (unsigned int i = 0; i < input.length(); i++) {
            if (isalpha(input.at(i))) {
                valid = true;
            }
        }
        if (valid){
            break;
        } else {
            cout << "Command not recognized. \nPlease enter a valid command:\n";
            cout << "> ";
            getline(cin, input);
        }
    }
    
    return input;
}

// Get a command from user
vector<string> OS::getCommand() {
    string input = getLine();
    vector<string> command = stringToVector(input);
    
    // Checks for valid command
    while(true) {
        if (command.at(0).at(0) == 'x' || command.at(0).at(0) == 'X' || command.at(0).at(0) == 't'){
            break;
        } else if (command.size() > 1){
            break;
        } else {
            cout << "Command not recognized. \nPlease enter a valid command:\n";
            input = getLine();
            command = stringToVector(input);
        }
    }
    
    return command;
}

// Executes user command
void OS::execute(vector<string> inCommand) {
    char commandCode = inCommand.at(0).at(0);
    
    // ADDS A NEW PROCESS WITH PRIORITY GIVEN
    if (commandCode == 'A') {
        unsigned int priority = 0;
        // Extracts priority from command
        if (isdigit(inCommand.at(1).at(0))) {
            priority = stoi(inCommand.at(1));
        } else {
            cout << "Command not recognized.";
            return;
        }
        addProcess(pidCounter++, priority);
        
    // TERMINATES PROCESS
    } else if  (commandCode == 't'){
        
        terminateProcess();
        
    // CURRENT PROCESS ACCESSES HDD #'S FILE
    } else if  (commandCode == 'd'){
        unsigned int hddNum = 0;
        string fileName = "";
        // Extracts HDD number and file name from command
        if (isdigit(inCommand.at(1).at(0)) && inCommand.size() > 2) {
            hddNum = stoi(inCommand.at(1));
            if (hddNum >= numHardDisks) {
                cout << "Invalid command: You entered a HDD number greater than " << numHardDisks-1 << "." << endl;
                return;
            }
            fileName = inCommand.at(2);
        } else {
            cout << "Command not recognized.";
            return;
        }
        hddAccessFile(hddNum, fileName);
        
        // HDD # COMPLETES CURRENT PROCESS' FILE ACCESS
    } else if  (commandCode == 'D'){
        unsigned int hddNum = 0;
        // Extracts HDD number
        if (isdigit(inCommand.at(1).at(0))) {
            hddNum = stoi(inCommand.at(1));
            if (hddNum >= numHardDisks) {
                cout << "Invalid command: You entered a HDD number greater than " << numHardDisks-1 << "." << endl;
                return;
            }
        } else {
            cout << "Command not recognized.";
            return;
        }
        hddCompleteTask(hddNum);
        
    // PROCESS ACCESS MEMORY LOCATION
    } else if  (commandCode == 'm'){
        unsigned int memAddress = 0;
        // Extracts memoryAddress from command
        if (isdigit(inCommand.at(1).at(0))) {
            memAddress = stoi(inCommand.at(1));
        } else {
            cout << "Command not recognized.";
            return;
        }
        memoryAccess(memAddress);
       
    // SNAPSHOT OF CURRENT OS INSTANCE
    } else if  (commandCode == 'S'){
        char mode = inCommand.at(1).at(0);
        
        if (mode == 'r' || mode == 'i' || mode == 'm') {
            snapshot(mode);
        } else {
            cout << "Command not recognized.";
        }
        
    } else {
        cout << "Command not recognized.";
    }
}

// Adds a new process with the given priority
void OS::addProcess(unsigned int pid, unsigned int priority) {
    // Creates a new Process with provided PID and priority
    shared_ptr<Process> newProcess(new Process(pid, priority));
    // Add the Process to the Ready Queue
    readyQueue.add(newProcess);
    
    // Creates Frame 0 for this process
    shared_ptr<Frame> newFrame(new Frame(0, pid, timestamp++));
    // Add the Frame to the Frame Table
    frameTable.addFrame(newFrame);
    
    cout << "\nNew Process with [PID: " << newProcess->getPid() << "] and [Priority: " <<
    newProcess->getPriority() << "] has been created and added to the Ready Queue.";
}

// Terminates currently running process
void OS::terminateProcess() {
    if (readyQueue.empty()) {
        cout << "\nThere are no processes currently being used by the CPU.";
    } else {
        shared_ptr<Process> temp = readyQueue.popFront();
        cout << "\nProcess with [PID: " << temp->getPid() << "] and [Priority: " <<
        temp->getPriority() << "] has been terminated." << endl;
        frameTable.clearFramesByPid(temp->getPid());
    }
}

// Current process accesses HDD for a file
void OS::hddAccessFile(unsigned int hddNumber, string fileName) {
    if (readyQueue.empty()) {
        cout << "\nThere are no processes currently being used by the CPU.";
        return;
    }
    shared_ptr<Process> temp = readyQueue.popFront();
    // Sets file to be accessed
    temp->setAccessedFile(fileName);
    // Pops the Process at the front of the Ready Queue and adds it to the IO Queue of HDD # given
    ioDevices.at(hddNumber)->addProcessToIOQueue(temp);
    
    cout << "\nProcess with [PID: " << temp->getPid() << "] has been added to IO Queue of [HDD: " << hddNumber <<
    "] to access [File: \"" << fileName << "\"]." << endl;
    
}

// HDD completes its current task
void OS::hddCompleteTask(unsigned int hddNumber) {
    if (ioDevices.at(hddNumber)->empty()) {
        cout << "\nThe IO Queue of [HDD: " << hddNumber << "] is empty.";
        return;
    }
    shared_ptr<Process> temp;
    temp = ioDevices.at(hddNumber)->dequeue();
    readyQueue.add(temp);
    cout << "\nProcess with [PID: " << temp->getPid() << "] has completed accessing [HDD: " <<
    hddNumber << "] and has re-entered the Ready Queue.";
    
}

// Current process accesses memory
void OS::memoryAccess(unsigned int memAddress) {
    if (readyQueue.empty()) {
        cout << "\nThere are no processes currently being used by the CPU.";
    } else {
	unsigned int accessedPage = memAddress / pageSize;
        shared_ptr<Process> temp = readyQueue.at(0);
        // If Page is already in Frame Table, update timestamp
        int pos = frameTable.contains(accessedPage, temp->getPid());
        if (pos >= 0) {
            frameTable.at(pos)->updateTimestamp(timestamp++);
        // If Page is not in Frame Table, add/"swap" it in
        } else {
            shared_ptr<Frame> newFrame(new Frame(accessedPage, temp->getPid(), timestamp++));
            frameTable.addFrame(newFrame);
        }
        cout << "\nProcess with [PID: " << readyQueue.at(0)->getPid() << "] accessed its virtual [Page: " << accessedPage << "].\n";
    }
}

// Snapshot the current running environment
// Modes: [r] Ready Queue, [i] I/O Queue, [m] Memory State
void OS::snapshot(char sMode) {
    
    // Display snapshot of Ready Queue
    if (sMode == 'r') {
        cout << "\n[=== Ready Queue Snapshot ===]" << endl;
        cout << "\n[Position]\t[Proc ID]\t[Priority]" << endl;
        if (readyQueue.empty()) {
            cout << "* Ready Queue is empty and no processes currently using CPU.\n";
        } else if (readyQueue.size() == 1) {
            cout << "Using CPU:\t[PID: " << readyQueue.at(0)->getPid() << "]\t[Priority: " << readyQueue.at(0)->getPriority() << "]" << endl;
            cout << "* There are no other processes waiting to use the CPU.\n";
        } else {
            cout << "Using CPU:\t[PID: " << readyQueue.at(0)->getPid() << "]\t[Priority: " << readyQueue.at(0)->getPriority() << "]" << endl;
            for (unsigned int i = 1; i < readyQueue.size(); i++) {
                cout << "Pos " << i << ":\t\t[PID: " << readyQueue.at(i)->getPid() << "]\t[Priority: " << readyQueue.at(i)->getPriority() << "]" << endl;
            }
        }
    // Display snapshot of IO Devices
    } else if (sMode == 'i') {
        cout << "\n[=== I/O Devices Queue Snapshot ===]" << endl;
        for (unsigned int i = 0; i < ioDevices.size(); i++) {
            cout << "\n== HDD: " << i << " ==" << endl;
            cout << "[Position]\t[Proc ID]\t[File Accessed]" << endl;
            if (ioDevices.at(i)->empty()) {
                cout << "* There are no processes using this HDD." << endl;
            } else {
                for (unsigned int j = 0; j < ioDevices.at(i)->size(); j++) {
                    if (j == 0) {
                        cout << "Using HDD:\t[PID: " << ioDevices.at(i)->at(j)->getPid() << "]\t[\"" << ioDevices.at(i)->at(j)->getAccessedFile() << "\"]\n";
                    } else {
                        cout << "Pos " << j << ":\t\t[PID: " << ioDevices.at(i)->at(j)->getPid() << "]\t[\"" << ioDevices.at(i)->at(j)->getAccessedFile() << "\"]\n";
                    }
                }
            }
        }
        
    // Display snapshot of Memory
    } else {
        cout << "\n[=== Memory Snapshot ===]" << endl;
        cout << "\n[Frame #]\t[Proc ID]\t[Page #]\t[Timestamp]" << endl;
        if (frameTable.isEmpty()) {
            cout << "* The Frame Table does not currently contain any Frames." << endl;
        } else {
            for (unsigned int i = 0; i < numFrames; i++) {
                if (frameTable.at(i) != nullptr) {
                    cout << "[Frame " << i << "]\t[PID: " << frameTable.at(i)->getPid() << "]\t[Page: " << frameTable.at(i)->getPageNum() <<
                    "]\t[Time: " << frameTable.at(i)->getTimestamp() << "]" << endl;
                }
            }
        }
    }
}

// Converts string into vector of strings
vector<string> OS::stringToVector(string inString) {
    vector<string> stringVec;
    
    istringstream iss(inString);
    copy(istream_iterator<string>(iss),
         istream_iterator<string>(),
         back_inserter(stringVec));
    
    return stringVec;
}
