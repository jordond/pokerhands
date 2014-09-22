#include "deck.h"

Deck::Deck() : size_(0), decks_(0) {
    Deck::create();
}

Deck::~Deck() {}

void Deck::create() {
    cards_.clear();
    for (int i = 0; i < 13; ++i) {
        for (int j = 0; j < 4; ++j) {
            Card c;
            c.createCard(c.SUITS[j], c.RANKS[i]);
            cards_.push_back(c);
            size_++;
        }
    }
    #if _DEBUG
    std::cout << "New Deck created." << std::endl;
    #endif
    decks_++;
    shuffle();
}

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