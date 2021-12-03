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
* @param ordersList is the vector Order pointer of all the orders the player can do
*/
Player::Player(vector<Territory *> vTerritories, Hand *vHand, OrdersList *ordersList) {
    this->vTerritory = vTerritories;
    this->vHand = vHand;
    this->ordersList = ordersList;

}

Player::Player(string *name, vector<Territory *> vTerritories, Hand *vHand, OrdersList *ordersList) {
    (*this).name = *name;
    this->vTerritory = vTerritories;
    this->vHand = vHand;
    this->ordersList = ordersList;
    this->reinforcements = 0;
}

/**
 * Constructor that takes in the following parameters
 *
 * @param name is the name of the player
 * @param vTerritories is the vector Territory pointer of all the territories the player owns
 * @param vHand is the vector Hand pointer of all the hand the player owns
 * @param ordersList is the vector Order pointer of all the orders the player can do
 */
Player::Player(string *name, vector<Territory *> vTerritories, Hand *vHand, OrdersList *ordersList, PlayerStrategy* initStrategy) {
    (*this).name = *name;
    this->vTerritory = vTerritories;
    this->vHand = vHand;
    this->ordersList = ordersList;
    this->reinforcements = 0;
    this->ps = initStrategy;
}

/**
 * Copy constructor
 *
 * @param copyPlayer is the Class we would like to copy
 */
Player::Player(Player const &copyPlayer) {
    name = copyPlayer.name;
    for (int i = 0; i < copyPlayer.vTerritory.size(); i++) {
        vTerritory.at(i) = copyPlayer.vTerritory.at(i);
    }
    for (int i = 0; i < copyPlayer.vHand->cardsHeld.size(); i++) {
        vHand->cardsHeld.at(i) = copyPlayer.vHand->cardsHeld.at(i);
    }
    ordersList = copyPlayer.ordersList;
}

/**
 * Assignment operator
 *
 * @param p constant player class
 * @return address of Player.
 */
Player &Player::operator=(const Player &copyPlayer) {

    this->name = copyPlayer.name;
    for (int i = 0; i < copyPlayer.vTerritory.size(); i++) {
        this->vTerritory.at(i) = copyPlayer.vTerritory.at(i);
    }
    for (int i = 0; i < copyPlayer.vHand->cardsHeld.size(); i++) {
        this->vHand->cardsHeld.at(i) = copyPlayer.vHand->cardsHeld.at(i);
        this->vHand->cardsHeld.at(i) = copyPlayer.vHand->cardsHeld.at(i);
    }
    this->ordersList = copyPlayer.ordersList;
    return *this;
}

/**
 * Destructor
 */
Player::~Player() {
    /*for (auto &i: vTerritory) {
        delete i;
    }
    */
    for (auto &i: vHand->cardsHeld) {
        delete i;
    }
    cout << "Destructor !" << endl;
}

/**
 * Ostream insertion operator to output territory, hand and order of each player
 *
 * @param output operator
 * @param player is the player we are currently looking at
 * @return the output to the terminal
 */
ostream &operator<<(ostream &output, Player &player) {

    output << "Player Name: " << player.getName() << endl;
    output << "Territories Owned: \n";
    for (int j = 0; j < player.getTerritorySize(); j++) {
        // output << "\t" + player.getTerritoriesOwned(j) << endl;
    }
    output << "Cards Owned: \n";
    for (int k = 0; k < player.getHandSize(); k++) {
        output << "\tCard Number: " + to_string(player.getCardsOwned(k)) << endl;
    }
    output << "Orders Sent: \n";

    output << "Territories to defend: \n";
    player.toDefend();
    output << "\n";

    return output;
}

/**
 * Loops through the list of the current players territories and displays them
 */
void Player::displayTerritoriesOwned() {
    for (int i = 0; i < vTerritory.size(); i++) {
        cout << "Name: " << vTerritory.at(i)->name << " ID: " << vTerritory.at(i)->id << " units: " << vTerritory.at(i)->unitsGarrisoned << endl;
    }
}

/**
 * All the territories adjacent to the player that he can attack
 *
 * @param vPlayer the vector of all Players in the game
 */
vector<Territory *> Player::toAttack() {
   return ps->toAttack();
}

/**
 * All the territories that the current player can defend
 * Returns a list of territories that the player owns
 */
vector<Territory *> Player::toDefend() {
    return ps->toDefend();
}

/**
 * Shows territories adjacent to the territories owned by current player
 * (Used in toAttack)
 */
void Player::displayAdjacentTerritoriesNotOwned() {

    for (int i = 0; i < this->toAttack().size(); i++) {
        cout << "Name: " << this->toAttack().at(i)->name <<
             " ID: " << this->toAttack().at(i)->id << endl;
    }
}

/**
 * Shows the territories that are owned by player that are adjacent to enemy territories
 * (used in toDefend)
 */
void Player::displayOwnedAdjacentTerritories() {

    for (int i = 0; i < this->toDefend().size() - 1; i++) {
        cout << "Name: " << this->toDefend().at(i)->name <<
             " ID: " << this->toDefend().at(i)->id << endl;
    }
}

/**
 * Pass in a territory id to see if its in the given list of Territories
 *
 * @param listOfTerritories
 * @param idOfTerritory
 * @return
 */
