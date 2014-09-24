#ifndef HAND_H
#define HAND_H

#include <sstream>
#include <vector>
#include <array>
#include "card.h"

class Hand {
private:
    int HAND_SIZE = 5;
    
    std::vector<Card> hand_;
    int type_;

public:
    Hand();
    Hand(std::array<int, 10>);
    ~Hand();

    void add(Card);

    int analyze();
    std::string readable();
    std::string readableType();

    int handSize() { return HAND_SIZE; }
    void handSize(int h) { HAND_SIZE = h; }

    int type() { return type_; }
    void type(int t) { type_ = t; }

    enum HandType { Invalid = -2, None = -1, NoPair = 0, OnePair, TwoPair, ThreeKind, Straight, Flush, FullHouse, FourKind, StraightFlush, RoyalFlush };
    
    friend bool operator<(Card& lhs, Card& rhs);
};

#endif