#ifndef HAND_H
#define HAND_H

#include <sstream>
#include "deck.h"

class Hand {
private:
    static const int HAND_SIZE = 5;

    std::vector<Card> hand_;
    int type_;

public:
    Hand();
    Hand(Deck&);
    Hand(int []);
    ~Hand();

    int analyze();
    std::string readable();
    int type() { return type_; }
    friend bool operator<(Card& lhs, Card& rhs);
};

#endif