#include "Card.h"
#include "Map.h"
#include "Orders.h"
#include "Player.h"
#include "CommandProcessing.h"
#include "LoggingObserver.h"
#include <iostream>
#include <memory>
using namespace std;

void driveMap() {
    auto *loader(new MapLoader());

    std::cout << *loader;

    std::cout << loader->maps.size() << std::endl;

    delete loader;
}

void chooseComandProcessor() {
    LogObserver* logger = new LogObserver();
    GameEngine* ge = new GameEngine();
    ge->Attach(logger);
    cout << "Choose between accepting the commands from the console (1) or from a file (2):";
    int input = 0;
    cin >> input;

    // user selected console
    if(input == 1) {
        CommandProcessor cp;
        cp.Attach(logger);
        ge->startupPhase(cp, ge);
    } else {
        string filename;

        cout << "Please enter a filename (commands.txt, commands2.txt are the only available files):";
        cin >> filename;

        FileLineReader flr("../CommandProcessorFiles/" + filename);
        FileCommandProcessorAdapter adapter(flr);
        adapter.Attach(logger);
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
    }
}

void cpDriver() {
    chooseComandProcessor();
}

int main() {
    ofstream file("../gamelog.txt");
    file.close();

    auto *neutralName = new string("neutral");
    vector<Territory*> neutralTerritories;
    Hand *neutralHand = new Hand();
    auto *neutralOrdersList = new OrdersList();
    Player::neutralPlayer() = *new Player(neutralName, neutralTerritories, neutralHand, neutralOrdersList);
    cpDriver();

    delete neutralName;
    delete neutralHand;
    delete neutralOrdersList;

    return 0;
}
