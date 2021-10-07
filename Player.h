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
    Player(); //default constructor
    Player(string *name);
    Player(string *name, vector<Territory*> pTerritories, vector<Hand*> pHand, vector<Order*> pOrder);
    vector<Territory*> toDefend();
    vector<Territory*> toAttack();
    //Player class includes issueOrder method that creates an Order object and places it in the list of orders of the player
    vector<Order*> issueOrder(Player *currentPlayer);
    void setTerritoriesOwned(vector<Territory*> *pTerritories);
    string getTerritoriesOwned(int vIndex);
    int getCardsOwned(int vIndex);
    string getOrder(int vIndex);
    //const does not modify the object.
    string getName() const;
    void setName(string);


private:
    string name;
    vector<Territory*> vTerritory;
    vector<Hand*> vHand;
    vector<Order*> vOrder; //objects that are child to order

};

#endif //COMP_345_PROJ_PLAYER_H
