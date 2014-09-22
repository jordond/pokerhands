#ifndef CARD_H
#define CARD_H

#include <string>

class Card {
private:
    std::string _suit;
    std::string _rank;

public:
    Card();

    static const std::string SUITS[4];
    static const std::string RANKS[13];
    
    // Sets the current card information based on the passed in arguments.
    // Accepts: std::string Suit, std::string Rank
    void createCard(std::string, std::string);

    std::string getSuit() { return _suit; }
    std::string getRank() { return _rank; }
};

#endif