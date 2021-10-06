//
// Created by 14388 on 2021-10-01.
//

#include "Orders.h"
#include <iostream>
#include <vector>
using namespace std;

//------------------------------------------------------
// OrdersList functions
//------------------------------------------------------

/**
 * Adds a Deploy object to a list of Order objects
 * @param deploy Is the Deploy object to add to the list of Order objects
 */
void OrdersList::addDeploy(Deploy * deploy) {
    this->ordersList.push_back(deploy);
    cout << "Deploy order added." << endl;
}

/**
 * Adds a Advance object to a list of Order objects
 * @param advance Is the Advance object to add to the list of Order objects
 */
void OrdersList::addAdvance(Advance * advance) {
    this->ordersList.push_back(advance);
    cout << "Advance order added." << endl;
}

void OrdersList::addBomb(Bomb * bomb) {
    this->ordersList.push_back(bomb);
    cout << "Bomb order added." << endl;
}
void OrdersList::addBlockade(Blockade * blockade) {
    this->ordersList.push_back(blockade);
    cout << "Blockade order added." << endl;
}
void OrdersList::addAirlift(Airlift * airlift) {
    this->ordersList.push_back(airlift);
    cout << "Airlift order added." << endl;
}
void OrdersList::addNegotiate(Negotiate * negotiate) {
    this->ordersList.push_back(negotiate);
    cout << "Negotiate order added." << endl;
}

OrdersList::OrdersList() {
    cout << "OrdersList is being created." << endl;
}

std::vector<Orders*> OrdersList::getList(){
    return this->ordersList;
}

//getter
void OrdersList::getListMember(int index) {
    this->ordersList.at(index)->identify();
}

void OrdersList::move(int indexFrom, int indexTo) {
    this->ordersList.insert(ordersList.begin()+indexTo, this->ordersList[indexFrom]);
    this->ordersList.erase(ordersList.begin()+indexFrom+1);
}


void OrdersList::remove(int index) {
    this->ordersList.erase(ordersList.begin()+index);
}

//------------------------------------------------------
// Orders functions
//------------------------------------------------------

void Orders::identify() {
    std::cout << "Orders object: ";
}
void Orders::validate() {
    std::cout << "Orders validate method.";
}

//------------------------------------------------------
// Deploy functions
//------------------------------------------------------

void Deploy::setArmies(int sArmies) {
    this->armies = sArmies;
}

int Deploy::getArmies() const {
    return this->armies;
}

void Deploy::validate() {
    // validate if player has enough armies
    std::cout << "How many armies does the current player own?";
    int totalArmies;
    std::cin >> totalArmies;
    if (this->getArmies() <= totalArmies) {
        // validate if territory is owned by current player
        std::cout << "Great! Is the territory deployed to owned by the current player? (1 for yes, 0 for no)";
        int ownedTerritory;
        std::cin >> ownedTerritory;
        if (ownedTerritory >= 1) {
            // deploy vArmies
            std::cout << "Deploying armies!\n";
            Deploy::execute();
        } else {
            // refuse to deploy vArmies
            std::cout << "Territory not owned by current player, cannot deploy armies.\n";
        }
    } else {
        // refuse to deploy vArmies
        std::cout << "Not enough armies available for this deployment.\n";
    }
}

void Deploy::execute() {
    std::cout << "\nDeploy executed.\n";
}

void Deploy::identify() {
    Orders::identify();
    std::cout << "Deploy object. Can deploy armies to territories. It has " << this->getArmies() << " armies.\n";
}

//------------------------------------------------------
// Advance functions
//------------------------------------------------------

void Advance::setArmies(int sArmies) {
    this->armies = sArmies;
}

int Advance::getArmies() const {
    return this->armies;
}

void Advance::validate() {
    // validate if player has enough armies
    std::cout << "How many armies does the current player own?";
    int totalArmies;
    std::cin >> totalArmies;
    if (this->getArmies() <= totalArmies) {
        Advance::execute();
    } else {
        // refuse to deploy vArmies
        std::cout << "Not enough armies available for this advancement.\n";
    }
}

void Advance::execute() {
    // check if enemy territory is owned by current player or not

    std::cout << "Is the territory destination adjacent to a territory of the current player? (1 for yes, 0 for no)";
    int adjacentTerritory;
    std::cin >> adjacentTerritory;
    if (adjacentTerritory >= 1) {
        std::cout << "Is the territory destination owned by the current player? (1 for yes, 0 for no)";
        int ownedTerritory;
        std::cin >> ownedTerritory;
        if (ownedTerritory >= 1) {
            std::cout << "Advancing armies to an owned territory.\n";
        } else {
            std::cout << "Advancing armies to enemy territory. Time for battle!\n";
        }
    } else {
        std::cout << "Territory is not adjacent, therefore cannot move armies to it.\n";
    }
}

void Advance::identify() {
    Orders::identify();
    std::cout << "Advance object. Can deploy armies to territories owned. It has " << this->getArmies() << " armies.\n";
}

//------------------------------------------------------
// Bomb functions
//------------------------------------------------------

void Bomb::validate() {
    std::cout << "Is the territory being bombed an enemy territory that is adjacent to a territory owned by the current player? (1 for yes, 0 for no)";
    int adjacentTerritory;
    std::cin >> adjacentTerritory;
    if (adjacentTerritory >= 1) {
        Bomb::execute();
    } else {
        std::cout << "Cannot bomb territory.\n";
    }
}

void Bomb::execute() {
    std::cout << "Bombing half the enemy armies!\n";
}

void Bomb::identify() {
    Orders::identify();
    std::cout << "Bomb object. Can eliminate half of the armies located on an opponent's territory that is adjacent to one of the current player's territories.\n";
}

//------------------------------------------------------
// Blockade functions
//------------------------------------------------------

void Blockade::validate() {
    std::cout << "Is the territory being blockaded owned by the current player? (1 for yes, 0 for no)";
    int blockade;
    std::cin >> blockade;
    if (blockade >= 1) {
        Blockade::execute();
    } else {
        std::cout << "Cannot blockade territory.\n";
    }
}

void Blockade::execute() {
    std::cout << "Territory blockade set up! Territory lost.\n";
}

void Blockade::identify() {
    Orders::identify();
    std::cout << "Blockade object. Can triple the number of armies on one of the current player's territory and make it a neutral territory.\n";
}

//------------------------------------------------------
// Airlift functions
//------------------------------------------------------

void Airlift::validate() {
    std::cout << "Is starting territory owned by player? (1 for yes, 0 for no)";
    int airlift;
    std::cin >> airlift;
    if (airlift >= 1) {
        Airlift::execute();
    } else {
        std::cout << "Cannot take armies from this location!\n";
    }
}

void Airlift::execute() {
    std::cout << "Airlifting armies to destination.\n";
}

void Airlift::identify() {
    Orders::identify();
    std::cout << "Airlift object. Can advance some armies from one of the current player's territories to any other territory.\n";
}

//------------------------------------------------------
// Negotiate functions
//------------------------------------------------------

void Negotiate::validate() {
    std::cout << "Validating if negotiate can happen between the two selected players...\n";
    Negotiate::execute();
}

void Negotiate::execute() {
    std::cout << "Negotiate active between the two selected players.\n";
}

void Negotiate::identify() {
    Orders::identify();
    std::cout << "Negotiate object. Can prevent attacks between the current player and another player until the end of the turn. \n";
}
