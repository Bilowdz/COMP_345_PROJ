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

OrdersList::OrdersList() {
    cout << "OrdersList is being created." << endl;
}

std::vector<Orders*> OrdersList::getList(){
    return this->ordersList;
}


//OrdersList::OrdersList() : ordersList(NULL) {
//}
// constructor
//OrdersList::OrdersList(Orders *ordersList[]) {
//    this->ordersList;
//}
//
// setter
//void OrdersList::setListMember(Orders *order, int index) {
//    this->ordersList[index] = *order;
//}
//
//getter
void OrdersList::getListMember(int index) {
    cout << "Inside getListMember\n";
    this->ordersList[index]->identify();
}

void OrdersList::move(int indexFrom, int indexTo) {
    this->ordersList.insert(ordersList.begin()+indexTo, this->ordersList[indexFrom]);
    this->ordersList.erase(ordersList.begin()+indexFrom+1);
}


void OrdersList::remove(int index) {
    cout << "Inside remove\n";
    this->ordersList.erase(ordersList.begin()+index);
}


//void OrdersList::toString() {
//    std::cout << "This is an OrdersList object\n";
//}

//-----------------------------------------------------------------------------------------------------------------------------------------

//void OrdersList::addDeploy(Deploy addDeploy, std::vector<Orders> ordersList) {
//    if (typeid(addDeploy) == typeid(Deploy)){
//        std::cout << "orderToAdd is an instance of Deploy\n";
//
//    } else {
//        std::cout << "orderToAdd is NOT an instance of Deploy\n";
//    }
//}
//void OrdersList::move(int index) {
//
//}

//------------------------------------------------------
// Orders functions
//------------------------------------------------------

void Orders::identify() {
        std::cout << "Orders object: ";
}

//void Deploy::deployArmies(int armies) {
//    // validate that territory is owned by current player and player has enough armies
//    Deploy::validate(armies);
//}
//
//void Deploy::validate(int armies) {
//    // validate if player has enough armies
//    std::cout << "How many armies does the current player own?";
//    int totalArmies;
//    std::cin >> totalArmies;
//    if (armies <= totalArmies) {
//        // validate if territory is owned by current player
//        std::cout << "Great! Is the territory deployed to owned by the current player? (1 for yes, 0 for no)";
//        int ownedTerritory;
//        std::cin >> ownedTerritory;
//        if (ownedTerritory >= 1) {
//            // deploy armies
//            std::cout << "Deploying armies!";
//            Deploy::execute();
//        } else {
//            // refuse to deploy armies
//            std::cout << "Territory not owned by current player, cannot deploy armies.";
//        }
//    } else {
//        // refuse to deploy armies
//        std::cout << "Not enough armies available for this deployment.";
//    }
//}
//
//void Deploy::execute() {
//    std::cout << "Deploy executed.";
//}
//
void Deploy::identify() {
    Orders::identify();
    std::cout << "Deploy object. Can deploy armies to territories. It has " << this->getArmies() << " armies.\n";
}

void Deploy::setArmies(int armies) {
    this->armies = armies;
}

int Deploy::getArmies() {
    return this->armies;
}

void Advance::identify() {
    Orders::identify();
    std::cout << "Advance object. Can deploy armies to territories owned. It has " << this->getArmies() << " armies.\n";
}

void Advance::setArmies(int armies) {
    this->armies = armies;
}

int Advance::getArmies() {
    return this->armies;
}
