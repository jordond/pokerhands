#include "hand.h"

Hand::Hand() : type_(Deck::NoPair) {}

Hand::~Hand() {}

void Hand::create(Deck &d) {
    hand_.clear();
    type_ = Deck::NoPair;
    for (int i = 0; i < HAND_SIZE; ++i) {
        if (d.getDeckSize() != 0) {
            Card c = d.draw();
            hand_.push_back(c);
        }
        else {
            //std::cout << "Deck is empty..." << std::endl;
            d.create();
            i--;
        }
    }
    type_ = Hand::analyze();
}

//void Hand::create(Deck &d) {
//    
//}

int Hand::analyze() {
    //std::sort(hand_.begin(), hand_.end());
    int handType = Deck::HandType::NoPair;
    int test = 1;
    int rank[13] = {0};
    int suit[4] = {0};
    for (std::vector<Card>::iterator it = hand_.begin(); it != hand_.end(); ++it) {
        rank[it->rank() - 1]++;
        suit[it->suit()]++;
    }

    //flush
    for (int i = 0; i < 4; ++i) {
        if (suit[i] == 5) {
            handType = Deck::Flush;
        }
    }
    return handType;
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