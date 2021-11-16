//
// Created by Main on 2021-09-29.
//

#ifndef COMP_345_PROJ_CARD_H
#define COMP_345_PROJ_CARD_H
#include <vector>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include "Orders.h"
using namespace std;

class Hand;

//creating all functions and constructors
class Card {
    public:
        string cardType;
        Card();
        Card(string type);
        Card(Card const  &copyCard);
        string getType() const;
        friend ostream & operator << (ostream &out, const Card &c);
        Card& operator =(const Card &c);
};


class Deck {
public:
    std::vector<Card*> cardsHeld;
    Deck();
    Deck(int numPlayers);
    Deck(Deck const  &copyDeck);
    ~Deck();
    void ReceiveCard(Card *c);
    void Draw(Hand *playerHand);
    friend ostream & operator << (ostream &out, const Deck &showDeck);
    Deck& operator =(const Deck &d);
};

class Hand {
public:
    std::vector<Card*> cardsHeld;
    Hand();
    Hand(vector<Card*> cardsHeld);
    Hand(const Hand &copyHand);
    ~Hand();
    void ReceiveCard(Card *c);
    bool isCardOwned(string playerCardType);
    OrdersList Play(Deck *mainDeck, OrdersList *o);
    friend ostream & operator << (ostream &out, const Hand &showHand);
    Hand& operator = (const Hand &h);
};

#endif //COMP_345_PROJ_CARD_H
