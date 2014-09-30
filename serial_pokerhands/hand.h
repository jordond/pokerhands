#ifndef HAND_H
#define HAND_H

#include <sstream>
#include <vector>
#include <array>
#include "card.h"

enum class HandType { Invalid = -2, None = -1, HighCard = 0, OnePair, TwoPair, ThreeKind, Straight, Flush, FullHouse, FourKind, StraightFlush, RoyalFlush };

class Hand {
private:
    int HAND_SIZE = 5;

    std::vector<Card> hand_;
    HandType type_;

public:
    Hand();
    Hand(std::array<int, 10>);
    ~Hand();

    void add(Card);

    HandType analyze();
    std::string readable();

    int handSize() { return HAND_SIZE; }
    void handSize(int h) { HAND_SIZE = h; }

    HandType type() { return type_; }
    void type(HandType t) { type_ = t; } //shouldn't use
    
    friend bool operator<(Card& lhs, Card& rhs);
};

#endif