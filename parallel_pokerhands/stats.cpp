#include "stats.h"

Stats::Stats() : hands_(0), version_("PARALLEL") {}

Stats::~Stats() {}

//Start the clock
void Stats::start() {
    begin_ = clock();
}

//Stop the clock
void Stats::stop() {
    end_ = clock();
}

//Reset the clock
void Stats::reset() {
    begin_ = 0;
    end_ = 0;
}

//Return the elapsed time in seconds
double Stats::getClock() {
    return double(end_ - begin_) / CLOCKS_PER_SEC;
}

//Increment a single hand type
void Stats::increment(int t) {
    std::string k = typeToString(t);
    stats_[k]++; //update or add
    hands_++;
}

//Increment multiple hands of the same type
void Stats::increment(int t, int n) {
    std::string k = typeToString(t);
    stats_[k] += n;
    hands_ += n;
}

//Return the number of hands of a specific type
int Stats::getTypeCount(int t) {
    std::string k = typeToString(t);
    if (stats_.find(k) == stats_.end()) {
        return -1; // hand type wasn't found
    }
    else {
        return stats_[k];
    }
}

//Return true if all the hand types have been found
bool Stats::allHandsFound() {
    int c = stats_.size();
    if (stats_.find("Invalid") != stats_.end()) { //if a invalid hand is in the map than decrement the count
        c--;
    }
    if (c == 10) { //10 for royalflush, 9 quicker debug
        return true;
    }
    return false;
}

void Stats::printHeader() {
    std::cout << "Poker Hand Frequency Simulation [" + version_ + " Version]" << std::endl;
    std::cout << "=====================================================" << std::endl;
}

//Take the map and reverse it so royal flush is at the bottom
void Stats::printHands() {
    std::cout << "Hand Type" << "\t\tFrequency" << "\tRelative (%)" << std::endl;
    std::map<int, std::string> sorted;
    for (std::map<std::string, int>::iterator m = stats_.begin(); m != stats_.end(); ++m) {
        sorted[m->second] = m->first;
    }
    for (std::map<int, std::string>::reverse_iterator m = sorted.rbegin(); m != sorted.rend(); ++m) {
        double relF = ((double) m->first / hands_) * 100;
        std::cout << std::setprecision(6) << std::fixed;
        std::cout << m->second << "\t\t" << m->first << "\t\t" << relF << "%" << std::endl;
    }
}

void Stats::printFooter(int n) {
    std::cout << "-----------------------------------------------------" << std::endl;
    std::cout << std::setprecision(3) << std::fixed;
    std::cout << "Hands Generated:\t" << hands_ << std::endl;
    std::cout << "Decks Drawn:\t\t" << hands_ / 10.0 << std::endl;
    std::cout << "Elapsed Time:\t\t" << getClock() << "s" << std::endl;
    if (version_ == "PARALLEL")
        std::cout << "Number of Processes:\t\t" << n << std::endl;
    std::cout << "-----------------------------------------------------" << std::endl;
}

void Stats::printHistogram() {
    //todo
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
        return "Flush\t";
    case Hand::Straight:
        return "Straight";
    case Hand::ThreeKind:
        return "Three of a Kind";
    case Hand::TwoPair:
        return "Two pairs";
    case Hand::OnePair:
        return "One Pair";
    case Hand::HighCard:
        return "High Card";
    default:
        return "Invalid";
    }
}