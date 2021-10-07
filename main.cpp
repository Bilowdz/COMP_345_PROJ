#include <iostream>
#include "Player.h"
#include <memory>

using namespace std;

void createPlayers(vector<Player *>, int);

vector<Territory *> generateTerritories(int numTerritoryOwned);
vector<Hand *> generateHand(int numCardsPerPlayer);
vector<Order *> generateOrder();
void displayTerritories(vector<Territory*>);
static int territoryNumber = 1;
static int cardNumber = 1;
static int numOfOrders = 2;

int main() {
    static const int territoriesOwnedPerPlayer = 5;
    static const int numCardsPerPlayer = 3;
    int numPlayers = 0;
    vector<Player *> vPlayer;
    vector<Player *> nameVector;
    vector<Territory *> vTerri;



    //generate territory vector, hand vector and order vector to be passed into constructor.
    //createPlayers(nameVector, numPlayers);

    string playerName;
    string *pPlayerName = &playerName;
    cout << "Enter number of players: \n";
    cin >> numPlayers;

    for (unsigned i = 0; i < numPlayers; ++i) {
        cout << "Please enter your name: ";
        cin >> playerName;
        auto *pPlayer = new Player(pPlayerName,
                                   generateTerritories(territoriesOwnedPerPlayer),
                                   generateHand( numCardsPerPlayer),
                                   generateOrder());
        vPlayer.push_back(pPlayer);
        cout << endl;
    }

    for (int i = 0; i < numPlayers; ++i) {
        cout << "Player: " + to_string(i + 1) << endl;
        cout << "Player Name: " << vPlayer.at(i)->getName() << endl;
        cout << "Territories Owned: \n";
        for(int j = 0; j < territoriesOwnedPerPlayer; ++j) {
            cout << "\t" + vPlayer.at(i)->getTerritoriesOwned(j) << endl;
        }
        cout << "Cards Owned: \n" ;
        for(int k = 0; k < numCardsPerPlayer; ++k) {
            cout << "\tCard Number: " + to_string(vPlayer.at(i)->getCardsOwned(k)) << endl;
        }
        cout << "Orders Sent: \n";
        for(int l = 0; l < numOfOrders; ++l) {
            cout << "\t" + vPlayer.at(i)->getOrder(l) << " " + to_string(l + 1) << endl;
        }
        cout << endl;
    }

    return 0;
}

void createPlayers(vector<Player *> vPlayer, int numPlayers) {
    numPlayers;
    string playerName;
    string *pPlayerName = &playerName;
    cout << "Enter number of players: ";
    cin >> numPlayers;
    Player *pPlayer;

    for (unsigned i = 0; i < numPlayers; ++i) {
        cout << "Please enter your name: ";
        cin >> playerName;
        pPlayer = new Player(pPlayerName);
        vPlayer.push_back(pPlayer);
        cout << endl;
    }
}

vector<Territory *> generateTerritories(int numTerritoryOwned) {
    vector<Territory *> vTerritory;
    Territory *pPlayerTerritory;
    for (int i = 0; i < numTerritoryOwned ; ++i) {
        pPlayerTerritory = new Territory((rand() % 100), "Territory " + to_string(territoryNumber));
        vTerritory.push_back(pPlayerTerritory);
        territoryNumber++;
    }
    return vTerritory;
}

vector<Hand *> generateHand(int numCardsPerPlayer) {
    vector<Hand *> vHand;
    Hand *pHand;
    for (unsigned i = 0; i < numCardsPerPlayer; i++) {
        pHand = new Hand(cardNumber);
        vHand.push_back(pHand);
        cardNumber++;
    }
    return vHand;
}

vector<Order *> generateOrder() {
    vector<Order *> vOrder;
    for (unsigned i = 0; i <= numOfOrders; ++i) {
        auto *pOrder = new Order;
        vOrder.push_back(pOrder);
    }
    return vOrder;
}


