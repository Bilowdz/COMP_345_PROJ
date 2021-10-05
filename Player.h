//
// Created by Ryan on 2021-09-24.
//

#include <iostream>
#include <vector>
#include <string>
#include "Territory.h"
#include "Order.h"

using namespace std;

#ifndef COMP_345_PROJ_PLAYER_H
#define COMP_345_PROJ_PLAYER_H


class Player {
public:

    string name;

    Player(); //default constructor
    Player(string *name);

    //todo Add the hand that the player will have when cards are given to him
    //Player(string *name, vector<Territory*>);

    vector<Territory> *toDefend(vector<Territory>);

    vector<Territory> *toAttack(vector<Territory>);

    vector<Order> *issueOrder(Player);

    string getName() const;

    void setName(string);


private:
    //const string player = "Player";
    //static int playerNumber;
};


#endif //COMP_345_PROJ_PLAYER_H
