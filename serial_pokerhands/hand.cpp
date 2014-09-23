#include "hand.h"

Hand::Hand() {

}

void Hand::createHand(Deck &d) {
    for (int i = 0; i < HAND_SIZE; ++i) {
        if (d.getDeckSize() != 0) {
            Card c = d.draw();
            hand_.push_back(c);
        }
        else {
            std::cout << "Deck is empty..." << std::endl;
            d.create();
            i--;
        }
    }
}

std::string Hand::readableHand() {
    std::stringstream ss;
    for (std::vector<Card>::iterator it = hand_.begin(); it != hand_.end(); ++it) {
        int s = it->getSuit();
        int r = it->getRank();
        ss << it->getSuit(s) << it->getRank(r);
    }
    return ss.str();
}