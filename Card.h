//
// Created by Main on 2021-09-29.
//

#ifndef COMP_345_PROJ_CARD_H
#define COMP_345_PROJ_CARD_H
#pragma  once
#include <vector>
#include<iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
using namespace std;

class Hand;

//creating all functions and constructors
class Card {
    public:
        string cardType;
        Card();
        Card(string type);
        Card(Card *c);
        string getType() const;
        Card& operator =(const Card &c);
};


class Deck {
public:
    std::vector<Card*> cardsHeld;
    Deck();
    Deck(int numPlayers);
    Deck(Deck *d);
    void ReceiveCard(Card *c);
    void Draw(Hand *playerHand);
    friend ostream & operator << (ostream &out, const Deck &showDeck);
    Deck& operator =(const Deck &d);
};

class Hand {
public:
    std::vector<Card*> cardsHeld;
    Hand();
    Hand(Hand *h);
    void ReceiveCard(Card *c);
    void Play(Deck *mainDeck);
    friend ostream & operator << (ostream &out, const Hand &showHand);
    Hand& operator =(const Hand &h);
};

#endif //COMP_345_PROJ_CARD_H
