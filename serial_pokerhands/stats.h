#ifndef STATS_H
#define STATS_H

#define VERSION "SERIAL"

#include <map>
#include "deck.h"

class Stats {
private:
    typedef HandType type_t;
    std::map<std::string, int> stats_;
public:
    Stats();
    ~Stats();

    void increment(type_t);
    int getValue(type_t);
    bool allHandsFound();

    //printing
    void printHeader();

    std::string typeToString(type_t);

};

#endif