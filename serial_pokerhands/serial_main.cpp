#include "serial_main.h"

int main() {
    /*std::cout << "test" << std::endl;
    Deck test;

    for (int i = 0; i < test.getDeck().size(); ++i) {
        Card c = test.draw();
        std::cout << "Suit: " << c.getSuit() << " Rank: " << c.getRank() << " SIZE: " << test.getDeckSize() << std::endl;
    }*/

    Deck d;
    int hands = 0;
    //get 100 hands
    std::cin;
    for (int i = 0; i < 1000; ++i){
        Hand h;
        h.createHand(d);
        hands++;
        std::cout << "Hand created: " << h.test << std::endl;
    }
    
    return 0;
}