#include <iostream>

#include "Deck.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    Deck* TestDeck = new Deck(5);
    TestDeck->showCards();
    return 0;
}
