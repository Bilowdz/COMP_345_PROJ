#include <iostream>
#include "Card.h"

void RunCardDriver()
{
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
    delete TestDeck;
    delete TestHand;
}

int main() {
    RunCardDriver();
    return 0;
}
