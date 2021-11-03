//
// Created by Ryan on 2021-09-24.
//

#include "Player.h"

/**
* Default Constructor
*/
Player::Player() = default;

/**
 * Constructor that only takes in a name pointer
 * @param name pointer for the name of the player
 */
Player::Player(string *name) {
    this->name = *name;
}

/**
* Constructor that takes in the following parameters
*
* @param vTerritories is the vector Territory pointer of all the territories the player owns
* @param vHand is the vector Hand pointer of all the hand the player owns
* @param vOrder is the vector Order pointer of all the orders the player can do
*/
Player::Player(vector<Territory *> vTerritories) {
    this->vTerritory = vTerritories;
}

/**
 * Constructor that takes in the following parameters
 *
 * @param name is the name of the player
 * @param vTerritories is the vector Territory pointer of all the territories the player owns
 * @param vHand is the vector Hand pointer of all the hand the player owns
 * @param vOrder is the vector Order pointer of all the orders the player can do
 */
Player::Player(string *name, vector<Territory *> vTerritories) {
    (*this).name = *name;
    this->vTerritory = vTerritories;
}

/**
 * Copy constructor
 *
 * @param copyPlayer is the Class we would like to copy
 */
Player::Player(Player const &copyPlayer) {
    name = copyPlayer.name;
    vTerritory = copyPlayer.vTerritory;
}

Player &Player::operator=(const Player &p) {

    this->name = p.name;
    this->vTerritory = p.vTerritory;

    return *this;
}

/**
 * Destructor
 */
Player::~Player() {
    for (auto &i: vTerritory) {
        delete i;
    }
}

/**
 * Ostream operator to output territory, hand and order of each player
 *
 * @param output operator
 * @param player is the player we are currently looking at
 * @return the output to the terminal
 */
ostream &operator<<(ostream &output, Player &player) {

    output << "Player Name: " << player.getName() << endl;
    cout << "Territories Owned: \n";
    for (int j = 0; j < player.getTerritorySize(); ++j) {
        cout << "\t" + player.getTerritoriesOwned(j) << endl;
    }
    cout << "Cards Owned: \n";
    for (int k = 0; k < player.getHandSize(); ++k) {
        cout << "\tCard Number: " + to_string(player.getCardsOwned(k)) << endl;
    }
    cout << "Orders Sent: \n";
    for (int l = 0; l < player.getNumberOfOrders(); ++l) {
        cout << "\t" + player.getOrder(l) << " " + to_string(l + 1) << endl;
    }
    cout << "Territories to defend: \n";
    player.toDefend();
    cout << "\n";

    return output;
}

/**
 * All the territories that the current player can defend
 */
void Player::toDefend() {
    for (int i = 0; i < vTerritory.size(); ++i) {
        cout << "\t" + vTerritory.at(i)->name << endl;
    }
}

/**
 * All the territories the player can attack
 *
 * @param vPlayer the vector of all Players in the game
 */
void Player::toAttack(vector<Player *> vPlayers) {
    for (int i = 0; i < vPlayers.size(); ++i) {
        //Compare the names of the players
        if (vPlayers.at(i)->getName().compare(name) != 0) {
            for (int j = 0; j < vPlayers.at(i)->getTerritorySize(); ++j) {
                cout << "\t" + vPlayers.at(i)->vTerritory.at(j)->name << endl;
            }
        }
    }
}

/**
 * The order the player would like to do
 *
 * @param order string the player wants to do
 */
void Player::issueOrder(string sOrder) {

}

/**
 * Set the territories that the player owns
 *
 * @param vTerritories vector Territory that gets passed in
 */
void Player::setTerritoriesOwned(vector<Territory *> vTerritories) {
    vTerritory = vTerritories;
}

/**
 * Gets all the territories the current player owns.
 *
 * @param vIndex is the current territory from the list of territories
 * @return the name of the territory
 */
string Player::getTerritoriesOwned(int vIndex) {
    return vTerritory.at(vIndex)->name;
}

/**
 * Gets the size of all the territories the player owns
 *
 * @return an int of the size
 */
int Player::getTerritorySize() const {
    return vTerritory.size();
}

/**
 * Gets the number of cards the player has in its hand
 *
 * @param vIndex the current card from the list of Hands
 * @return the number of the current card
 */
int Player::getCardsOwned(int vIndex) {
    return 0;
}

/**
 * Gets the number of cards in the players hand
 *
 * @return the int for amount of cards
 */
int Player::getHandSize() const {
    return 0;
}

/**
 * Gets the order from the vector Order list.
 *
 * @param vIndex the current index of the order
 * @return the name of the order
 */
string Player::getOrder(int vIndex) {
    return "";
}

/**
 * Indicated the amount of orders the player can do
 *
 * @return an int of the amount of orders
 */
int Player::getNumberOfOrders() const {
    return 0;
}

/**
 * Gets the name of the current player
 *
 * @return the name of the player
 */
string Player::getName() const {
    //same as (*this).name
    return this->name;
}

/**
 * Sets the name of the player
 */
void Player::setName(string s) {
    this->name = std::move(s);
}













