#include "hand.h"

Hand::Hand() {

}

void Hand::createHand(Deck &d) {
    for (int i = 0; i < HAND_SIZE; ++i) {
        if (d.getDeckSize() != 0) {
            Card c = d.draw();
            test.append(c.getSuit() + c.getRank() + ", ");
            _hand.push_back(c);
        }
        else {
            std::cout << "Deck is empty..." << std::endl;
            d.create();
            i--;
        }
    }
}