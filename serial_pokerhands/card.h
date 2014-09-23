#ifndef CARD_H
#define CARD_H

#include <string>

enum class Suit { Diamonds = 1, Hearts, Clubs, Spades };

class Card {
private:
    int _suit;
    int _rank;

public:
    Card();

    static const int SUITS[4];
    static const int RANKS[13];
    
    // Sets the current card information based on the passed in arguments.
    // Accepts: int Suit, int Rank
    void createCard(int s, int r);

    int getSuit() { return _suit; }
    int getRank() { return _rank; }
    std::string getSuit(int);
    std::string getRank(int);

};

#endif