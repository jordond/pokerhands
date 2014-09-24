#ifndef HAND_H
#define HAND_H

#include <sstream>
#include <array>
#include "deck.h"

class Hand {
private:
    static const int HAND_SIZE = 5;

    std::vector<Card> hand_;
    int type_;

public:
    Hand();
    Hand(Deck&);
    Hand(std::array<int, HAND_SIZE * 2>);
    ~Hand();

    int analyze();
    std::string readable();
    int type() { return type_; }
    void type(int t) { type_ = t; }

    enum HandType { Invalid = -2, None = -1, NoPair = 0, OnePair, TwoPair, ThreeKind, Straight, Flush, FullHouse, FourKind, StraightFlush, RoyalFlush };
    
    friend bool operator<(Card& lhs, Card& rhs);
};

#endif