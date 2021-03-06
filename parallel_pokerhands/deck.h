/*
Program:		parallel_pokerhands.exe
Module:			deck.h
Author:			Jordon de Hoog, Jon Decher
Date:			Sept 30, 2014
Description:	The deck object has a container of 52 card objects which represent a 
                standard deck of cards.  This object has functions that are called to  
                create a new deck, and to draw cards from the deck.  It also can draw 
                a hand which contains the max number of cards for the hand which is defined
                in the Card object.  All references to the Hand object were specifically left
                out of the deck object for interoperability. 
*/

#ifndef DECK_H
#define DECK_H

#include <vector>
#include <algorithm>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "card.h"
#include "hand.h"

class Deck {
private:
    std::vector<Card> cards_;                           // Container that holds all the cards - 52

    static const int MAX_DECK_SIZE = 52;                // Constant for the size of the deck
    int size_;                                          // The current number of cards in deck
    int decks_;                                         // The number of decks drawn

public:
    Deck();                                             // Default constructor
    ~Deck();

    void create();                                      // Create a new vector with all of the cards
    std::vector<Card> getDeck() { return cards_; }      // Returns the deck container

    void shuffle();                                     // Shuffle the deck of cards

    std::vector<Card> dealHand();                       // Deal a new hand of Card::HAND_SIZE cards

    int getDeckSize() { return size_; }                 // Returns the current size of the deck
    int getDecks() { return decks_; }                   // Returns the number of decks drawn - not used

    Card draw();                                        // Draw a new card off the top of the deck
};

#endif