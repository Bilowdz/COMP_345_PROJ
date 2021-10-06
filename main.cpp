#include <iostream>

#include "Deck.h"
#include "Hand.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    Deck* TestDeck = new Deck(5);
    Hand* TestHand = new Hand();
    Deck::showCards(TestDeck);
    TestDeck->Deal(TestHand);
    Deck::showCards(TestDeck);
    Hand::ShowHandCards(TestHand);
    return 0;
}
