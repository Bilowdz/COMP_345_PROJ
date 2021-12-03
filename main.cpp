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


void cpDriver() {
    chooseComandProcessor();
}

string validateTournament(GameEngine * ge) {
    string input;

    cout << "Enter tournament thing: ";
    // get user input
    getline(cin,input);
    cout << endl;

    while(!ge->validateTournamentPhase(input)) {
        cout << endl;
        cout << "Enter tournament thing: ";
        // get user input
        getline(cin,input);
    }
    return input;
}

void tournamentDriver() {
    LogObserver* logger = new LogObserver();
    GameEngine* ge = new GameEngine();
    ge->Attach(logger);

    // used for parsing the tournament parameters
    FileCommandWriter fcw;

    // get tournament command from user, and validate it
    string input = validateTournament(ge);
    // parse tournament parameters
    vector<string> players = fcw.parsePlayer(input);
    vector<string> maps = fcw.parseMap(input);
    int depth = fcw.parseMaxDepth(input);
    int numGames = fcw.parseNumGames(input);

    ge->setTournament(numGames, depth, maps, players);
    // write a commands.txt type file based on given tournament parameters, get its fileName
    string fileName = fcw.writeTournamentFile(maps,players,numGames);

    FileLineReader flr(fileName);
    FileCommandProcessorAdapter adapter(flr);
    adapter.Attach(logger);

    // read whole tournament until there are no more commands left
    while(adapter.hasCommand()) {
        Command * c = adapter.getCommand(ge);
        ge->transition(c);
        // todo: destruct everything
    }
    ge->PrintResults();
}

int main() {

    // sample tournament command:
    // tournament -M zertina.map, canada.map -P Cheater, Aggressive, Neutral, Benevolent -G 2 -D 15

    tournamentDriver();
    return 0;
}
