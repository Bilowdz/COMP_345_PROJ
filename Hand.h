//
// Created by Main on 2021-10-05.
//

#ifndef COMP_345_PROJ_HAND_H
#define COMP_345_PROJ_HAND_H
#pragma once
#include <vector>
#include "Card.h"
#include "Deck.h"



class Hand {
public:
    std::vector<Card*> cardsHeld;
    Hand();
    void ReceiveCard(Card *c);
    void Play(Deck *mainDeck);
    static void ShowHandCards(Hand *showHand);
};


#endif //COMP_345_PROJ_HAND_H
