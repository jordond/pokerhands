#ifndef STATS_H
#define STATS_H

#include <map>
#include "deck.h"

class Stats {
private:
    typedef HandType type_t;
    std::map<std::string, int> stats_;
    
    const std::string VERSION;

public:
    Stats();
    ~Stats();

    void increment(type_t);
    int getValue(type_t);
    bool allHandsFound();

    //printing
    void printHeader();
    void printFooter();

    std::string typeToString(type_t);

};

class A {
private:
    static const std::string RECTANGLE;
};

#endif