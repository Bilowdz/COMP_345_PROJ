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
};


class Deck {
public:
    std::vector<Card*> cardsHeld;
    Deck();
    Deck(int numPlayers);
    void ReceiveCard(Card *c);
    void Draw(Hand *playerHand);
    static void showCards(Deck *showDeck);
};

class Hand {
public:
    std::vector<Card*> cardsHeld;
    Hand();
    void ReceiveCard(Card *c);
    void Play(Deck *mainDeck);
    static void ShowHandCards(Hand *showHand);
};

#endif //COMP_345_PROJ_CARD_H
