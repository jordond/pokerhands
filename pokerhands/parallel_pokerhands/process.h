#ifndef PROCESS_H
#define PROCESS_H

#include "deck.h"
#include "stats.h"
#include "mpi.h"

class Process {
private:
    static const int TAG_DATA = 1, TAG_QUIT = 2, TAG_FREQS = 3;
    Stats stats_;

    int rank_;
    int procs_;
    int active_;

public:
    Process();
    Process(int, int);
    ~Process();

    void processMaster();
    void processSlave(int);

    void checkMessages();
    void recieveStats(int);

    void terminateSlaves();
};

#endif