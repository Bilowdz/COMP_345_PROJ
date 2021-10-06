//
// Created by Main on 2021-09-29.
//

#ifndef COMP_345_PROJ_DECK_H
#define COMP_345_PROJ_DECK_H
#pragma  once

#include <vector>
#include "Card.h"
#include "Hand.h"
#include <stdlib.h>
#include <time.h>


//creating all functions and constructors
class Deck {
    public:
        std::vector<Card*> cardsHeld;
    Deck();
    Deck(int numPlayers);
    void ReceiveCard(Card *c);
    void Deal(Hand *playerHand);
    void Play(Deck otherDeck, string ct);
    static void showCards(Deck *showDeck);
};


#endif //COMP_345_PROJ_DECK_H
