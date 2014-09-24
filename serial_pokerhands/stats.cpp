#include "stats.h"

Stats::Stats() {

}

Stats::~Stats() {}

int Stats::getValue(int t) {
    int val = 0;
    std::string test = "";

    test = Stats::typeToString(t);
    
    return 0;
}

std::string Stats::typeToString(int t) {
    switch (t) {
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