//
//  Frame.hpp
//  AethyrOS.cpp
//
//  Created by Brian Hao on 11/22/17.
//  CSCI340
//  Prof Shostak
//  Operating Systems Project
//  Copyright © 2017 Brian Hao. All rights reserved.
//
// A Frame contains the PID of its process, the virtual page number, and the timestamp for LRU
//

#ifndef Frame_hpp
#define Frame_hpp

class Frame{
public:
    Frame(unsigned int inPageNum, unsigned int inPid, unsigned int inTime) {
        pageNum = inPageNum; pid = inPid; timestamp = inTime;
    }
    
    // Update Timestamp when this frame is accessed
    void updateTimestamp(unsigned int inTime) { timestamp = inTime; };
    
    // Get Frame Information
    unsigned int getPageNum() { return pageNum; };
    unsigned int getPid() { return pid; };
    unsigned int getTimestamp() { return timestamp; };
    
private:
    // Frame Parameters
    unsigned int pageNum = 0;
    unsigned int pid = 0;
    unsigned int timestamp = 0;
};

#endif /* Frame_hpp */
