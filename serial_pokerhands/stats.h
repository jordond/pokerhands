#ifndef STATS_H
#define STATS_H

#include <map>
#include "deck.h"

class Stats {
private:
    std::map<std::string, int> stats_;

public:
    Stats();
    ~Stats();

    void increment();

    int getValue(int);

    std::string typeToString(int);

};

#endif