#include "deck.h"

Deck::Deck() : size_(MAX_DECK_SIZE) {
    for (int i = 0; i < 13; ++i) {
        for (int j = 0; j < 4; ++j) {
            Card c;
            c.createCard(c.SUITS[j], c.RANKS[i]);
            cards_.push_back(c);
        }
    }
    #if _DEBUG
    std::cout << "New Deck created." << std::endl;
    #endif
    decksCreated_++;
    shuffle();
}

Deck::~Deck() {}

void Deck::shuffle() {
    std::random_shuffle(&cards_[0], &cards_[MAX_DECK_SIZE - 1]);
}

Card Deck::draw() {
    if (size_ != 0) {
        size_--;
        return cards_[size_];
    }
    else {
        Card c;
        return c;
    }
}

void Deck::setDecksCreated(int d) {
    decksCreated_ = d;
}