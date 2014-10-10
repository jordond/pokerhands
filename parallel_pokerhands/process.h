/*
Program:		parallel_pokerhands.exe
Module:			process.h
Author:			Jordon de Hoog, Jon Decher
Date:			Sept 30, 2014
Description:	The Process object contains all of the work to be done by the MPI architecture.
                The original plan was to encapsulate it out a bit, however that was deemed unnecessary.
                This object is either called by the master or slave process, and the master will keep 
                track of all the hands drawn by the other processes.
*/

#ifndef PROCESS_H
#define PROCESS_H

#include "deck.h"
#include "stats.h"
#include "mpi.h"

class Process {
private:
    static const int TAG_DATA = 1, TAG_QUIT = 2, TAG_FREQS = 3;    // The different TAG values
    Stats stats_;                                           // Stats container object

    int rank_;                                              // Current rank of the process
    int procs_;                                             // Total number of processes
    int active_;                                            // Total number of active processes

public:
    Process();                                              // Default Constructor
    Process(int, int);                                      // Constuctor for creating Process object by rank and total processes
    ~Process();                                             // Default destructor

    int getProcs() { return procs_; }                       // Return the total number of processes

    void processMaster();                                   // Function that the master will run
    void processSlave(int);                                 // Function that each slave will run

    void checkMessages();                                   // Check for messages from any of the slaves
    void recieveStats(int);                                 // After termination signal found, recieve all stats from slave process

    void terminateSlaves();                                 // Send the termination signal to all the slaves
};

#endif