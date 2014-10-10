#ifndef HAND_H
#define HAND_H

#include <sstream>
#include <vector>
#include <iostream>
#include <algorithm>
#include "card.h"

class Hand {
public:
    Hand();                                     // Default constructor
    Hand(std::vector<Card>);                    // Create a hand by passing a vector of (5) cards
    Hand(std::string);                          // todo Convert a user entered string to a valid hand
    ~Hand();

    // All of the different hand types, numbers added for int to enum casting
    enum HandType { Invalid = -2, None = -1, HighCard = 0, OnePair = 1, TwoPair = 2, 
                    ThreeKind = 3, Straight = 4, Flush = 5, FullHouse = 6, FourKind = 7, 
                    StraightFlush = 8, RoyalFlush = 9 };

    void add(Card);                             // Add a card to the hand vector

    HandType analyze();                         // Analyse the current hand and return its type
    std::string readable();                     // Convert the hand (numbers) to a more readable string format

    HandType type() { return type_; }           // Return the type of the current hand
    void type(HandType t) { type_ = t; }        // shouldn't use, set the hand type
    
    friend bool operator<(Card& lhs, Card& rhs);// Used for sorting the hand - deprecated

private:
    std::vector<Card> hand_;                    // Container of cards
    HandType type_;                             // The type of poker hand
};

#endif