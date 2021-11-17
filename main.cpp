#include <iostream>
#include "Map.h"
#include "Orders.h"
#include "Card.h"
#include "Player.h"
#include "CommandProcessing.h"
#include <memory>
using namespace std;

void driveMap() {
    auto* loader(new MapLoader());

    std::cout << *loader;

    std::cout << loader->maps.size() << std::endl;

    delete loader;
}

void chooseComandProcessor() {
    GameEngine* ge = new GameEngine();
    cout << "Choose between accepting the commands from the console (1) or from a file (2):";
    int input = 0;
    cin >> input;

    // user selected console
    if(input == 1) {
        CommandProcessor cp;
        ge->startupPhase(cp, ge);
    } else {
        string filename;

        cout << "Please enter a filename (commands.txt, commands2.txt are the only available files):";
        cin >> filename;

        FileLineReader flr("../CommandProcessorFiles/" + filename);
        FileCommandProcessorAdapter adapter(flr);
        Command * c1 = adapter.getCommand(ge);
        ge->transition(c1);
        Command * c2 =adapter.getCommand(ge);
        ge->transition(c2);
        Command * c3 =adapter.getCommand(ge);
        ge->transition(c3);
        Command * c4 =adapter.getCommand(ge);
        ge->transition(c4);
        Command * c5 =adapter.getCommand(ge);
        ge->transition(c5);
        Command * c6 =adapter.getCommand(ge);
        ge->transition(c6);
        Command * c7 =adapter.getCommand(ge);
        ge->transition(c7);
        Command * c8 =adapter.getCommand(ge);
        ge->transition(c8);
    }
}

void cpDriver() {
    chooseComandProcessor();
}

int main() {
    cpDriver();
    //GameEngine* ge = new GameEngine();
    //CommandProcessor cp;
    //ge->startupPhase(cp, ge);

    return 0;
}
