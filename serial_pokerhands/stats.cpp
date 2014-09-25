#include "stats.h"

Stats::Stats() {
    const std::string VERSION = "SERIAL";
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
    int c = stats_.size();
    if (stats_.find("Invalid") == stats_.end()) {
        c--;
    }
    if (c == 10) {
        return true;
    }
    return false;
}

void Stats::printHeader() {
    std::cout << "Poker Hand Frequency Simulation [" + VERSION + " Version]" << std::endl;
    std::cout << "=====================================================" << std::endl;
    std::cout << "Hand Type: " << std::endl;
}

void Stats::printFooter() {
    std::cout << "-----------------------------------------------------" << std::endl;
    std::cout << "Hands Generated:" << std::endl;
    std::cout << "Decks Drawn:" << std::endl;
    std::cout << "Elapsed Time:" << std::endl;
    if (VERSION == "PARALLEL")
        std::cout << "Number of Processes:" << std::endl;
    std::cout << "-----------------------------------------------------" << std::endl;
}

void Stats::printHands() {
    std::cout << "Hands: " << std::endl;
    for (std::map<std::string, int>::iterator m = stats_.begin(); m != stats_.end(); ++m) {
        std::cout << m->first << "\t\tCount: " << m->second << std::endl;
    }
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
        return "High Card";
    default:
        return "Invalid";
    }
}