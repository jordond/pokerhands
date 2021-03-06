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
    std::vector<Card> cards_;

    static const int MAX_DECK_SIZE = 52;
    int size_;
    int decks_;

public:
    Deck();
    ~Deck();

    void create();
    std::vector<Card> getDeck() { return cards_; }

    // Shuffles the deck of cards
    void shuffle();

    std::vector<Card> dealHand();

    // Obtain the current number of cards in the deck.
    // Returns: int - size of deck
    int getDeckSize() { return size_; }

    int getDecks() { return decks_; }

    // Draw a card from the top of the deck, and remove it
    // from the deck.
    // Returns: Card - card on the top of deck
    Card draw();
};

#endif