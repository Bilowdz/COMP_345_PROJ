/**
 * Created by: Simon Bilodeau 40130702
 * Due date: Oct 3rd, 2021
 * Class: COMP 345
 * Professor: Joey Paquet
 *
 * Orders.cpp description:
 * This file includes the method descriptions for the following classes:
 * OrdersList, Orders, and subclasses of Orders: Deploy, Advance, Bomb, Blockade, Airlift, Negotiate.
 * The class OrdersList has a vector of Orders objects as its only member. This vector is composed of
 * objects of the subclasses of Orders. These are orders used by the players to order their armies around
 * the map. Each order has a different function for the player, described in its "identify()" method.
 */

#include "Orders.h"
#include <iostream>
#include <vector>
using namespace std;

//------------------------------------------------------
// OrdersList functions
//------------------------------------------------------

ostream &operator << (ostream &out, const OrdersList &ordersList) {
    cout << "OrdersList object. Holds a list of objects that are subclasses to the Orders class. \n";
    return out;
}
std::istream &operator >> (istream &in, const OrdersList &ordersList) {
    return in;
}

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

/**
 * Adds a Bomb object to a list of Order objects
 * @param bomb Is the Bomb object to add to the list of Order objects
 */
void OrdersList::addBomb(Bomb * bomb) {
    this->ordersList.push_back(bomb);
    cout << "Bomb order added." << endl;
}

/**
 * Adds a Blockade object to a list of Order objects
 * @param blockade Is the Blockade object to add to the list of Order objects
 */
void OrdersList::addBlockade(Blockade * blockade) {
    this->ordersList.push_back(blockade);
    cout << "Blockade order added." << endl;
}

/**
 * Adds a Airlift object to a list of Order objects
 * @param airlift Is the Airlift object to add to the list of Order objects
 */
void OrdersList::addAirlift(Airlift * airlift) {
    this->ordersList.push_back(airlift);
    cout << "Airlift order added." << endl;
}

/**
 * Adds a Negotiate object to a list of Order objects
 * @param negotiate Is the Negotiate object to add to the list of Order objects
 */
void OrdersList::addNegotiate(Negotiate * negotiate) {
    this->ordersList.push_back(negotiate);
    cout << "Negotiate order added." << endl;
}

/**
 * OrdersList default constructor
 */
OrdersList::OrdersList() = default;

/**
 * OrdersList destructor
 */
OrdersList::~OrdersList() = default;

/**
 * OrdersList copy constructor
 * @param o1 OrdersList object to be copied
 */
OrdersList::OrdersList(const OrdersList &o1) = default;

/**
 * Returns the list of Order objects from the OrdersList object
 * @return ordersList, the list of Order objects in the OrdersList object
 */
std::vector<Orders*> OrdersList::getList(){
    return this->ordersList;
}

/**
 * To access a single member of the list of Order objects in OrdersList object
 * @param index The index of the object being accessed
 */
void OrdersList::getListMember(int index) {
    this->ordersList.at(index)->identify();
}

/**
 * To move an object from the ordersList from one index to another
 * @param indexFrom The object being moved
 * @param indexTo Where to move the object
 */
void OrdersList::move(int indexFrom, int indexTo) {
    if (indexFrom > indexTo) {
        this->ordersList.insert(ordersList.begin() + indexTo, this->ordersList[indexFrom]);
        this->ordersList.erase(ordersList.begin() + indexFrom + 1);
    } else if (indexFrom < indexTo) {
        this->ordersList.insert(ordersList.begin() + indexTo, this->ordersList[indexFrom]);
        this->ordersList.erase(ordersList.begin() + indexFrom);
    } else {
        std::cout << "Order already there, cancelling move call.\n\n";
    }
}

/**
 * Removes an object from the list of Orders
 * @param index The index of the object being removed
 */
void OrdersList::remove(int index) {
    this->ordersList.erase(ordersList.begin()+index);
}

//------------------------------------------------------
// Orders functions
//------------------------------------------------------

/**
 * Orders default constructor
 */
Orders::Orders() = default;

/**
 * Orders destructor
 */
Orders::~Orders() = default;

/**
 * Orders copy constructor
 * @param o1 Object to be copied
 */
