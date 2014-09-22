#include "card.h"

const std::string Card::SUITS[4] = { "S", "C", "D", "H" };
const std::string Card::RANKS[13] = { "a", "2", "3", "4", "5", "6", "7", "8", "9", "10", "j", "q", "k" };

Card::Card() {
    Card::_suit = "0";
    Card::_rank = "0";
}

void Card::createCard(std::string s, std::string r) {
    Card::_suit = s;
    Card::_rank = r;
}