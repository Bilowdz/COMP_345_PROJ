//
// Created by 14388 on 2021-10-01.
//

#include "Orders.h"
#include <iostream>
#include <vector>

//------------------------------------------------------
// OrdersList functions
//------------------------------------------------------

// constructor
OrdersList::OrdersList(std::vector<Orders> ordersList) {
    for (int i = 0; i < ordersList.size(); ++i) {
        setListMember(ordersList[i]);
    }
}

// setter
void OrdersList::setListMember(Orders order) {
    this->ordersList.push_back(order);
}

// getter
std::vector<Orders> OrdersList::getList() {
    return this->ordersList;
}

//-----------------------------------------------------------------------------------------------------------------------------------------

void OrdersList::addDeploy(Deploy addDeploy, std::vector<Orders> ordersList) {
    if (typeid(addDeploy) == typeid(Deploy)){
        std::cout << "orderToAdd is an instance of Deploy\n";

    } else {
        std::cout << "orderToAdd is NOT an instance of Deploy\n";
    }
}
void OrdersList::move(int index) {

}

//------------------------------------------------------
// Orders functions
//------------------------------------------------------

void Orders::toString() {
    if (Deploy* d = dynamic_cast<Deploy*>(this)) {
        Deploy::toString();
    }
        std::cout << "This is an Orders object\n";
}

void Deploy::deployArmies(int armies) {
    // validate that territory is owned by current player and player has enough armies
    Deploy::validate(armies);
}

void Deploy::validate(int armies) {
    // validate if player has enough armies
    std::cout << "How many armies does the current player own?";
    int totalArmies;
    std::cin >> totalArmies;
    if (armies <= totalArmies) {
        // validate if territory is owned by current player
        std::cout << "Great! Is the territory deployed to owned by the current player? (1 for yes, 0 for no)";
        int ownedTerritory;
        std::cin >> ownedTerritory;
        if (ownedTerritory >= 1) {
            // deploy armies
            std::cout << "Deploying armies!";
            Deploy::execute();
        } else {
            // refuse to deploy armies
            std::cout << "Territory not owned by current player, cannot deploy armies.";
        }
    } else {
        // refuse to deploy armies
        std::cout << "Not enough armies available for this deployment.";
    }
}

void Deploy::execute() {
    std::cout << "Deploy executed.";
}

void Deploy::toString() {
    std::cout << "This is a deploy object\n";
}

void Deploy::setArmies(int armies) {
    Deploy::armies = armies;
}

Deploy::Deploy(int armies) {
    Deploy::setArmies(armies);
}
