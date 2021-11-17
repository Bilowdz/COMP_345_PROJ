//
// Created by Nicolo on 2021-09-24.
//
#include "GameEngine.h"
#include "CommandProcessing.h"
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

// constructor
GameEngine::GameEngine() : isGameDone(false), currentState(ST_START) {
    if(this->debug)
        cout << "GameEngine constructor called" << endl;
}

// copy constructors
GameEngine::GameEngine(const GameEngine &game) : isGameDone(false), currentState(game.currentState) {
    if(this->debug)
        cout << "GameEngine copy constructor called" << endl;
}

GameEngine::GameEngine(GameEngine *const pGameEngine) : isGameDone(false), currentState(pGameEngine->currentState) {
    if(this->debug)
        cout << "GameEngine copy constructor 2 called" << endl;
}

// destructor
GameEngine::~GameEngine() = default;

// validate and execute transitions based on current state
bool GameEngine::transition(Command *c) {
    string command = c->getCommand();
    string loadmap = "loadmap";
    string addplayer = "addplayer";

    if (command.rfind(loadmap, 0) == 0) {
        // only transition from valid states
        if (currentState == ST_START || currentState == ST_MAP_LOADED) {

            // valid transition to state map loaded, so travel to state
            currentState = ST_MAP_LOADED;

            // execute game engine function
            this->loadmap(c);
            return true;
        }
    } else if (command == "validatemap") {
        if (currentState == ST_MAP_LOADED) {
            currentState = ST_MAP_VALIDATED;
            this->validatemap();
            return true;
        }
    } else if (command.rfind(addplayer, 0) == 0) {
        if (currentState == ST_MAP_VALIDATED || currentState == ST_PLAYERS_ADDED) {
            currentState = ST_PLAYERS_ADDED;
            this->addplayer(c);
            return true;
        }
    } else if (command == "assigncountries") {
        if (currentState == ST_PLAYERS_ADDED) {
            currentState = ST_ASSIGN_REINFORCEMENT;
            this->assigncountries();
            return true;
        }
    } else if (command == "issueorders") {
        if (currentState == ST_ASSIGN_REINFORCEMENT || currentState == ST_ISSUE_ORDERS) {
            currentState = ST_ISSUE_ORDERS;
            this->issueorder();
            return true;
        }
    } else if (command == "endissueorders") {
        if (currentState == ST_ISSUE_ORDERS) {
            currentState = ST_EXECUTE_ORDERS;
            this->endissueorders();
            return true;
        }
    } else if (command == "execorder") {
        if (currentState == ST_ISSUE_ORDERS || currentState == ST_EXECUTE_ORDERS) {
            currentState = ST_EXECUTE_ORDERS;
            this->execorder();
            return true;
        }
    } else if (command == "endexecorders") {
        if (currentState == ST_EXECUTE_ORDERS) {
            currentState = ST_ASSIGN_REINFORCEMENT;
            this->endexecorders();
            return true;
        }
    } else if (command == "win") {
        if (currentState == ST_EXECUTE_ORDERS) {
            currentState = ST_WIN;
            this->win();
            return true;
        }
    } else if (command == "play") {
        if (currentState == ST_WIN) {
            currentState = ST_START;
            this->play();
            return true;
        }
    } else if (command == "end") {
        if (currentState == ST_WIN) {
            currentState = ST_END;
            this->end();
            this->isGameDone = true;
            return true;
        }
    }
    return false;
}

// return enum value currentState
State GameEngine::getState() {
    return currentState;
}

void GameEngine::loadmap(Command *c) {

    string command = c->getCommand();
    int mapChosen;

    if (command == "loadmap zertina.map") {
        mapChosen = 3;
    } else if (command == "loadmap bigeurope.map") {
        mapChosen = 1;
    } else if (command == "loadmap canada.map") {
        mapChosen = 2;

    // invalid map
    } else {

    }

    MapLoader load;
    gameMap = *load.maps.at(mapChosen - 1);

}

void GameEngine::validatemap() {
    cout << "Validating Map..." << endl;
    if (gameMap.Validate())
        cout << "Map is valid!" << endl;
    else {
        cout << "Map is not valid!" << endl;
        exit(0);
    }
}

void GameEngine::addplayer(Command *c) {

    // get the name from command object
    string *name = new string((c->getCommand()).substr(10));
    vector<Territory*> vTerritories;
    Hand *vHand = new Hand();
    OrdersList *ordersList = new OrdersList();
    Player *newPlayer = new Player(name, vTerritories, vHand, ordersList);
    newPlayer->setDeckLink(MainDeck);
    newPlayer->setMapLink(&gameMap);
    newPlayer->setTerritoriesOwnedPerContinent();
    newPlayer->addReinforcements(50);
    this->Players.push_back(newPlayer);

}

void GameEngine::gamestart() {
    gameMap.countTerritoriesPerContinent();
    std::shuffle(std::begin(Players), std::end(Players), std::default_random_engine());
    cout << "\nThe player order is: " << endl;
    for (int i = 0; i < Players.size(); i++) {
        cout << i + 1 << ": " << Players.at(i)->getName() << endl;
    }
    MainDeck = new Deck(Players.size());
    for (auto &Player: Players) {
        MainDeck->Draw(Player->getHand());
        MainDeck->Draw(Player->getHand());
    }

    this->transition(new Command("assigncountries"));
}

