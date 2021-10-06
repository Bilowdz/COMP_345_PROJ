#include <iostream>
#include "Player.h"

using namespace std;

void createPlayerVec(vector<Player>);
void showPlayerVec(vector<Player>);
vector<Territory*> generateTerritories(int territoryNumber);
vector<Hand*> generateHand(vector<Territory*>, int cardNumber);

int main() {
    int territoryNumber = 1;
    int cardNumber = 1;

    vector<Player> nameVector;
    vector<Territory*> vTerri;

    int numPlayers;
    string playerName;
    string *pPlayerName = &playerName;
    cout << "Enter number of players: ";
    cin >> numPlayers;

    for (unsigned i = 0; i < numPlayers; ++i) {
        cout << "Please enter your name: ";
        cin >> playerName;
        Player pObject(pPlayerName);
        nameVector.push_back(pObject);
        cout << endl;
    }



//    for(vector<Player*>::iterator it = nameVector.begin(); it != nameVector.end(); ++it) {
//        cout << (*it)->getName() << endl; //The * operator gives you the item referenced by the iterator, which in your case is a pointer. Then you use the -> to dereference that pointer.
//    }
//
    cout << "Names entered" << endl;
    for (unsigned i = 0; i < nameVector.size(); i++) {
        cout << nameVector.at(i).getName() << endl;
    }

    return 0;
}

//vector<Territory*> generateTerritories(vector<Territory*> vTerritory, int territoryNumber) {
//    Territory playerTerritory((rand() % 20), ("Territory" + to_string(territoryNumber)));
//    //vTerritory.push_back(playerTerritory);
//
//}
//
//vector<Hand*> generateHand(int card) {
//    //Hand(card);
//}

//void createPlayerVec(vector<Player> vecPlayer) {
//
//}
//
//void showPlayerVec(const vector<Player>& vecPlayer) {
//
//    unsigned int vecSize = vecPlayer.size();
//
//    for(unsigned int i = 0; i < vecSize; i++) {
//        cout << vecPlayer[i].getName() << endl;
//    }
//
//}
