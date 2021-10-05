//
// Created by Ryan on 2021-09-24.
//

#include "Player.h"

//must have a default constructor for the vector array
Player::Player() {
//     this->name = "Player" + std::to_string(playerNumber);
//     playerNumber++;
//player to chose what countries it has
}

Player::Player(string *name) {
    this->name = *name;
}

//Player::Player(string *name, vector<Territory *> territory) {
//
//}

vector<Territory> *Player::toDefend(vector<Territory> defend) { //might not need these params
    //vector<Territory> territory = NULL;

    return NULL;
}

vector<Territory> *Player::toAttack(vector<Territory> attack) { //might not need these params

    return NULL;
}

vector<Order> *Player::issueOrder(Player currentPlayer) {
    //Order newOrder();
    return NULL;
}

string Player::getName() const{
    //same as (*this).name
    return this->name;
}

void Player::setName(string s) {
    //same as (*this).name = s;
    this->name = s;
}

Player::Player(string *name, vector<Territory *> pTerritories, vector<Hand *> pHand, vector<OrderList *> pOrderList) {

}

