#ifndef STATS_H
#define STATS_H

#include <map>
#include "deck.h"

class Stats {
private:
    typedef Hand::HandType type_t;
    std::map<std::string, int> stats_;
public:
    Stats();
    ~Stats();

    void increment(type_t);

    void setValue(type_t);
    int getValue(type_t);

    std::string typeToString(type_t);

};

#endif