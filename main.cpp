#include <iostream>
#include "GameEngineDriver.h"
using namespace std;

int main() {
    cout << "Hello, World!" << endl;

    GameEngineDriver driver;
    cout << "-------------" << endl;
    cout << "GameEngineDriver: " << driver << endl;

    while(!driver.isGameDone) {
        driver.chooseCommand();
    }

    return 0;
}
