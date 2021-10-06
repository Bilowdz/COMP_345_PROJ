//
// Created by Ryan on 2021-10-05.
//

#include <iostream>
#include "Hand.h"

Hand::Hand() {
    std::cout<< "Hand constructor" << std::endl;
}

void Hand::ReceiveCard(Card *c) {
    cardsHeld.push_back(c);
}

void Hand::ShowHandCards(Hand *showHand)
{
    for(int i = 0; i < showHand->cardsHeld.size(); i++)
    {
        cout << "The Hand Card " << (i+1) << " is of type " << showHand->cardsHeld.at(i)->getType() << endl;
    }
    cout << "\n\n\n" << endl;
};