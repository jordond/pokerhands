#include "hand.h"

Hand::Hand() {
    //todo / not needed?
}

void Hand::createHand(Deck &d) {
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
}

void Hand::analyzeHand() {
    //todo
}

std::string Hand::readableHand() {
    std::stringstream ss;
    for (std::vector<Card>::iterator it = hand_.begin(); it != hand_.end(); ++it) {
        int s = it->suit();
        int r = it->rank();
        ss << it->suit(s) << it->rank(r);
    }
    return ss.str();
}