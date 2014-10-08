#ifndef STATS_H
#define STATS_H

#include <map>
#include <iomanip>
#include <ctime>
#include "deck.h"

class Stats {
private:
    typedef Hand::HandType type_t;
    std::map<std::string, int> stats_;
    int hands_;
    std::string version_;
    clock_t begin_;
    clock_t end_;

public:
    Stats();
    ~Stats();

    void start();
    void stop();
    void reset();
    double getClock();

    void increment(type_t);
    int getTypeCount(type_t);
    int getHands() { return hands_; }
    bool allHandsFound();

    //printing
    void printHeader();
    void printFooter();
    void printHands();
    void printHistogram();

    std::string typeToString(type_t);

};

#endif