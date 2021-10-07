//
// Created by Ryan on 2021-09-24.
//

#include <iostream>
#include <vector>
#include <string>
#include "Territory.h"
#include "Order.h"
#include "OrderList.h"
#include "Hand.h"

using namespace std;

#ifndef COMP_345_PROJ_PLAYER_H
#define COMP_345_PROJ_PLAYER_H

//todo add identify to each class.

class Player {
public:
    Player();

    explicit Player(string *name);

    Player(string *name, vector<Territory *> pTerritories, vector<Hand *> pHand, vector<Order *> pOrder);

    //copy constructor
    Player(const Player & copyPlayer);

    void toDefend();

    void toAttack(vector<Player *>);

    void issueOrder(string);

    void setTerritoriesOwned(vector<Territory *> *pTerritories);

    string getTerritoriesOwned(int vIndex);

    int getTerritorySize() const;

    int getCardsOwned(int vIndex);

    string getOrder(int vIndex);

    int getNumberOfOrders() const;

    string getName() const;

    void setName(string);

private:
    string name;
    vector<Territory *> vTerritory;
    vector<Hand *> vHand;
    vector<Order *> vOrder; //objects that are child to order
};

#endif //COMP_345_PROJ_PLAYER_H
