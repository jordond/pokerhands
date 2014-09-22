#ifndef HAND_H
#define HAND_H

#include "deck.h"

class Hand {
private:
    static const int HAND_SIZE = 5;

    std::vector<Card> _hand;

public:
    Hand();

    std::string test;
    void createHand(Deck&);

};

#endif