#ifndef HAND_H
#define HAND_H

#include <sstream>
#include <vector>
//#include <array>
#include "card.h"

class Hand {
public:
    Hand();
    Hand(std::vector<Card>);
    //Hand(std::array<int, 10>);
    ~Hand();

    enum HandType { Invalid = -2, None = -1, HighCard = 0, OnePair, TwoPair, ThreeKind, Straight, Flush, FullHouse, FourKind, StraightFlush, RoyalFlush };

    void add(Card);

    HandType analyze();
    std::string readable();

    HandType type() { return type_; }
    void type(HandType t) { type_ = t; } //shouldn't use
    
    friend bool operator<(Card& lhs, Card& rhs);

private:
    std::vector<Card> hand_;
    HandType type_;
};

#endif