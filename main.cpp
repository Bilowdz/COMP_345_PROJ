#include <iostream>
#include "Player.h"

using namespace std;

void createPlayerVec(vector<Player> &);

void showPlayerVec(vector<Player> &);

int main() {

    vector<Player> nameVector;

    int numPlayers;
    string x;
    string *pPlayerName;
    pPlayerName = &x;
    cout << "Enter number of players: ";
    cin >> numPlayers;

    for (unsigned i = 0; i < numPlayers; ++i) {
        cout << "Please enter your name: ";
        cin >> x;
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
