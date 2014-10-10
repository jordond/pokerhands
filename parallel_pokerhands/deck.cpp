#include "deck.h"

Deck::Deck() : size_(0), decks_(0) {
    std::srand(unsigned(std::time(NULL)));

    Deck::create();
}

Deck::~Deck() {}

void Deck::create() {
    cards_.clear();
    for (int i = 0; i < 13; ++i) {
        for (int j = 0; j < 4; ++j) {
            Card c = Card(c.SUITS[j], c.RANKS[i]);
            cards_.push_back(c);
            size_++;
        }
    }
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
        return Card();
    }
}

std::vector<Card> Deck::dealHand() {
    std::vector<Card> h;
    for (int i = 0; i < Card::HAND_SIZE; ++i) {
        if (size_ != 0) {
            Card c = draw();
            if (c.rank() != -1 && c.suit() != -1){ // invalid card returned
                h.push_back(c);
            }
        }
        else { //deck is empty
            create();
            i--;
        }
    }
    return h;
}