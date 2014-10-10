#ifndef PROCESS_H
#define PROCESS_H

#include "deck.h"
#include "stats.h"
#include "mpi.h"

class Process {
private:
    const int TAG_DATA = 1, TAG_QUIT = 2, TAG_FREQS = 3;    // The different TAG values
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