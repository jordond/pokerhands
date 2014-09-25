#include "stats.h"

Stats::Stats() {

}

Stats::~Stats() {}

void Stats::increment(type_t t) {
    std::string k = typeToString(t);
    stats_[k]++; //update or add
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

bool Stats::allHandsFound() {
    int c = stats_.count;
    if (stats_.find("Invalid") == stats_.end()) {
        c--;
    }
    if (c == 10) {
        return true;
    }
    return false;
}

std::string Stats::typeToString(type_t t) {
    switch (t) {
    case HandType::RoyalFlush:
        return "Royal Flush";
    case HandType::StraightFlush:
        return "Straight Flush";
    case HandType::FourKind:
        return "Four of a Kind";
    case HandType::FullHouse:
        return "Full House";
    case HandType::Flush:
        return "Flush";
    case HandType::Straight:
        return "Straight";
    case HandType::ThreeKind:
        return "Three of a Kind";
    case HandType::TwoPair:
        return "Two pairs";
    case HandType::OnePair:
        return "One Pair";
    case HandType::NoPair:
        return "High Card/No Pair";
    default:
        return "Invalid";
    }
}