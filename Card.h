//
// Created by Main on 2021-09-29.
//

#ifndef COMP_345_PROJ_CARD_H
#define COMP_345_PROJ_CARD_H
#include<iostream>
#include <string>
using namespace std;


struct Card {
    public:
        string cardType;
        Card();
        Card(string type);
        string getType();
};


#endif //COMP_345_PROJ_CARD_H
