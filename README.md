#Operating System Process Queue Simulation
Brian Hao

A basic command-line simulation of an operating system and its management of processes. Scheduling uses preemptive priority scheduling. I/O device (in this case, HDD) queues are FCFS.

On execution, user will be prompted for the amount of memory (in bytes) desired for their simulated computer, the size of a page/frame, and the number of IO devices (in this case, HDD). HDD enumeration starts at 0.

## Compilation Instructions
### Compile your code with:

`make all`

### Execute using:

`./OS`

## Commands
    A <priority> : 
		(ex. "A 12")
		Create a new process with a given priority.
		
    t : 
		Terminate current process accessing CPU immediately.
		
    d <disk_num> <file_name> : 
		(ex. "d 1 file.txt")
		Process currently using CPU requests disk <disk_num> 
		to access file <file_name>. 
		
    D <disk_num> : 
		Interrupt from disk <disk_num>. Current task complete.
		
	m <mem_address> :
		(ex. "m 12000")
		Process currently using CPU requests a memory operation
		for the address <mem_address>.
    
	S <i, r, OR m> : Snapshot of System.
        S i : IO devices information
        S r : Ready Queue information
        S m : Memory information
		
    x OR X :
		Exits program.