//
// Created by Main on 2021-09-29.
//
#include "CardDriver.h"

int main() {
    Deck* TestDeck = new Deck(3);
    Hand* TestHand = new Hand();
    cout <<  *TestDeck << endl;
    TestDeck->Draw(TestHand);
    TestDeck->Draw(TestHand);
    TestHand->Play(TestDeck);
    cout <<  *TestDeck << endl;
    cout <<  *TestHand << endl;
}