void GameEngine::assigncountries() {
    for (int i = 0; i < gameMap.map.size(); i++) {
        int randomPlayer = i % Players.size();
        Players.at(randomPlayer)->addTerritory(gameMap.map.at(i));
        gameMap.map.at(i)->playerLink = Players.at(randomPlayer);
    }
}

void GameEngine::issueorder() {
    issueOrdersPhase();
}

void GameEngine::execorder() {
    executeOrdersPhase();
}

void GameEngine::endexecorders() {
    cout << "Executing function endexecorders" << endl;
}

void GameEngine::endissueorders() {
    cout << "Executing function endissueorders" << endl;
}

void GameEngine::win() {
    cout << "Executing function win" << endl;
    // todo: prompt user to play again or quit using command processor
}

void GameEngine::end() {
    cout << "Executing function end" << endl;
}

void GameEngine::play() {
    cout << "Executing function play" << endl;
}

// assignment operator overload
GameEngine &GameEngine::operator=(const GameEngine &ge) {
    this->currentState = ge.currentState;

    return *this;
}

// stream insertion operator overloads
ostream &operator<<(ostream &out, const GameEngine &ge) {
    out << "Current State:" << enum_state_str[ge.currentState] << endl;
    return out;
}

void GameEngine::startupPhase(CommandProcessor cp, GameEngine *ge) {
    while (true) {

        // get command
        Command *c = cp.getCommand(ge);
        string commandName = c->getCommand();
        string effect = c->getEffect();

        // process commands that have no errors
        if(effect.length() == 0) {

            // stop startup phase once game started
            if (commandName == "gamestart") {
                gamestart();
                mainGameLoop();
                break;
            } else {
                transition(c);
            }
        } else {

            // output the error message
            cout << "ERROR" << effect << endl;
        }
    }
}

void GameEngine::mainGameLoop() {

    bool noWinner = false;
    while (!noWinner) {

        reinforcementPhase();

        this->transition(new Command("issueorders"));
        this->transition(new Command("endissueorders"));
        this->transition(new Command("endissueorders"));
        this->transition(new Command("execorder"));
        this->transition(new Command("endexecorders"));

        //Check to see if players owns a territory, if they dont remove them from game
        for (int i = 0; i < Players.size()-1; i++) {
            if (Players.at(i)->getTerritorySize() == 0) {
                //delete this player from the vector
                Players.erase(Players.begin() + i);
            }
        }

        //Check to see if final player owns all territories on the map
        if (Players.size() == 1) {
            int doneCounter = 0;
            for (int i = 0; i < gameMap.numberOfTerritoriesPerContinent.size()-1; i++) {
                if (Players.at(0)->getTerritoriesOwnedPerContinent().at(i) == gameMap.numberOfTerritoriesPerContinent.at(i)) {
                    doneCounter++;
                }
            }
            if (doneCounter == gameMap.continents.size()) {
                //if there are neutral territories then he might not win
                noWinner = true;
                cout << "The winner is " << Players.at(0)->getName();
            }
            //TODO final player can request to end the game
        }
    }
    this->transition(new Command("win"));
}

void GameEngine::reinforcementPhase() {
    this->currentState = ST_ASSIGN_REINFORCEMENT;
    //Adds armies to the reinforcement pool
    for (int i = 0; i < Players.size(); i++) {
        //sets the number of armies based on territory size
        int numArmies = floor(Players.at(i)->getTerritorySize() / 3);
        Players.at(i)->addReinforcements(numArmies);

        for (int j = 0; j < gameMap.numberOfTerritoriesPerContinent.size()-1; j++) {
            if (gameMap.numberOfTerritoriesPerContinent.at(j) == Players.at(i)->getTerritoriesOwnedPerContinent().at(j)) {
                //give reward
                Players.at(i)->setReinforcements(Players.at(i)->getReinforcements() +
                                                    gameMap.continents.at(j)->territorialReward);
            }
        }
    }
}

void GameEngine::issueOrdersPhase() {
    //loop through each player and allow them to issue orders
    for (int i = 0; i < Players.size(); i++) {
        cout << endl << Players.at(i)->getName() << "\'s turn to issue orders:\n\n";
        Players.at(i)->issueOrder(Players);
    }
}

void GameEngine::executeOrdersPhase() {
    //TODO destroy all the pointers
    //Order of execution is which order was passed into the orderslist first
    cout << "\nExecuting orders:" << endl;
    for (int i = 0; i < Players.size(); i++) {
        cout << Players.at(i)->getName() << "\'s orders:" << endl;
        int numberOfOrders = Players.at(i)->getOrdersList()->getList().size();
        for (int j = 0; j < numberOfOrders; j++) {
            //validates the order and executes the order if it is good.
            Players.at(i)->getOrdersList()->getList().at(0)->validate(*Players.at(i));
            Players.at(i)->getOrdersList()->remove(0);
        }
    }
    for (int i = 0; i < Players.size(); i++) {
        for (int j = 0; j < Players.at(i)->negotiatingWith.size(); j++) {
            Players.at(i)->removeNegotiations(j);
        }
    }
}
//end ryan