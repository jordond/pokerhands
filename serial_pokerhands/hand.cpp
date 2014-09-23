#include "hand.h"

Hand::Hand() {
    //todo / not needed?
}

void Hand::create(Deck &d) {
    for (int i = 0; i < HAND_SIZE; ++i) {
        if (d.getDeckSize() != 0) {
            Card c = d.draw();
            hand_.push_back(c);
        }
        else {
            #if _DEBUG
            std::cout << "Deck is empty..." << std::endl;
            #endif
            d.create();
            i--;
        }
    }
    Hand::analyze();
}

void Hand::analyze() {
    //todo
    std::sort(hand_.begin(), hand_.end());
}

std::string Hand::readable() {
    std::stringstream ss;
    for (std::vector<Card>::iterator it = hand_.begin(); it != hand_.end(); ++it) {
        int s = it->suit();
        int r = it->rank();
        ss << it->suit(s) << it->rank(r);
    }
    return ss.str();
}

bool operator<(Card& lhs, Card& rhs) {
    return lhs.rank() < rhs.rank();
}