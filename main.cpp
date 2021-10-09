#include <iostream>
#include "Player.h"
#include <memory>
using namespace std;

vector<Territory *> generateTerritories(int numTerritoryOwned);
vector<Hand *> generateHand(int numberCardsPerPlayer);
vector<Order *> generateOrder();

static int territoryNumber = 1;
static int cardNumber = 1;
static int numOfOrders = 2;
static const int territoriesOwnedPerPlayer = 5;
static const int numCardsPerPlayer = 3;

int main() {

    int numPlayers = 0;
    vector<Player *> vPlayer;
    string playerName;
    cout << "Enter number of players: \n";
    cin >> numPlayers;

    for (unsigned i = 0; i < numPlayers; ++i) {
        cout << "Please enter your name: ";
        cin >> playerName;

        auto *pPlayer = new Player(&playerName,
                                   generateTerritories(territoriesOwnedPerPlayer),
                                   generateHand(numCardsPerPlayer),
                                   generateOrder());
        vPlayer.push_back(pPlayer);
        cout << endl;
    }



    for (int i = 0; i < numPlayers; ++i) {

        cout << *vPlayer.at(i); //ostream called
        cout << "Territories to attack: \n";
        vPlayer.at(i)->toAttack(vPlayer);
        cout << endl;
    }

    int playing = false;

    while(!playing) {
        string input;
        string order;
        cout << "Would you like to issue an order (y/n)? ";
        cin >> input;

        if(input == "y") {
            cout << "Enter your order: ";
            cin >> order;
            vPlayer.at(0)->issueOrder(order); //showing issueOrder Function
            playing = false;
        } else if(input == "n") {
            cout << "Orders Sent: \n";
            for (int l = 0; l < vPlayer.at(0)->getNumberOfOrders(); ++l) {
                cout << "\t" + vPlayer.at(0)->getOrder(l) << endl;
            }
            cout << "End of program!" << endl;
            playing = true;
        }
        else {
            cout << "Sorry try again\n" << endl;
            playing = false;
        }
    }

    //delete the pointers of vPlayer
    for (auto & i : vPlayer) {
        delete i;
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
vector<Hand *> generateHand(int numberCardsPerPlayer) {
    vector<Hand *> vHand;
    Hand *pHand;
    for (unsigned i = 0; i < numberCardsPerPlayer; i++) {
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



