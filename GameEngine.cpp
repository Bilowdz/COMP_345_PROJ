//
// Created by Nicolo on 2021-09-24.
//
#include "GameEngine.h"
using namespace std;

// constructor
GameEngine::GameEngine(): isGameDone(false), currentState(ST_START) {
    cout << "GameEngine constructor called" << endl;
}

// copy constructors
GameEngine::GameEngine(const GameEngine &game): isGameDone(false), currentState(game.currentState) {
    cout << "GameEngine copy constructor called" << endl;
}

GameEngine::GameEngine(GameEngine *const pGameEngine): isGameDone(false), currentState(pGameEngine->currentState) {
    cout << "GameEngine copy constructor 2 called" << endl;

}

// destructor
GameEngine:: ~GameEngine() = default;

// validate and execute transitions based on current state
bool GameEngine::transition(string command) {
    string loadmap = "loadmap";
    string addplayer = "addplayer";

    if(command.rfind(loadmap,0) == 0) {
        // only transition from valid states
        if(currentState == ST_START || currentState == ST_MAP_LOADED) {

            // valid transition to state map loaded, so travel to state
            currentState = ST_MAP_LOADED;

            // execute game engine function
            this->loadmap();
            return true;
        }
    }else if(command == "validatemap") {
        if(currentState == ST_MAP_LOADED) {
            currentState = ST_MAP_VALIDATED;
            this->validatemap();
            return true;
        }
    }else if(command == "addplayer") {
        if(currentState == ST_MAP_VALIDATED || currentState == ST_PLAYERS_ADDED) {
            currentState = ST_PLAYERS_ADDED;
            this->addplayer();
            return true;
        }
    }else if(command == "assigncountries") {
        if(currentState == ST_PLAYERS_ADDED) {
            currentState = ST_ASSIGN_REINFORCEMENT;
            this->assigncountries();
            return true;
        }
    }else if(command == "issueorders") {
        if(currentState == ST_ASSIGN_REINFORCEMENT || currentState == ST_ISSUE_ORDERS) {
            currentState = ST_ISSUE_ORDERS;
            this->issueorder();
            return true;
        }
    }else if(command == "endissueorders") {
        if(currentState == ST_ISSUE_ORDERS) {
            currentState = ST_EXECUTE_ORDERS;
            this->endissueorders();
            return true;
        }
    }else if(command == "execorder") {
        if(currentState == ST_ISSUE_ORDERS || currentState == ST_EXECUTE_ORDERS) {
            currentState = ST_EXECUTE_ORDERS;
            this->execorder();
            return true;
        }
    }else if(command == "endexecorders") {
        if(currentState == ST_EXECUTE_ORDERS) {
            currentState = ST_ASSIGN_REINFORCEMENT;
            this->endexecorders();
            return true;
        }
    }else if(command == "win") {
        if(currentState == ST_EXECUTE_ORDERS) {
            currentState = ST_WIN;
            this->win();
            return true;
        }
    }else if(command == "play") {
        if(currentState == ST_WIN) {
            currentState = ST_START;
            this->play();
            return true;
        }
    }else if(command == "end") {
        if(currentState == ST_WIN) {
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

void GameEngine::loadmap() {
    transition("loadmap");
    cout << "Chose between any of the following files:\n" <<
        "1: Europe\n"<<
        "2: Canada\n"<<
        "3: Zertina\n"<<endl;
    int mapChosen;
    cin >> mapChosen;
    MapLoader load;
    gameMap = *load.maps.at(mapChosen-1);
}

void GameEngine::validatemap() {
    transition("validatemap");
    cout << "Validating Map";
    if(gameMap.Validate())
        cout << "Map is valid";
    else {
        cout << "Map is not valid";
        exit(0);
    }
}

void GameEngine::addplayer() {
    transition("addplayer");
    cout << "How many players do you want to add" << endl;
    int numPlayers;
    cin >> numPlayers;
    for(int i = 0; i < numPlayers; i++)
    {
        cout << "Select a name for this player";
        string *name;
        cin >> *name;
        Players.push_back(new Player(name));
    }

    //shuffle(Players.begin(), Players.end(), 15); todo uncommment
}

void GameEngine::gamestart() {
    *MainDeck = *new Deck(Players.size());
    for(auto & Player : Players){
       MainDeck->Draw(Player->vHand);
       MainDeck->Draw(Player->vHand);
    }
    assigncountries();
}

void GameEngine::assigncountries() {
    transition("assigncountries");
    for(int i = 0; i < gameMap.map.size(); i++)
    {
        Players.at(i%Players.size())->vTerritory.push_back(gameMap.map.at(i));
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
GameEngine& GameEngine::operator =(const GameEngine &ge) {
    this->currentState = ge.currentState;

    return *this;
}

// stream insertion operator overloads
ostream & operator << (ostream &out, const GameEngine &ge)
{
    out << "Current State:" << enum_state_str[ge.currentState] << endl;
    return out;
}

void GameEngine::startupPhase(){
    loadmap();
    validatemap();
    addplayer();
    gamestart();
}


