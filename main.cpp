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

    cout << "Choose between accepting the commands from the console (1) or from a file (2):";
    int input = 0;
    cin >> input;

    // user selected console
    if(input == 1) {


        bool isGameDone = false;
        // loop until user chooses to exit game
        while(!isGameDone) {
            LogObserver* logger = new LogObserver();
            CommandProcessor cp;
            cp.Attach(logger);
            GameEngine *ge2 = new GameEngine();
            ge2->Attach(logger);
            ge2->startupPhase(cp, ge2);

            // check for win condition
            if(ge2->getState() == ST_WIN) {
                while(true) {
                    Command* c = cp.getCommand(ge2);

                    // check for error
                    if(c->getEffect().length() != 0) {
                        cout << "ERROR: " << c->getEffect() << endl;

                        // valid command, execute it
                    } else {
                        ge2->transition(c);
                        if (ge2->isGameDone) {
                            isGameDone = true;
                        }
                        break;
                    }
                }
            }
            delete ge2;
            delete logger;
        }

    } else {
        LogObserver* logger = new LogObserver();
        GameEngine* ge = new GameEngine();
        ge->Attach(logger);
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
        Command * c6 =adapter.getCommand(ge);
        ge->transition(c6);
    }
}

void tournamentDriver() {
    GameEngine* ge = new GameEngine();

    // used for parsing the tournament parameters
    FileCommandWriter fcw;

    // sample data until tournament parameters is parsed
    vector<string> maps;
    maps.push_back("minimap.map");
    maps.push_back("canada.map");

    vector<string> players;
    players.push_back("p1");
    players.push_back("p2");
    players.push_back("p3");
    int numGames = 4;

    // write a commands.txt type file based on given tournament parameters, get its fileName
    string fileName = fcw.writeTournamentFile(maps,players,numGames);

    FileCommandProcessorAdapter adapter((FileLineReader(fileName)));

    // read whole tournament until there are no more commands left
    while(adapter.hasCommand()) {
        Command * c = adapter.getCommand(ge);
        ge->transition(c);
        // todo: destruct everything
    }
    // todo: final output
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
