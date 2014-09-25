#ifndef STATS_H
#define STATS_H

#include <map>
#include <iomanip>
#include "deck.h"

class Stats {
private:
    typedef HandType type_t;
    std::map<std::string, int> stats_;
    int hands_;
    int decks_;
    std::string version_;

public:
    Stats();
    ~Stats();

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

class A {
private:
    static const std::string RECTANGLE;
};

#endif