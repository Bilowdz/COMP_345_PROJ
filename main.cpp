#include <iostream>
#include "GameEngineDriver.h"
using namespace std;

void runGameEngine(){
    GameEngineDriver driver;

    // loop until game is done
    while(!driver.isGameDone()) {

        // accept user input
        cin >> driver;

        cout << driver << endl;
    }
}

int main() {
    runGameEngine();

    return 0;
}
