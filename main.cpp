#include <iostream>
#include "GameEngineDriver.h"
#include "Map.h"
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

void driveMap() {
    auto* loader(new MapLoader());

    std::cout << *loader;

    std::cout << loader->maps.size() << std::endl;

    delete loader;
}

int main() {
    driveMap();

    return 0;
}
