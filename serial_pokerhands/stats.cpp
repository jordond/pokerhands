#include "stats.h"

Stats::Stats() {

}

Stats::~Stats() {}

void Stats::setValue(type_t t) {
    std::string k = typeToString(t);
}

int Stats::getValue(type_t t) {
    std::string k = typeToString(t);
    if (stats_.find(k) == stats_.end()) {
        return -1;
    }
    else {
        return stats_[k];
    }
}

std::string Stats::typeToString(type_t t) {
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