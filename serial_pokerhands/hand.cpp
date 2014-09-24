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
    bool pair = false, pair2 = false, three = false, four = false, flush = false, strt = false, rflush = false;
    int rank[14] = {0}; //13 ranks, low + high ace = 14
    int suit[4] = {0};
    for (std::vector<Card>::iterator it = hand_.begin(); it != hand_.end(); ++it) {
        rank[it->rank() - 1]++; // rank starts at 1 not 0
        suit[it->suit()]++;
    }
    //check for ace
    if (rank[0] > 0) {
        rank[13] = rank[0];
    }
    //one pair, two pair, 3kind, 4kind 
    for (int i = 0; i < 13; ++i){
        switch (rank[i]) {
        case 2:
            if (pair) 
                pair2 = true;
            else
                pair = true;
            break;
        case 3:
            three = true;
            break;
        case 4:
            four = true;
        }
    }
    //flush
    for (int i = 0; i < 4; ++i) {
        if (suit[i] == 5) {
            flush = true;
            break;
        }
    }
    //straight
    if (!pair && !pair2 && !three && !four) {
        int r = 0;
        for (int i = 0; i < 14; ++i) {
            if (rank[i] == 1) {
                r++;
            } else {
                r = 0;
            }
            if (r == 5)
                break;
        }
    }
    if (rflush)             return Deck::RoyalFlush;
    else if (flush && strt) return Deck::StraightFlush;
    else if (four)          return Deck::FourKind;
    else if (pair && three) return Deck::FullHouse;
    else if (flush)         return Deck::Flush;
    else if (strt)          return Deck::Straight;
    else if (three)         return Deck::ThreeKind;
    else if (pair && pair2) return Deck::TwoPair;
    else if (pair)          return Deck::OnePair;
    return Deck::NoPair;
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