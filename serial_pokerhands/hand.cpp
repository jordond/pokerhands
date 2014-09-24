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

int Hand::analyze() {
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
                strt = true;
                break;
            }
        }        
    }
    //royal - 10, j=11, q=12, k=13, a=14 flush
    if (flush && strt) {
        if (rank[9] == 1 && rank[10] == 1 && rank[11] == 1 && rank[12] == 1 && rank[13] == 1) {
            rflush = true;
        }
    }

    if (rflush)             return Hand::RoyalFlush;
    else if (flush && strt) return Hand::StraightFlush;
    else if (four)          return Hand::FourKind;
    else if (pair && three) return Hand::FullHouse;
    else if (flush)         return Hand::Flush;
    else if (strt)          return Hand::Straight;
    else if (three)         return Hand::ThreeKind;
    else if (pair && pair2) return Hand::TwoPair;
    else if (pair)          return Hand::OnePair;
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

std::string Hand::readableType() {
    switch (type_) {
    case Hand::RoyalFlush:
        return "Royal Flush";
    case Hand::StraightFlush:
        return "Straight Flush";
    case Hand::FourKind:
        return "Four of a Kind";
    case Hand::FullHouse:
        return "Full House";
    case Hand::Flush:
        return "Flush";
    case Hand::Straight:
        return "Straight";
    case Hand::ThreeKind:
        return "Three of a Kind";
    case Hand::TwoPair:
        return "Two pairs";
    case Hand::OnePair:
        return "One Pair";
    case Hand::NoPair:
        return "High Card/No Pair";
    default:
        return "Invalid";
    }
}

bool operator<(Card& lhs, Card& rhs) {
    return lhs.rank() < rhs.rank();
}