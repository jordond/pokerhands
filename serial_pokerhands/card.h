#ifndef CARD_H
#define CARD_H

#include <string>

enum class Suit { Diamonds = 0, Hearts = 1, Clubs = 2, Spades = 3};

class Card {
private:
    int suit_;
    int rank_;

public:
    Card();
    Card(int s, int r);
    ~Card() {}

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