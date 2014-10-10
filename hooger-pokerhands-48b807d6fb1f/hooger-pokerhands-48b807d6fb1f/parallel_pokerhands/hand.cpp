#include "hand.h"

Hand::Hand() : type_(Hand::None) {}

Hand::Hand(std::vector<Card> c) : type_(Hand::None) {
    for (size_t i = 0; i < c.size(); ++i) {
        Hand::add(c[i]);
    }
    Hand::analyze();
}

Hand::Hand(std::string s) : type_(Hand::None) {
    if (s.length() == Card::HAND_SIZE * 2) {
        //todo
    }
}

Hand::~Hand() {}

void Hand::add(Card c) {
    hand_.push_back(c);
}

Hand::HandType Hand::analyze() {
    bool pair = false, pair2 = false, three = false, four = false, flush = false, strt = false, rflush = false;
    int rank[14] = {0}; //13 ranks, low + high ace = 14
    int suit[4] = {0};
    for (std::vector<Card>::iterator it = hand_.begin(); it != hand_.end(); ++it) {
        rank[it->rank() - 1]++; // rank starts at 1 not 0
        suit[it->suit()]++;
    }
    //check for ace high
    rank[13] = (rank[0] > 0) ? rank[0] : 0;

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
        int r = 0; //run count
        for (int i = 0; i < 14; ++i) {
            if (rank[i] == 1) {
                r++;
            } else {
                r = 0;
            }
            if (r == 5) {
                if (flush && rank[9] == 1 && rank[13] == 1) {//royal flush
                    rflush = true;
                }
                strt = true;                
                break;
            }
        }        
    }

    if (rflush)             return type_ = Hand::RoyalFlush;
    else if (flush && strt) return type_ = Hand::StraightFlush;
    else if (four)          return type_ = Hand::FourKind;
    else if (pair && three) return type_ = Hand::FullHouse;
    else if (flush)         return type_ = Hand::Flush;
    else if (strt)          return type_ = Hand::Straight;
    else if (three)         return type_ = Hand::ThreeKind;
    else if (pair && pair2) return type_ = Hand::TwoPair;
    else if (pair)          return type_ = Hand::OnePair;
    return type_ = Hand::HighCard;
}

std::string Hand::readable() {
    std::stringstream ss;
    for (std::vector<Card>::iterator it = hand_.begin(); it != hand_.end(); ++it) {
        int s = it->suit();
        int r = it->rank();
        ss << "[" << it->suit(s) << it->rank(r) << "] ";
    }
    return ss.str();
}

bool operator<(Card& lhs, Card& rhs) {
    return lhs.rank() < rhs.rank();
}

