#include "serial_main.h"

int main() {
    //DEBUG
    Deck d;
    int hands = 0;
    //get 100 hands
    /*int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i){
        Hand h = Hand(d);
        hands++;
        std::cout << "Hand created: " << h.readable() << std::endl;
    }*/
    Hand h;
    do {
        h.create(d);
        hands++;
    } while (h.type() != d.Flush);
    std::string sdds = h.readable();

    std::cout << "Flush hand: " << h.readable() << std::endl;
    std::cout << "Hands Drawn: " << hands << " Decks drawn: " << d.getDecks() << std::endl;
    //GUBED
    return 0;
}