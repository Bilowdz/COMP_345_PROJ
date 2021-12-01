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
#include "PlayerStrategy.h"
using namespace std;

class Deck;
class Map;
//class PlayerStrategy;

class Player {
public:

    Deck * deckLink;
    Map * mapLink;
    PlayerStrategy *ps;

    void setMapLink(Map & map);
    void setDeckLink(Deck & deck);

    Player();
    explicit Player(string *name);
    //todo constructor must take in a initial strategy
    Player(vector<Territory *> vTerritories, Hand * vHand, OrdersList * ordersList);
    Player(string *name, vector<Territory *> vTerritories, Hand * vHand, OrdersList * ordersList);
    Player(const Player &copyPlayer);
    Player & operator = (const Player &p);
    ~Player();

    //todo add setStrategy() and executeStrategy()

    friend ostream &operator<<(ostream &output, Player &player);
    vector<Territory *> toAttack();
    vector<Territory *> toDefend();
    void displayAdjacentTerritoriesNotOwned();
    void displayOwnedAdjacentTerritories();
    bool isTerritoryInList(vector<Territory*>, int id);
    void issueOrder(vector<Player*> &vPlayersInPlay);

    //make function to check it matched player is in the list
    int validPlayer(vector<Player *> validPlayers, string name);

    void setTerritoriesOwned(vector<Territory *> vTerritories);
    void addTerritory(Territory * territory);
    void removeTerritory(Territory *territory);
    Territory * getTerritoriesOwned(int vIndex);
    int getTerritorySize() const;
    Territory * isOwnedTerritory(int id);
    void displayTerritoriesOwned();
    const vector<int> &getTerritoriesOwnedPerContinent() const;
    void setIncrementTerritoryCount(int index);
    void setDecrementTerritoryCount(int index);
    void setTerritoriesOwnedPerContinent();

    int getCardsOwned(int vIndex);
    Hand * getHand();
    //Hand * setHand();
    int getHandSize() const;

    OrdersList* getOrdersList();
    Orders* getOrder(int vIndex);
    //int getNumberOfOrders() const;
    void setReinforcements(int armies);
    int getReinforcements();
    void addReinforcements(int armiesToAdd);
    void removeReinforcements(int armiesToRemove);


    //void setOrdersList(OrdersList *ordersList);

    string getName() const;
    void setName(string s);
    vector<Player*> negotiatingWith;
    void removeNegotiations(int index);

    static Player &neutralPlayer();

private:
    string name; //Name of the player
    vector<Territory *> vTerritory; //Vector of all the territories owned
    Hand * vHand; //Vector of all the cards the player owns
    OrdersList * ordersList; //Vector for all the orders the player can do
    int reinforcements; //number of armies
    vector<int> territoriesOwnedPerContinent; //when a player captures a territory increment the value at the continent
};

extern Player neutralPlayer;

#endif //COMP_345_PROJ_PLAYER_H
