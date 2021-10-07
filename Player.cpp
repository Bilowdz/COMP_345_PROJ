//
// Created by Ryan on 2021-09-24.
//

#include "Player.h"

//must have a default constructor for the vector array
Player::Player() {

}

Player::Player(string *name) {
    this->name = *name;
}

Player::Player(string *name, vector<Territory *> pTerritories, vector<Hand *> pHand, vector<Order *> pOrder) {
    (*this).name = *name;
    this->vTerritory = pTerritories;
    this->vHand = pHand;
    this->vOrder = pOrder;
}


vector<Territory*> Player::toDefend() {

    return vTerritory;
}

vector<Territory*> Player::toAttack() {

    return vTerritory;
}

vector<Order*> Player::issueOrder(Player *currentPlayer) {
    Order *newOrder;
    vOrder.push_back(newOrder);
    return vOrder;
}



string Player::getName() const{
    //same as (*this).name
    return this->name;
}

void Player::setName(string s) {
    //same as (*this).name = s;
    this->name = s;
}

string Player::getTerritoriesOwned(int vIndex) {
    //for (int i = 0; i < vTerritory.size(); ++i) {
    return vTerritory.at(vIndex)->getName();
    //}
}

void Player::setTerritoriesOwned(vector<Territory *> *pTerritories) {
    vTerritory = *pTerritories;
}

int Player::getCardsOwned(int vIndex) {
    return vHand.at(vIndex)->getCardNumber();
}

string Player::getOrder(int vIndex) {
    return vOrder.at(vIndex)->getOrder();
}




