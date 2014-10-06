#include "serial_main.h"

int main() {
    //Create stat counting object, and the deck
    Stats s;
    Deck d;

    //Print message to user
    s.printHeader();

    //Start the timer 
    s.start();

    //Perform dealing hand until all hands are found
    do {
        Hand h = d.dealHand();

        //Increment the stats object with the found hand
        s.increment(h.type());
    } while (!s.allHandsFound());

    //Stop the timer and print the information
    s.stop();
    s.printHands();
    s.printFooter();

    //debugHandType(); // deprecated see Hand.cpp line 5
    //debugVariableHands();
    //debug250000Hands();
    //debugFindAllHands();
    return 0;
}

void debugHandType() {
    ////DEBUG
    Deck d;
    Stats s;
    int hands_ = 0;
   
    std::string cards;
    do {
        std::cout << "Suit: Diamond0, Hearts1, Club2, Spade3" << std::endl;
        std::cout << "Rank: Ace0/a, 1-10, Jack11/j, Queen12/q, King13/k, Ace14/a" << std::endl;
        std::cout << "Enter hand (" << Card::HAND_SIZE << ") cards - 0 to quit:";
        std::cin >> cards;

        Hand h = cards;

        if (h.type() != Hand::None) {
            std::cout << "Hand entered: " << cards;
            std::cout << "Hand parsed: " << h.readable();
            std::cout << "Hand type: " << h.type();
        }
    } while (cards != "0");
    
    std::cout << "Hands Drawn: " << hands_ << " Decks drawn: " << d.getDecks() << std::endl;
}
void debugVariableHands() {
    int count = 0;
    do {
        count = 0;
        std::cout << "Enter number of hands (0 to quit): ";
        std::cin >> count;
        std::vector<double> t;

        Deck d;
        Stats s;
        for (int i = 0; i <= count; ++i) {
            s.start();
            Hand h = d.dealHand();
            s.increment(h.type());
            s.stop();
            t.push_back(s.getClock());
        }
        s.printHands();

        double totaltime = 0.0;
        for (std::vector<double>::iterator it = t.begin(); it != t.end(); ++it) {
            totaltime += *it;
        }
        std::cout << "Average time per hand:\t" << totaltime / t.size() << std::endl;
        std::cout << "Total time:\t" << totaltime << std::endl;

        if (s.allHandsFound())
            std::cout << "All hands have been found.\n" << std::endl;
        else
            std::cout << "Missing some hands, luck is not in your favor.\n" << std::endl;
    } while (count > 0);
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
    s.start();
    do {
        Hand h = d.dealHand();
        s.increment(h.type());
        count++;
    } while (!s.allHandsFound());
    s.stop();
    s.printHands();
    s.printFooter();
}