#include "card.h"

const int Card::SUITS[4] = { 0, 1, 2, 3 };                      //Contains values for the suits
const int Card::RANKS[13] = { 1,2,3,4,5,6,7,8,9,10,11,12,13 };  //Contains values for the ranks

//Initialize default card as invalid
Card::Card() : suit_(-1), rank_(-1) {}

//Create a new card based on passed in rank and suit
Card::Card(int s, int r) : suit_(s), rank_(r) {}

//Returns true if the card is rank and suit is between acceptable values
bool Card::valid() {
    if (rank_ >= 0 && rank_ <= 13 &&
        suit_ >= 0 && suit_ <= 3) {
        return true;
    }
    return false;
}

int Card::suit() {
    return suit_;
}

int Card::rank() {
    return rank_;
}

//Returns a human readble version of the suit
std::string Card::suit(int s) {
    switch (s)
    {
    case 0:
        return "D"; //Diamond
    case 1:
        return "H"; //Heart
    case 2:
        return "C"; //Club
    case 3:
        return "S"; //Spade
    default:
        return "U"; //unknown
    }
}

//Return a human readble version of the rank
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
        std::stringstream ss;
        ss << r;
        return ss.str(); //non monkey
    }
}