bool Player::isTerritoryInList(vector<Territory *> listOfTerritories, int idOfTerritory) {
    for (int i = 0; i < listOfTerritories.size(); i++) {
        if (idOfTerritory == listOfTerritories.at(i)->id) {
            return true;
        }
    }
    return false;
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
Territory *Player::getTerritoriesOwned(int vIndex) {
    return vTerritory.at(vIndex);
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
    //return vHand->at(vIndex).size();
}

/**
 * Gets the number of cards in the players hand
 *
 * @return the int for amount of cards
 */
int Player::getHandSize() const {
    return vHand->cardsHeld.size();
}

/**
 * Gets the order at the index given
 * @param vIndex index of card
 * @return the order at the given index
 */
Orders *Player::getOrder(int vIndex) {
    return this->ordersList->getListMember(vIndex);
}

/**
 * Returns the orders list of the current player
 * @return orders list as a pointer
 */
OrdersList *Player::getOrdersList() {
    return this->ordersList;
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

/**
 * Sets the initial reinforcements based on the initial startup phase
 * @param armies
 */
void Player::setReinforcements(int armies) {
    this->reinforcements = armies;
}

/**
 * Gets the reinforcements of the current player
 * @return int of number of reinforcements
 */
int Player::getReinforcements() {
    return this->reinforcements;
}

/**
 * Loops through each player and allows them to issue orders based on their hand,
 * territories and the other players still in play
 * @param vPlayersInPlay is a vector of the other players still in the game
 */
void Player::issueOrder(vector<Player *> &vPlayersInPlay) {
    this->ps->issueOrder(vPlayersInPlay);
}

/**
 * Checks if the current territory id is owned by the current player
 * @param id of the territory
 * @return the territory that is owned otherwise a nullptr
 */
Territory *Player::isOwnedTerritory(int id) {
    for (int i = 0; i < vTerritory.size(); i++) {
        if (vTerritory.at(i)->id == id) {
            return vTerritory.at(i);
        }
    }
    return nullptr;
}

/**
 * Adds a territory to the players vector of territories
 * @param territory is the territory being added
 */
void Player::addTerritory(Territory *territory) {
    vTerritory.push_back(territory);
    this->setIncrementTerritoryCount(territory->continent-1);
}

/**
 * Removes a territory from the vector of territories
 * @param territory is the territory we want to remove
 */
void Player::removeTerritory(Territory *territory) {
    for (int i = 0; i < vTerritory.size(); i++) {
        if (territory->id == vTerritory.at(i)->id) {
            vTerritory.erase(vTerritory.begin() + i);
        }
    }
    this->setDecrementTerritoryCount(territory->continent-1);
}

/**
 * Gets the current players hand
 * @return the hand of the player
 */
Hand *Player::getHand() {
    return this->vHand;
}

//Hand * Player::setHand() {
//
//}

/**
 * Gets the territories owned conter in each continent
 * @return a vector that is the same size and order as the main games continent territory count
 */
const vector<int> &Player::getTerritoriesOwnedPerContinent() const {
    return territoriesOwnedPerContinent;
}

/**
 * Adds a count depending on the index where a new territory was gained
 */
void Player::setTerritoriesOwnedPerContinent() {
    for (int i = 0; i < mapLink->continents.size(); i++) {
        //if the total number of continents is 3 then it will loop 3 times and set the vector to a size of 3
        this->territoriesOwnedPerContinent.push_back(0);
    }
}

/**
 * Increments the territory size of the player
 * @param index at the index of specified territory
 */
void Player::setIncrementTerritoryCount(int index) {
    this->territoriesOwnedPerContinent.at(index) = this->territoriesOwnedPerContinent.at(index) + 1;
}

/*
 * Decrements the territory size if a territory is lost
 */
void Player::setDecrementTerritoryCount(int index) {
    this->territoriesOwnedPerContinent.at(index) = this->territoriesOwnedPerContinent.at(index) - 1;
}

int Player::validPlayer(vector<Player *> validPlayers, string name) {
    for (int i = 0; i < validPlayers.size(); i++) {
        if (name.rfind(validPlayers.at(i)->getName(), 0) == 0) {
            return i;
        }
    }
    return -1;
}

/**
 * Links each player to the map loaded at startup
 * @param map is the map at startup
 */
void Player::setMapLink(Map &map) {
    this->mapLink = &map;
}

/**
 * Links each player to the deck that is loaded at startup
 * @param deck is the deck at startup
 */
void Player::setDeckLink(Deck &deck) {
    this->deckLink = &deck;
}

/**
 *
 * @param armiesToAdd
 */
void Player::addReinforcements(int armiesToAdd) {
    this->reinforcements += armiesToAdd;
}

/**
 * Removes reinforcements from the reinforcement pool
 * @param armiesToRemove
 */
void Player::removeReinforcements(int armiesToRemove) {
    this->reinforcements -= armiesToRemove;
}

/**
 * Remove a negotiation once it has be called
 * @param index
 */
void Player::removeNegotiations(int index) {
    this->negotiatingWith.erase(negotiatingWith.cbegin());
}

void Player::setPlayerStrategy(PlayerStrategy *newStrategy) {
    this->ps = newStrategy;
}
const vector<Territory *> &Player::getVTerritory() const {
    return vTerritory;
}
int Player::getPlayerStrategy() {
    if (ps->neutralReturn() == 1) {
        return 1;
    }
    return 0;
}


/**
 * A neutral player is created
 * @return a neutral player
 */
//Player &Player::neutralPlayer() {
//    static Player neutralPlayer;
//    return neutralPlayer;
//}



