#include "hand.h"

Hand::Hand() : type_(HandType::None) {}

Hand::Hand(std::array<int, 10>r) : type_(HandType::None) {
    for (int i = 0; i < 10; i += 2) {
        Card c = Card(r[i], r[i + 1]);
        hand_.push_back(c);
    }
    type_ = Hand::analyze();
}

Hand::~Hand() {}

void Hand::add(Card c) {
    hand_.push_back(c);
}

HandType Hand::analyze() {
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
                if (flush && rank[9] == 1 && rank[13] == 1) //royal flush
                    rflush = true;
                strt = true;                
                break;
            }
        }        
    }

    if (rflush)             return HandType::RoyalFlush;
    else if (flush && strt) return HandType::StraightFlush;
    else if (four)          return HandType::FourKind;
    else if (pair && three) return HandType::FullHouse;
    else if (flush)         return HandType::Flush;
    else if (strt)          return HandType::Straight;
    else if (three)         return HandType::ThreeKind;
    else if (pair && pair2) return HandType::TwoPair;
    else if (pair)          return HandType::OnePair;
    return HandType::NoPair;
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