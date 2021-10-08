#include <iostream>
#include "Player.h"
#include <memory>
using namespace std;

vector<Territory *> generateTerritories(int numTerritoryOwned);
vector<Hand *> generateHand(int numCardsPerPlayer);
vector<Order *> generateOrder();

static int territoryNumber = 1;
static int cardNumber = 1;
static int numOfOrders = 2;

int main() {
    static const int territoriesOwnedPerPlayer = 5;
    static const int numCardsPerPlayer = 3;
    int numPlayers = 0;
    vector<Player *> vPlayer;
    //vector<Player *> nameVector;
    //vector<Territory *> vTerri;
    string playerName;
    string *pPlayerName = &playerName;
    cout << "Enter number of players: \n";
    cin >> numPlayers;

    for (unsigned i = 0; i < numPlayers; ++i) {
        cout << "Please enter your name: ";
        cin >> playerName;
        auto *pPlayer = new Player(pPlayerName,
                                   generateTerritories(territoriesOwnedPerPlayer),
                                   generateHand(numCardsPerPlayer),
                                   generateOrder());
        vPlayer.push_back(pPlayer);
        cout << endl;
    }

    for (int i = 0; i < numPlayers; ++i) {
        cout << "Player: " + to_string(i + 1) << endl;
        cout << "Player Name: " << vPlayer.at(i)->getName() << endl;
        cout << "Territories Owned: \n";
        for (int j = 0; j < territoriesOwnedPerPlayer; ++j) {
            cout << "\t" + vPlayer.at(i)->getTerritoriesOwned(j) << endl;
        }
        cout << "Cards Owned: \n";
        for (int k = 0; k < numCardsPerPlayer; ++k) {
            cout << "\tCard Number: " + to_string(vPlayer.at(i)->getCardsOwned(k)) << endl;
        }
        cout << "Orders Sent: \n";
        for (int l = 0; l <= numOfOrders; ++l) {
            cout << "\t" + vPlayer.at(i)->getOrder(l) << " " + to_string(l + 1) << endl;
        }
        cout << "Territories to defend: \n";
        vPlayer.at(i)->toDefend();

        cout << "Territories to attack: \n";
        vPlayer.at(i)->toAttack(vPlayer);
        cout << endl;
    }

    int playing = false;

    while(!playing) {
        string input;
        string order;
        cout << "Would you like to issue an order (y/n)?";
        cin >> input;

        if(input == "y") {
            cout << "Enter your order: ";
            cin >> order;
            vPlayer.at(0)->issueOrder(order);
            playing = false;
        } else if(input == "n") {
            cout << "End of program!" << endl;
            playing = true;
        }
        else {
            cout << "Sorry try again" << endl;
            playing = false;
        }
    }

    cout << "Orders Sent: \n";
    for (int l = 0; l < vPlayer.at(0)->getNumberOfOrders(); ++l) {
        cout << "\t" + vPlayer.at(0)->getOrder(l) << endl;
    }

    for (auto & clearMemory : vPlayer) {
        delete clearMemory;
    }

    return 0;
}
/**
 * Generates the territories for each player.
 *
 * @param numTerritoryOwned the initial amount of territories
 * @return vector of Territories that gets passed into the player vector
 */
vector<Territory *> generateTerritories(int numTerritoryOwned) {
    vector<Territory *> vTerritory;
    Territory *pPlayerTerritory;
    for (int i = 0; i < numTerritoryOwned; ++i) {
        pPlayerTerritory = new Territory((rand() % 100), "Territory " + to_string(territoryNumber));
        vTerritory.push_back(pPlayerTerritory);
        territoryNumber++;
    }
    return vTerritory;
}

/**
 * Generates the cards for each player
 *
 * @param numCardsPerPlayer the initial amount of cards per player
 * @return vector of Hands that gets passed into the player vector
 */
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

/**
 * Generates Orders that each player can execute
 *
 * @return a vector of Orders that gets passed into player vector
 */
vector<Order *> generateOrder() {
    vector<Order *> vOrder;
    for (unsigned i = 0; i <= numOfOrders; ++i) {
        auto *pOrder = new Order;
        vOrder.push_back(pOrder);
    }
    return vOrder;
}



