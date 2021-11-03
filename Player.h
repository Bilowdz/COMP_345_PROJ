//
// Created by Ryan on 2021-09-24.
//

#include <iostream>
#include <vector>
#include <string>
#include "Map.h"

using namespace std;

#ifndef COMP_345_PROJ_PLAYER_H
#define COMP_345_PROJ_PLAYER_H

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
    Player(vector<Territory *> vTerritories);

    /**
     * Constructor that takes in the following parameters
     *
     * @param name is the name of the player
     * @param vTerritories is the vector Territory pointer of all the territories the player owns
     * @param vHand is the vector Hand pointer of all the hand the player owns
     * @param vOrder is the vector Order pointer of all the orders the player can do
     */
    Player(string *name, vector<Territory *> vTerritories);

    /**
     * Copy constructor
     *
     * @param copyPlayer is the Class we would like to copy
     */
    Player(const Player &copyPlayer);

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
    void issueOrder(string order);

    /**
     * Set the territories that the player owns
     *
     * @param vTerritories vector Territory that gets passed in
     */
    void setTerritoriesOwned(vector<Territory *> vTerritories);

    /**
     * Gets all the territories the current player owns.
     *
     * @param vIndex is the current territory from the list of territories
     * @return the name of the territory
     */
    string getTerritoriesOwned(int vIndex);

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
    string getOrder(int vIndex);

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
     */
    void setName(string);

private:
    string name; //Name of the player
    vector<Territory *> vTerritory; //Vector of all the territories owned
};

#endif //COMP_345_PROJ_PLAYER_H