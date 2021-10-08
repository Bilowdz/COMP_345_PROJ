#include <iostream>
#include "GameEngineDriver.h"
using namespace std;

void runGameEngine(){
    GameEngineDriver driver;
    while(!driver.isGameDone()) {
        cin >> driver;
        cout << driver << endl;
    }
}

int main() {
    runGameEngine();

    return 0;
}
