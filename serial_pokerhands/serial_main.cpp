#include "serial_main.h"

int main() {
    //debugHandType();
    //debugVariableHands();
    //debug250000Hands();
    debugFindAllHands();

    return 0;
}

void debugHandType() {
    ////DEBUG
    Deck d;
    Stats s;
    int hands_ = 0;

    // 0 - Diamond
    // 1 - Heart
    // 2 - Club
    // 3 - Spade
    // 11 - Jack
    // 12 - Queen
    // 13 - King
    // 1  - Ace

    std::vector< std::array<int, 10> > hands;
    std::array<int, 10> npair = { 0, 1, 1, 5, 2, 4, 3, 8, 3, 9 }; //no pair
    hands.push_back(npair);
    std::array<int, 10> pair = { 0, 1, 1, 1, 2, 2, 3, 3, 3, 4 }; //pair
    hands.push_back(pair);
    std::array<int, 10> pair2 = { 0, 1, 1, 1, 2, 2, 3, 2, 3, 4 }; //2 pair
    hands.push_back(pair2);
    std::array<int, 10> k3 = { 0, 1, 1, 1, 2, 1, 3, 2, 3, 4 }; //3 kind
    hands.push_back(k3);
    std::array<int, 10> strt = { 0, 1, 0, 2, 1, 3, 2, 4, 3, 5 }; //straight
    hands.push_back(strt);
    std::array<int, 10> flush = { 0, 1, 0, 5, 0, 6, 0, 2, 0, 9 }; //flush
    hands.push_back(flush);
    std::array<int, 10> fh = { 1, 1, 1, 1, 1, 4, 2, 4, 3, 4 }; //fullhouse
    hands.push_back(fh);
    std::array<int, 10> k4 = { 0, 1, 1, 1, 2, 1, 3, 1, 3, 4 }; //4kind
    hands.push_back(k4);
    std::array<int, 10> strtflush = { 0, 1, 0, 2, 0, 3, 0, 4, 0, 5 }; //straight flush
    hands.push_back(strtflush);
    std::array<int, 10> royal = { 0, 1, 0, 10, 0, 11, 0, 12, 0, 13 }; //royal
    hands.push_back(royal);
    std::array<int, 10> royal2 = { 1, 1, 1, 10, 1, 11, 1, 12, 1, 13 }; //royal 2
    hands.push_back(royal2);
    std::array<int, 10> royal3 = { 2, 1, 2, 10, 2, 11, 2, 12, 2, 13 }; //royal 3
    hands.push_back(royal3);
    std::array<int, 10> royal4 = { 3, 1, 3, 10, 3, 11, 3, 12, 3, 13 }; //royal 4
    hands.push_back(royal4);

    for (std::vector<std::array<int, 10>>::iterator it = hands.begin(); it != hands.end(); ++it) {
        Hand test = Hand(*it);
        hands_++;
        if (test.type() != HandType::None)
            std::cout << test.readable() << " contains a " << s.typeToString(test.type()) << std::endl;
        else
            std::cout << test.readable() << " doesn't contain valid hand" << std::endl;
    }

    std::cout << "Hands Drawn: " << hands_ << " Decks drawn: " << d.getDecks() << std::endl;
}
void debugVariableHands() {
    int count = 0;
    std::cout << "Enter number of hands: ";
    std::cin >> count;

    Deck d;
    Stats s;

    for (int i = 0; i <= count; ++i) {
        Hand h = d.dealHand();
        s.increment(h.type());
    }
    s.printHands();
    if (s.allHandsFound())
        std::cout << "All hands have been found." << std::endl;
    else 
        std::cout << "Missing some hands, luck is not in your favor." << std::endl;
}
void debug250000Hands() {
    Deck d;
    Stats s;
    std::cout << "Drawing 250k hands..." << std::endl;
    for (int i = 0; i <= 250000; ++i) {
        Hand h = d.dealHand();
        s.increment(h.type());
    }
    s.printHands();
    if (s.allHandsFound())
        std::cout << "All hands have been found." << std::endl;
    else
        std::cout << "Missing some hands, luck is not in your favor." << std::endl;
}
void debugFindAllHands() {
    Deck d;
    Stats s;
    int count = 0;
    s.printHeader();
    do {
        Hand h = d.dealHand();
        s.increment(h.type());
        count++;
    } while (!s.allHandsFound());
    s.printHands();
    s.printFooter();
}