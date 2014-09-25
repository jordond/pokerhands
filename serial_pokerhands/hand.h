#ifndef HAND_H
#define HAND_H

#include <sstream>
#include <vector>
#include <array>
#include "card.h"

class Hand {


public:
    Hand();
    Hand(std::array<int, 10>);
    ~Hand();

    enum HandType { Invalid = -2, None = -1, NoPair = 0, OnePair, TwoPair, ThreeKind, Straight, Flush, FullHouse, FourKind, StraightFlush, RoyalFlush };

    void add(Card);

    HandType analyze();
    std::string readable();

    int handSize() { return HAND_SIZE; }
    void handSize(int h) { HAND_SIZE = h; }

    HandType type() { return type_; }
    void type(HandType t) { type_ = t; }
    
    friend bool operator<(Card& lhs, Card& rhs);

private:
    int HAND_SIZE = 5;

    std::vector<Card> hand_;
    HandType type_;
};

#endif