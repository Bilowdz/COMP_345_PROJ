//
// Created by Main on 2021-09-29.
//

#ifndef COMP_345_PROJ_CARD_H
#define COMP_345_PROJ_CARD_H
#pragma  once
#include<iostream>
#include <string>
using namespace std;

//creating all functions and constructors
class Card {
    public:
        string cardType;
        Card();
        Card(string type);
        Card(Card *c);
        string getType() const;
};


#endif //COMP_345_PROJ_CARD_H
