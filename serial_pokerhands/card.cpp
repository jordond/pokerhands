#include "card.h"

const int Card::SUITS[4] = { (int) Suit::Diamonds, (int) Suit::Hearts, (int) Suit::Clubs, (int) Suit::Spades };
const int Card::RANKS[13] = { 1,2,3,4,5,6,7,8,9,10,11,12,13 };

Card::Card() : suit_(-1), rank_(-1) {}

Card::Card(int s, int r) : suit_(s), rank_(r) {}

int Card::suit() {
    return suit_;
}

int Card::rank() {
    return rank_;
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