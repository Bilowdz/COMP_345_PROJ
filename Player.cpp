//
// Created by Ryan on 2021-09-24.
//

#include "Player.h"

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

Player::Player(Player const &copyPlayer) {
    name = copyPlayer.name;
    vTerritory = copyPlayer.vTerritory;
    vHand = copyPlayer.vHand;
    vOrder = copyPlayer.vOrder;
}


void Player::toDefend() {
    for (int i = 0; i < vTerritory.size(); ++i) {
        cout << "\t" + vTerritory.at(i)->getName() << endl;
    }
}

void Player::toAttack(vector<Player *> vPlayers) {
    for (int i = 0; i < vPlayers.size(); ++i) {
        //Compare the names of the players
        if (vPlayers.at(i)->getName().compare(name) != 0) {
            for (int j = 0; j < vPlayers.at(i)->getTerritorySize(); ++j) {
                cout << "\t" + vPlayers.at(i)->vTerritory.at(j)->getName() << endl;
            }
        }
    }
}

void Player::issueOrder(string sOrder) {
    auto *pOrder = new Order(std::move(sOrder));
    vOrder.push_back(pOrder);
}


string Player::getName() const {
    //same as (*this).name
    return this->name;
}

void Player::setName(string s) {
    //same as (*this).name = s;
    this->name = s;
}

string Player::getTerritoriesOwned(int vIndex) {
    return vTerritory.at(vIndex)->getName();
}

void Player::setTerritoriesOwned(vector<Territory *> vTerritories) {
    vTerritory = vTerritories;
}

int Player::getCardsOwned(int vIndex) {
    return vHand.at(vIndex)->getCardNumber();
}

string Player::getOrder(int vIndex) {
    return vOrder.at(vIndex)->getOrder();
}

int Player::getTerritorySize() const {
    return vTerritory.size();
}

int Player::getNumberOfOrders() const {
    return vOrder.size();
}