Orders::Orders(const Orders &o1) = default;

/**
 * Orders identify to output a string identifying the object called
 */
void Orders::identify() {
    std::cout << "Orders object: ";
}

ostream &operator << (ostream &out, const Orders &orders) {
    std::cout << "Orders object: ";
    return out;
}
std::istream &operator >> (istream &in, const Orders &orders) {
    std::cout << "Orders object: ";
    return in;
}

/**
 * Orders validate, a placeholder for the validate method of subclasses
 */
void Orders::validate() {
    std::cout << "Orders validate method.";
}

//------------------------------------------------------
// Deploy functions
//------------------------------------------------------

/**
 * Deploy setArmies to change the value of armies in a Deploy object
 * @param sArmies the new number of armies
 */
void Deploy::setArmies(int sArmies) {
    this->armies = sArmies;
}

/**
 * Deploy getArmies to get the number of armies in a Deploy object
 * @return the number of armies in the Deploy object
 */
int Deploy::getArmies() const {
    return this->armies;
}

/**
 * Deploy default constructor
 */
Deploy::Deploy() = default;

/**
 * Deploy destructor
 */
Deploy::~Deploy() = default;

/**
 * Deploy copy constructor
 * @param d1 Deploy object being copied
 */
Deploy::Deploy(const Deploy &d1) {
    this->armies = d1.armies;
}

/**
 * Deploy validate checks if the Deploy object can execute
 */
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

/**
 * Executes a Deploy order
 */
void Deploy::execute() {
    std::cout << "\nDeploy executed.\n";
}

/**
 * Identifies a Deploy object when called
 */
void Deploy::identify() {
    Orders::identify();
    std::cout << "Deploy object. Can deploy armies to territories. It needs " << this->getArmies() << " armies.\n";
}

ostream &operator << (ostream &out, const Deploy &deploy) {
    Orders orders;
    std::cout << orders;
    std::cout << "Deploy object. Can deploy armies to territories. It needs " << deploy.getArmies() << " armies.\n";
    return out;
}
std::istream &operator >> (istream &in, const Deploy &deploy) {
    return in;
}

//------------------------------------------------------
// Advance functions
//------------------------------------------------------

/**
 * Advance setArmies to change the value of armies in a Advance object
 * @param sArmies the new number of armies
 */
void Advance::setArmies(int sArmies) {
    this->armies = sArmies;
}

/**
 * Advance getArmies to get the number of armies in a Advance object
 * @return the number of armies in the Advance object
 */
int Advance::getArmies() const {
    return this->armies;
}

/**
 * Advance default constructor
 */
Advance::Advance() = default;

/**
 * Advance destructor
 */
Advance::~Advance() = default;

/**
 * Advance copy constructor
 * @param a1 Advance object to be copied
 */
Advance::Advance(const Advance &a1) {
    this->armies = a1.armies;
}

/**
 * Advance validate checks if the Advance object can execute
 */
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

/**
 * Executes an Advance order
 */
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

/**
 * Identifies an Advance object when called
 */
void Advance::identify() {
    Orders::identify();
    std::cout << "Advance object. Can advance armies to territories owned. It needs " << this->getArmies() << " armies.\n";
}

ostream &operator << (ostream &out, const Advance &advance) {
    Orders orders;
    std::cout << orders;
    std::cout << "Advance object. Can advance armies to territories. It needs " << advance.getArmies() << " armies.\n";
    return out;
}
std::istream &operator >> (istream &in, const Advance &advance) {
    return in;
}

//------------------------------------------------------
// Bomb functions
//------------------------------------------------------

/**
 * Bomb default constructor
 */
Bomb::Bomb() = default;

/**
 * Bomb destructor
 */
Bomb::~Bomb() = default;

/**
 * Bomb copy constructor
 * @param b1 Bomb object being copied
 */
Bomb::Bomb(const Bomb &b1) {
    // empty because Bomb has no members.
}

/**
 * Bomb validate checks if the Bomb object can execute
 */
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

/**
 * Executes a Bomb order
 */
void Bomb::execute() {
    std::cout << "Bombing half the enemy armies!\n";
}

/**
 * Identifies a Bomb object
 */
