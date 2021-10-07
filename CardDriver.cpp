//
// Created by Main on 2021-09-29.
//
#include "CardDriver.h"

void CardDriver::testDecks() {
    std::cout << "Hello, World!" << std::endl;
    Deck* TestDeck = new Deck(3);
    Hand* TestHand = new Hand();
    Deck::showCards(TestDeck);
    TestDeck->Draw(TestHand);
    TestDeck->Draw(TestHand);
    Deck::showCards(TestDeck);
    TestHand->Play(TestDeck);
    Deck::showCards(TestDeck);
    Hand::ShowHandCards(TestHand);
}
