//
// Created by Main on 2021-09-29.
//

#include "Card.h"

Card::Card(){
    cout << "No Type specified please try again" << endl;
}

Card::Card(string* t) : cardType(*t){
}

string Card::getType(){
    return type;
}