#include "serial_main.h"

int main() {
    /*std::cout << "test" << std::endl;
    Deck test;

    for (int i = 0; i < test.getDeck().size(); ++i) {
        Card c = test.draw();
        std::cout << "Suit: " << c.getSuit() << " Rank: " << c.getRank() << " SIZE: " << test.getDeckSize() << std::endl;
    }*/

    //DEBUG
    Deck d;
    int hands = 0;
    //get 100 hands
    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i){
        Hand h;
        h.createHand(d);
        hands++;
        std::cout << "Hand created: " << h.readableHand() << std::endl;
    }
    
    std::cout << "Hands Drawn: " << hands << " Decks drawn: " << d.getDecks() << std::endl;
    //GUBED
    return 0;
}