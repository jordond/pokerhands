/*
Program:		parallel_pokerhands.exe
Module:			card.h
Author:			Jordon de Hoog, Jon Decher
Date:			Sept 30, 2014
Description:	The card object holds all the data and functions relevant to the card.
                It is used to recognize suits and ranks, and used for the Deck and hand objects.
*/

#ifndef CARD_H
#define CARD_H

#include <sstream>
#include <string>

class Card {
private:
    int suit_;                          // Current suit of the card
    int rank_;                          // Current rank of the card

public:
    Card();                             // Default constructor
    Card(int s, int r);                 // Create card with a set suit and rank
    ~Card() {}

    static const int HAND_SIZE = 5;     // Hand size constant used for 5 or 7 card poker
    static const int SUITS[4];          // Array of all the suits
    static const int RANKS[13];         // Array of all the ranks
    
    void createCard(int s, int r);      // Create a card with a set suit and rank - deprecated use constructor
    bool valid();                       // Returns true if card is valid - deprecated
    int suit();                         // Return the suit of the card
    int rank();                         // Return the rank of the card
    std::string suit(int);              // Return a human readble version of the suit
    std::string rank(int);              // Return a human readble version of the rank
};

#endif