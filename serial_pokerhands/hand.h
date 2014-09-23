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

    void createHand(Deck&);
    void analyzeHand();
    std::string readableHand();
};

#endif