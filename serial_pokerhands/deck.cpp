#include "deck.h"

Deck::Deck() : size_(0), decks_(0) {
    Deck::stats_[0].Type = "No Pair";
    Deck::stats_[1].Type = "One Pair";
    Deck::stats_[2].Type = "Two Pair";
    Deck::stats_[3].Type = "Three of a Kind";
    Deck::stats_[4].Type = "Straight";
    Deck::stats_[5].Type = "Flush";
    Deck::stats_[6].Type = "Full House";
    Deck::stats_[7].Type = "Four of a Kind";
    Deck::stats_[8].Type = "Straight Flush";
    Deck::stats_[9].Type = "Royal Flush";

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
    #if _DEBUG
    std::cout << "New Deck created." << std::endl;
    #endif
    decks_++;
    shuffle();
}

void Deck::shuffle() {
    std::srand(unsigned(std::time(0)));
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