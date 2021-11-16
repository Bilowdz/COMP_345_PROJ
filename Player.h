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

class Deck;
class Map;

class Player {
public:

    Map * mapLink;
    Deck * deckLink;

    Player();
    explicit Player(string *name);
    Player(vector<Territory *> vTerritories, Hand * vHand, OrdersList * ordersList);
    Player(string *name, vector<Territory *> vTerritories, Hand * vHand, OrdersList * ordersList);
    Player(const Player &copyPlayer);
    Player & operator = (const Player &p);
    ~Player();

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
    const vector<int *> &getTerritoriesOwnedPerContinent() const;
    void setIncrementTerritoryCount(int index);
    void setDecrementTerritoryCount(int index);
    void setTerritoriesOwnedPerContinent(int size);

    int getCardsOwned(int vIndex);
    Hand * getHand();
    int getHandSize() const;

    OrdersList* getOrdersList();
    Orders* getOrder(int vIndex);
    int getNumberOfOrders() const;
    void setReinforcements(int armies);
    int getReinforcements();

    void setOrdersList(OrdersList *ordersList);

    string getName() const;
    void setName(string s);

private:
    string name; //Name of the player
    vector<Territory *> vTerritory; //Vector of all the territories owned
    Hand * vHand; //Vector of all the cards the player owns
    OrdersList * ordersList; //Vector for all the orders the player can do
    int reinforcements;
    vector<int *> territoriesOwnedPerContinent; //when a player captures a territory increment the value at the continent

};

#endif //COMP_345_PROJ_PLAYER_H
