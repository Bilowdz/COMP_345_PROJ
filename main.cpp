#include <iostream>
#include "GameEngineDriver.h"
using namespace std;

int main() {
    cout << "Hello, World!" << endl;

    GameEngineDriver driver;
    GameEngineDriver driver2;
    GameEngineDriver d = driver2;
    while(!driver.isGameDone) {
        driver.chooseCommand();
    }

    return 0;
}
