//
//  main.cpp
//
//  Created by Brian Hao on 11/4/17.
//  CSCI340
//  Prof Shostak
//  Operating Systems Project
//  Copyright © 2017 Brian Hao. All rights reserved.
//
// Gets OS parameters from user then creates and starts an OS with
// provided parameters.
//
#include <iostream>
#include <memory>
#include "OS.hpp"
using namespace std;

unsigned int getIntMem();
unsigned int getIntPage(unsigned int memSize);
unsigned int getIntHDD();

int main(int argc, const char * argv[]) {
    // Operating System Parameters
    unsigned int memorySize = 1;
    unsigned int pageSize = 1;
    unsigned int numHardDisks = 1;
    
    // Get OS Parameters from user
    cout << "Please provide parameters to initialize your Operating System." << endl;
    cout << "How much memory (in Bytes) would you like to allocate for your OS? (Max 4,000,000,000)"  << endl;
    memorySize = getIntMem();
    cout << "How much memory (in Bytes) would you like to set as the Page (Frame) Size?" << endl;
    pageSize = getIntPage(memorySize);
    cout << "How many Hard Disk Drives would you like to allocate for your OS?" << endl;
    numHardDisks = getIntHDD();
    
    
    // Create new OS with provided parameters
    OS myOS(memorySize, pageSize, numHardDisks);
    
    // Initialize the Operating System
    myOS.run();
    
    return 0;
}

// Gets a valid integer from the user as the OS's Memory Size
unsigned int getIntMem() {
    unsigned int input = 1;
    cout << "> ";
    cin >> input;
    cin.ignore();
    while ((!cin) || (input > 4000000000) || (input < 1)) {
        cout << "Invalid input. Please input a valid positive integer less than 4,000,000,000." << endl;
        cin.clear();
	cin.ignore();
        cout << "> ";
        cin >> input;
    }
    return input;
}

// Gets a valid integer from the user as the OS's Page Size
unsigned int getIntPage(unsigned int memSize) {
    unsigned int input = 1;
    cout << "> ";
    cin >> input;
    cin.ignore();
    while ((!cin) || (input > memSize) || (input < 1) ) {
        cout << "Invalid input. Please input a valid positive integer less than or equal to " << memSize << "." << endl;
        cin.clear();
	cin.ignore();
        cout << "> ";
        cin >> input;
    }
    return input;
}

// Gets a valid integer from the user
unsigned int getIntHDD() {
    unsigned int input = 1;
    cout << "> ";
    cin >> input;
    cin.ignore();
    while ((!cin) || (input > 100) || (input < 1)) {
        cout << "Invalid input. Please input a valid positive integer." << endl;
        cin.clear();
	cin.ignore();
        cout << "> ";
        cin >> input;
    }
    return input;
}
