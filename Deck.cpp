//
// Created by Main on 2021-09-29.
//

#include "Deck.h"

Deck::Deck(){

};

Deck::Deck(int numPlayers){
    for(int i = 0; i < numPlayers; i++)
    {
        cardsHeld.push_back(new Card((string *) "Bomb"));
        cardsHeld.push_back(new Card((string *) "Reinforcement"));
        cardsHeld.push_back(new Card((string *) "Blockade"));
        cardsHeld.push_back(new Card((string *) "Airlift"));
        cardsHeld.push_back(new Card((string *) "Diplomacy"));
    }
};

void Deck::ReceiveCard(Card *c)
{
    cardsHeld.push_back(c);
}

void Deck::Deal(Deck *otherDeck[])
{

}