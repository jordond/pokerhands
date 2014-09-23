#include "card.h"

const int Card::SUITS[4] = { (int) Suit::Diamonds, (int) Suit::Hearts, (int) Suit::Clubs, (int) Suit::Spades };
const int Card::RANKS[13] = { 1,2,3,4,5,6,7,8,9,10,11,12,13 };

Card::Card() {
    Card::_suit = -1;
    Card::_rank = -1;
}

void Card::createCard(int s, int r) {
    Card::_suit = s;
    Card::_rank = r;
}

std::string Card::suit(int s) {
    switch (s)
    {
    case (int)Suit::Diamonds:
        return "D";
    case (int)Suit::Hearts:
        return "H";
    case (int)Suit::Clubs:
        return "C";
    case (int) Suit::Spades:
        return "S";
    default:
        return "U"; //unknown
    }
}

std::string Card::rank(int r) {
    switch (r)
    {
    case 1:
        return "a";
    case 11:
        return "j";
    case 12:
        return "q";
    case 13:
        return "k";
    default:
        return std::to_string(r); //non monkey
    }
}