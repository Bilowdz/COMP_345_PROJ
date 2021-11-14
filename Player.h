//
// Created by Ryan on 2021-09-24.
//

#ifndef COMP_345_PROJ_PLAYER_H
#define COMP_345_PROJ_PLAYER_H

#include <iostream>
#include <vector>
#include <string>
#include "Map.h"
#include "Card.h"
#include "Orders.h"


using namespace std;


class Player {
public:
    /**
     * Default Constructor
     */
    Player();

    /**
     * Constructor that only takes in a name pointer
     * @param name pointer for the name of the player
     */
    explicit Player(string *name);

    /**
    * Constructor that takes in the following parameters
    *
    * @param vTerritories is the vector Territory pointer of all the territories the player owns
    * @param vHand is the vector Hand pointer of all the hand the player owns
    * @param vOrder is the vector Order pointer of all the orders the player can do
    */
<<<<<<< HEAD
    Player(vector<Territory *> vTerritories, vector<Hand *> vHand, OrdersList * vOrder);
=======
    Player(vector<Territory *> vTerritories, Hand * vHand, vector<Order *> vOrder);
>>>>>>> commandProcessingMergedStartupPhase

    /**
     * Constructor that takes in the following parameters
     *
     * @param name is the name of the player
     * @param vTerritories is the vector Territory pointer of all the territories the player owns
     * @param vHand is the vector Hand pointer of all the hand the player owns
     * @param vOrder is the vector Order pointer of all the orders the player can do
     */
<<<<<<< HEAD
    Player(string *name, vector<Territory *> vTerritories, vector<Hand *> vHand, OrdersList * vOrder);
=======
    Player(string *name, vector<Territory *> vTerritories, Hand * vHand, vector<Order *> vOrder);
>>>>>>> commandProcessingMergedStartupPhase

    /**
     * Copy constructor
     *
     * @param copyPlayer is the Class we would like to copy
     */
    Player(const Player &copyPlayer);

    /**
     * Assignment operator
     *
     * @param p constant player class
     * @return address of Player.
     */
    Player & operator = (const Player &p);

    /**
     * Destructor
     */
    ~Player();

    /**
     * Ostream operator to output territory, hand and order of each player
     *
     * @param output operator
     * @param player is the player we are currently looking at
     * @return the output to the terminal
     */
    friend ostream &operator<<(ostream &output, Player &player);

    /**
     * All the territories that the current player can defend
     */
    void toDefend();

    /**
     * All the territories the player can attack
     *
     * @param vPlayer the vector of all Players in the game
     */
    void toAttack(vector<Player *> vPlayer);

    /**
     * The order the player would like to do
     *
     * @param order string the player wants to do
     */
    void issueOrder();

    /**
     * Set the territories that the player owns
     *
     * @param vTerritories vector Territory that gets passed in
     */
    void setTerritoriesOwned(vector<Territory *> vTerritories);

    void addTerritory(Territory * territory);

    /**
     * Gets all the territories the current player owns.
     *
     * @param vIndex is the current territory from the list of territories
     * @return the name of the territory
     */
    Territory * getTerritoriesOwned(int vIndex);

    /**
     * Gets the size of all the territories the player owns
     *
     * @return an int of the size
     */
    int getTerritorySize() const;

    /**
     * Gets the number of cards the player has in its hand
     *
     * @param vIndex the current card from the list of Hands
     * @return the number of the current card
     */
    int getCardsOwned(int vIndex);

    /**
     * Gets the number of cards in the players hand
     *
     * @return the int for amount of cards
     */
    int getHandSize() const;

    /**
     * Gets the order from the vector Order list.
     *
     * @param vIndex the current index of the order
     * @return the name of the order
     */
    Orders* getOrder(int vIndex);

    /**
     * Indicated the amount of orders the player can do
     *
     * @return an int of the amount of orders
     */
    int getNumberOfOrders() const;

    /**
     * Gets the name of the current player
     *
     * @return the name of the player
     */
    string getName() const;

    /**
     * Sets the name of the player
     *
     * @param s
     */
    void setName(string s);

<<<<<<< HEAD
    void setReinforcements(int armies);

    int getReinforcements();
    Territory * isOwnedTerritory(int id);
    void displayTerritoriesOwned();

private:
    string name; //Name of the player
    vector<Territory *> vTerritory; //Vector of all the territories owned
    vector<Hand *> vHand; //Vector of all the cards the player owns
    OrdersList * ordersList; //Vector for all the orders the player can do
    int reinforcements;
=======
    vector<Territory *> vTerritory; //Vector of all the territories owned
    Hand * vHand; //Vector of all the cards the player owns

private:
    string name; //Name of the player
    vector<Order *> vOrder; //Vector for all the orders the player can do
>>>>>>> commandProcessingMergedStartupPhase
};

#endif //COMP_345_PROJ_PLAYER_H
