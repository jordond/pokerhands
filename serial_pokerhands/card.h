#ifndef CARD_H
#define CARD_H

#include <string>

enum class Suit { Diamonds = 1, Hearts, Clubs, Spades };

class Card {
private:
    int suit_;
    int rank_;

public:
    Card();
    Card(int s, int r);

    static const int SUITS[4];
    static const int RANKS[13];
    
    // Sets the current card information based on the passed in arguments.
    // Accepts: int Suit, int Rank
    void createCard(int s, int r);

    int suit();
    int rank();
    std::string suit(int);
    std::string rank(int);

};

#endif