void Bomb::identify() {
    Orders::identify();
    std::cout << "Bomb object. Can eliminate half of the armies located on an opponent's territory that is adjacent to one of the current player's territories.\n";
}

ostream &operator << (ostream &out, const Bomb &bomb) {
    Orders orders;
    std::cout << orders;
    std::cout << "Bomb object. Can eliminate half of the armies located on an opponent's territory that is adjacent to one of the current player's territories.\n";
    return out;
}
std::istream &operator >> (istream &in, const Bomb &bomb) {
    return in;
}

//------------------------------------------------------
// Blockade functions
//------------------------------------------------------

/**
 * Blockade default constructor
 */
Blockade::Blockade() = default;

/**
 * Blockade destructor
 */
Blockade::~Blockade() = default;

/**
 * Blockade copy constructor
 * @param b1 Blockade object being copied
 */
Blockade::Blockade(const Blockade &b1) {
    // empty because Blockade has no members.
}

/**
 * Blockade validate checks if the Blockade object can execute
 */
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

/**
 * Executes a Blockade order
 */
void Blockade::execute() {
    std::cout << "Territory blockade set up! Territory lost.\n";
}

/**
 * Identifies a Blockade object
 */
void Blockade::identify() {
    Orders::identify();
    std::cout << "Blockade object. Can triple the number of armies on one of the current player's territory and make it a neutral territory.\n";
}

ostream &operator << (ostream &out, const Blockade &blockade) {
    Orders orders;
    std::cout << orders;
    std::cout << "Blockade object. Can triple the number of armies on one of the current player's territory and make it a neutral territory.\n";
    return out;
}
std::istream &operator >> (istream &in, const Blockade &blockade) {
    return in;
}

//------------------------------------------------------
// Airlift functions
//------------------------------------------------------

/**
 * Airlift default constructor
 */
Airlift::Airlift() = default;

/**
 * Airlift destructor
 */
Airlift::~Airlift() = default;

/**
 * Airlift copy constructor
 * @param a1 Airlift object being copied
 */
Airlift::Airlift(const Airlift &a1) {
    // empty because Airlift has no members.
}

/**
 * Airlift validate checks if the Airlift object can execute
 */
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

/**
 * Executes an Airlift order
 */
void Airlift::execute() {
    std::cout << "Airlifting armies to destination.\n";
}

/**
 * Identifies an Airlift object
 */
void Airlift::identify() {
    Orders::identify();
    std::cout << "Airlift object. Can advance some armies from one of the current player's territories to any other territory.\n";
}

ostream &operator << (ostream &out, const Airlift &airlift) {
    Orders orders;
    std::cout << orders;
    std::cout << "Airlift object. Can advance some armies from one of the current player's territories to any other territory.\n";
    return out;
}
std::istream &operator >> (istream &in, const Airlift &airlift) {
    return in;
}

//------------------------------------------------------
// Negotiate functions
//------------------------------------------------------

/**
 * Negotiate default constructor
 */
Negotiate::Negotiate() = default;

/**
 * Negotiate destructor
 */
Negotiate::~Negotiate() = default;

/**
 * Negotiate copy constructor
 * @param n1 Negotiate object being copied
 */
Negotiate::Negotiate(const Negotiate &n1) {
    // empty because Negotiate has no members.
}

/**
 * Negotiate validate checks if the Negotiate object can execute
 */
void Negotiate::validate() {
    std::cout << "Validating if negotiate can happen between the two selected players...\n";
    Negotiate::execute();
}

/**
 * Executes a Negotiate order
 */
void Negotiate::execute() {
    std::cout << "Negotiate active between the two selected players.\n";
}

/**
 * Identifies a Negotiate object
 */
void Negotiate::identify() {
    Orders::identify();
    std::cout << "Negotiate object. Can prevent attacks between the current player and another player until the end of the turn. \n";
}

ostream &operator << (ostream &out, const Negotiate &negotiate) {
    Orders orders;
    std::cout << orders;
    std::cout << "Negotiate object. Can prevent attacks between the current player and another player until the end of the turn.\n";
    return out;
}
std::istream &operator >> (istream &in, const Negotiate &negotiate) {
    return in;
}
