//
// Created by Nicolo on 2021-09-24.
//
#include "GameEngine.h"
#include "CommandProcessing.h"

using namespace std;

// constructor
GameEngine::GameEngine() : isGameDone(false), currentState(ST_START) {
    cout << "GameEngine constructor called" << endl;
}

// copy constructors
GameEngine::GameEngine(const GameEngine &game) : isGameDone(false), currentState(game.currentState) {
    cout << "GameEngine copy constructor called" << endl;
}

GameEngine::GameEngine(GameEngine *const pGameEngine) : isGameDone(false), currentState(pGameEngine->currentState) {
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
    } else if (command == "addplayer") {
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

    /*
         try {
             throw T_ERROR;
         } catch (Transition t) {
             cout << " An error has occurred. Exception: '" << t << "'" << endl;
         }
         */
    return false;
}

// return enum value currentState
State GameEngine::getState() {
    return currentState;
}

void GameEngine::loadmap(Command *c) {
    /*
    cout << "Chose between any of the following files:\n" <<
        "1: Europe\n"<<
        "2: Canada\n"<<
        "3: Zertina\n"<<endl;
*/
    string command = c->getCommand(); //command = "loadmap zertina.map"
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
    cout << "Validating Map";
    if (gameMap.Validate())
        cout << "Map is valid";
    else {
        cout << "Map is not valid";
        exit(0);
    }
}

void GameEngine::addplayer(Command *c) {

    // get the name from command object
    string *name = new string((c->getCommand()).substr(10));
    Player *newPlayer = new Player(name);
    newPlayer->setReinforcements(50);
    Players.push_back(newPlayer);


    //shuffle(Players.begin(), Players.end(), 15); todo uncommment
}

void GameEngine::gamestart() {
    *MainDeck = *new Deck(Players.size());
    for (auto &Player: Players) {
        MainDeck->Draw(Player->getHand());
        MainDeck->Draw(Player->getHand());
    }
    assigncountries();
}

void GameEngine::assigncountries() {
    for (int i = 0; i < gameMap.map.size(); i++) {
        Players.at(i % Players.size())->addTerritory(gameMap.map.at(i));
    }
}

void GameEngine::issueorder() {
    //transition(T_ISSUE_ORDER);
    cout << "Executing function issueorder" << endl;
}

void GameEngine::execorder() {
    //transition(T_EXEC_ORDER);
    cout << "Executing function execorder" << endl;
}

void GameEngine::endexecorders() {
    //transition(T_END_EXEC_ORDERS);
    cout << "Executing function endexecorders" << endl;
}

void GameEngine::endissueorders() {
    //transition(T_END_ISSUE_ORDERS);
    cout << "Executing function endissueorders" << endl;
}

void GameEngine::win() {
    //transition(T_WIN);
    cout << "Executing function win" << endl;
}

void GameEngine::end() {
    //transition(T_END);
    cout << "Executing function end" << endl;
}

void GameEngine::play() {
    //transition(T_PLAY);
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

        // stop startup phase once game started
        if (commandName == "gamestart") {
            break;
        } else {
            transition(c);
        }
    }
}

//added by ryan
//vector<Territory *> generateTerritories(int numTerritoryOwned);
//vector<Hand *> generateHand(int numberCardsPerPlayer);
//
//static int territoryNumber = 1;
//static int cardNumber = 1;
//static const int territoriesOwnedPerPlayer = 5;
//static const int numCardsPerPlayer = 3;
//
//vector<Territory *> generateTerritories(int numTerritoryOwned) {
//    vector<Territory *> vTerritory;
//    Territory *pPlayerTerritory;
//    for (int i = 0; i < numTerritoryOwned; i++) {
//        pPlayerTerritory = new Territory(i, "Territory " + to_string(territoryNumber), 1);
//        vTerritory.push_back(pPlayerTerritory);
//        territoryNumber++;
//    }
//    return vTerritory;
//}
//
///**
// * Generates the cards for each player
// *
// * @param numCardsPerPlayer the initial amount of cards per player
// * @return vector of Hands that gets passed into the player vector
// */
//vector<Hand *> generateHand(int numberCardsPerPlayer) {
//    vector<Hand *> vHand;
//    Hand *pHand;
//    for (unsigned i = 0; i < numberCardsPerPlayer; i++) {
//        pHand = new Hand();
//        pHand->ReceiveCard(new Card( "Bomb"));
//        vHand.push_back(pHand);
//        cardNumber++;
//    }
//    return vHand;
//}

void GameEngine::mainGameLoop(vector<Player*> & vPlayersInPlay) {
    //TODO Load map here

    //TODO this must be done right after the map loads and the players are chosen. Run only once
    for (int i = 0; i < Players.size(); ++i) {
        gameMap.countTerritoriesPerContinent();
        Players.at(i)->setTerritoriesOwnedPerContinent(
                gameMap.numberOfTerritoriesPerContinent.size());

    }

    bool noWinner = false;

    while (!noWinner) {

        reinforcementPhase();
        //Check to see if players owns a territory
        for (int i = 0; i < Players.size(); ++i) {
            if (Players.at(i)->getTerritorySize() == 0) {
                //delete this player from the vector
                Players.erase(Players.begin() + i);
            }
        }

        issueOrdersPhase(vPlayersInPlay);
        executeOrdersPhase(vPlayersInPlay);

        //Check to see if final player owns all territories on the map
        if (Players.size() == 1) {
            int doneCounter = 0;
            for (int i = 0; i < gameMap.numberOfTerritoriesPerContinent.size(); ++i) {
                if (Players.at(0)->getTerritoriesOwnedPerContinent().at(i) == gameMap.numberOfTerritoriesPerContinent.at(i)) {
                    doneCounter++;
                }
            }
            if (doneCounter == gameMap.continents.size()) {
                //if there are neutral territories then he might not win
                noWinner = true;
                cout << "The winner is " << Players.at(0)->getName();
            }
        }

    }
}

void GameEngine::reinforcementPhase() {

    for (int i = 0; i < Players.size(); ++i) {
        //sets the number of armies based on territory size
        int numArmies = floor(Players.at(i)->getTerritorySize() / 3);
        Players.at(i)->setReinforcements(numArmies);

        for (int i = 0; i < gameMap.numberOfTerritoriesPerContinent.size(); ++i) {
            if (gameMap.numberOfTerritoriesPerContinent.at(i) == Players.at(i)->getTerritoriesOwnedPerContinent().at(i)) {
                //give reward
                Players.at(i)->setReinforcements(Players.at(i)->getReinforcements() +
                                                    gameMap.continents.at(i)->territorialReward);
            }
        }
    }

}

void GameEngine::issueOrdersPhase(vector<Player*> &vPlayersInPlay) {
    //loop through each player and allow them to issue orders
    for (int i = 0; i < vPlayersInPlay.size(); ++i) {
        vPlayersInPlay.at(i)->issueOrder(vPlayersInPlay);
    }
}

void GameEngine::executeOrdersPhase(vector<Player*> &vPlayersInPlay) {
    //TODO destroy all the pointers
    //Order of execution is which order was passed into the orderslist first
    for (int i = 0; i < vPlayersInPlay.size(); ++i) {
        for (int j = 0; j < vPlayersInPlay.at(i)->getOrdersList()->getList().size(); ++j) {
            //validates the order and executes the order if it is good.
            vPlayersInPlay.at(i)->getOrdersList()->getList().at(j)->validate(vPlayersInPlay.at(i));
        }
    }
}
//end ryan