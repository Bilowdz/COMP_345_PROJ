//
// Created by Main on 2021-09-29.
//

#ifndef COMP_345_PROJ_DECK_H
#define COMP_345_PROJ_DECK_H
#include <vector>
#include "Card.cpp"

class Deck {
    public:
        std::vector<Card*> cardsHeld;
    Deck();
    Deck(int numPlayers);
    void Deal(Deck otherDeck[]);
    void Play(Deck otherDeck, string ct);
};


#endif //COMP_345_PROJ_DECK_H
