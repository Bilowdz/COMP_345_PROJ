//
// Created by Main on 2021-09-29.
//

#include "Deck.h"

Deck::Deck(){

};

Deck::Deck(int numPlayers){
    for(int i = 0; i < numPlayers; i++)
    {
        cardsHeld.push_back(new Card("Bomb"));
        cardsHeld.push_back(new Card("Reinforcement"));
        cardsHeld.push_back(new Card("Blockade"));
        cardsHeld.push_back(new Card("Airlift"));
        cardsHeld.push_back(new Card("Diplomacy"));
    }
};