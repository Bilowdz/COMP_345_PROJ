//
// Created by Main on 2021-09-29.
//
#include <iostream>
#include "Card.h"

int main() {
    Deck* TestDeck = new Deck(3);
    Hand* TestHand = new Hand();
    cout <<  *TestDeck << endl;
    TestDeck->Draw(TestHand);
    TestDeck->Draw(TestHand);
    TestDeck->Draw(TestHand);
    cout <<  *TestDeck << endl;
    TestHand->Play(TestDeck);
    cout <<  *TestDeck << endl;
    cout <<  *TestHand << endl;
}
