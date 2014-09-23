#ifndef HAND_H
#define HAND_H

#include <sstream>
#include "deck.h"

class Hand {
private:
    static const int HAND_SIZE = 5;

    std::vector<Card> hand_;

public:
    Hand();

    void create(Deck&);
    void analyze();
    std::string readable();

    friend bool operator<(Card& lhs, Card& rhs);
};

#endif