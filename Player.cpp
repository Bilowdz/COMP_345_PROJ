//
// Created by Ryan on 2021-09-24.
//

#include "Player.h"

//must have a default constructor for the vector array
Player::Player() {
//     this->name = "Player" + std::to_string(playerNumber);
//     playerNumber++;
}

Player::Player(string name) {
    this->name = name;
}

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

string Player::getName() {
    return this->name;
}

void Player::setName(string s) {
    this->name = s;
}
