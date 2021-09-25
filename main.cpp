#include <iostream>
#include "Player.h"

using namespace std;

int main() {

    int number;

    cout << "Enter number of players" << endl;
    cin >> number;

    vector<Player> nameVector(number); //using constructor to create n size array

    for (int i = 0; i < number; i++) {
        Player playerObj;
        string playerName;
        cout << "Please enter your name: ";
        cin >> playerName;
        playerObj.setName(playerName);
        nameVector.push_back(playerObj);
        cout << endl;
    }

    for (auto &x: nameVector) {
        cout << x.getName() << endl;
    }

    return 0;
}
