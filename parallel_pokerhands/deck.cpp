#include "deck.h"

//Initialze the deck object to zero, and seed the random number generator
Deck::Deck() : size_(0), decks_(0) {
    std::srand(unsigned(std::time(NULL)));

    //Fill the deck object with cards
    Deck::create();
}

Deck::~Deck() {}

//Fill the deck up with one of each card then shuffle the deck
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

//Used std::random_shuffle to shuffle the cards in the deck
void Deck::shuffle() {    
    std::random_shuffle(&cards_[0], &cards_[MAX_DECK_SIZE - 1]);
}

//Draw a new card from the deck
Card Deck::draw() {
    if (size_ != 0) {
        size_--;
        return cards_[size_];
    }
    else {
        return Card();
    }
}

//Deal a new hand of 5 cards
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
            create(); //refill the deck
            i--;
        }
    }
    return h;
}