//
// Created by Nicolo on 2021-09-24.
//
#include "GameEngine.h"
using namespace std;

// constructor
GameEngine::GameEngine(): isGameDone(false), currentState(ST_START) {}

// copy constructors
GameEngine::GameEngine(const GameEngine &game): isGameDone(false), currentState(game.currentState) {}

GameEngine::GameEngine(GameEngine *const pGameEngine): isGameDone(false), currentState(pGameEngine->currentState) {}

// destructor
GameEngine:: ~GameEngine() = default;

// validate and execute transitions based on current state
bool GameEngine::transition(Transition t) {
    switch(t) {
        case T_LOAD_MAP:

            // only transition from valid states
            if(currentState == ST_START || currentState == ST_MAP_LOADED) {

                    // valid transition to state map loaded, so travel to state
                    currentState = ST_MAP_LOADED;

                // execute game engine function
                this->loadmap();
                return true;
            }

            break;
        case T_VALIDATE_MAP:
            if(currentState == ST_MAP_LOADED) {
                currentState = ST_MAP_VALIDATED;
                this->validatemap();
                return true;
            }

            break;

        case T_ADD_PLAYER:
            if(currentState == ST_MAP_VALIDATED || currentState == ST_PLAYERS_ADDED) {
                currentState = ST_PLAYERS_ADDED;
                this->addplayer();
                return true;
            }
            break;
        case T_ASSIGN_COUNTRIES:
            if(currentState == ST_PLAYERS_ADDED) {
                currentState = ST_ASSIGN_REINFORCEMENT;
                this->assigncountries();
                return true;
            }
            break;
        case T_ISSUE_ORDER:
            if(currentState == ST_ASSIGN_REINFORCEMENT || currentState == ST_ISSUE_ORDERS) {
                currentState = ST_ISSUE_ORDERS;
                this->issueorder();
                return true;
            }
            break;
        case T_END_ISSUE_ORDERS:
            if(currentState == ST_ISSUE_ORDERS) {
                currentState = ST_EXECUTE_ORDERS;
                this->endissueorders();
                return true;
            }
            break;
        case T_EXEC_ORDER:
            if(currentState == ST_ISSUE_ORDERS || currentState == ST_EXECUTE_ORDERS) {
                currentState = ST_EXECUTE_ORDERS;
                this->execorder();
                return true;
            }
            break;
        case T_END_EXEC_ORDERS:
            if(currentState == ST_EXECUTE_ORDERS) {
                currentState = ST_ASSIGN_REINFORCEMENT;
                this->endexecorders();
                return true;
            }
            break;
        case T_WIN:
            if(currentState == ST_EXECUTE_ORDERS) {
                currentState = ST_WIN;
                this->win();
                return true;
            }
            break;
        case T_PLAY:
            if(currentState == ST_WIN) {
                currentState = ST_START;
                this->play();
                return true;
            }
            break;
        case T_END:
            if(currentState == ST_WIN) {
                currentState = ST_END;
                this->end();
                this->isGameDone = true;
                return true;
            }
            break;
        default:
            try {
                throw T_ERROR;
            } catch (Transition t) {
                cout << " An error has occurred. Exception: '" << t << "'" << endl;
            }
    }
    return false;
}

// return string equivalent of enum value currentState
string GameEngine::getState() {
    switch(currentState) {
        case ST_START:
            return "start";
        case ST_MAP_LOADED:
            return "maploaded";
        case ST_MAP_VALIDATED:
            return "mapvalidated";
        case ST_PLAYERS_ADDED:
            return "playersadded";
        case ST_ASSIGN_REINFORCEMENT:
            return "assignreinforcement";
        case ST_ISSUE_ORDERS:
            return "issueorders";
        case ST_EXECUTE_ORDERS:
            return "executeorders";
        case ST_WIN:
            return "win";
        case ST_END:
            return "end";
        default:
            return "error";
    }
}

void GameEngine::loadmap() {
    transition(T_LOAD_MAP);

    cout << "Chose between any of the following files:\n" <<
        "1: Europe\n"<<
        "2: Canada\n"<<
        "3: Middle Earth\n"<<
        "4: Broken Map\n"<<
        "5: Zertina\n"<<endl;
    int mapChosen;
    cin >> mapChosen;
    MapLoader load;
    switch (mapChosen) {
        case 1:
            load.Load("Maps/bigeurope.map");
            break;
        case 2:
            load.Load("Maps/canada.map");
            break;
        case 3:
            load.Load("Maps/middleearth.map");
            break;
        case 4:
            load.Load("Maps/bigeurope.map");
            break;
        case 5:
            load.Load("Maps/bigeurope.map");
            break;
        default:
            cout << "Incorrect input";
            exit(0);
    }
    gameMap = *load.maps.at(0);

}

void GameEngine::validatemap() {
    transition(T_VALIDATE_MAP);
    cout << "Validating Map";
    if(gameMap.Validate())
        cout << "Map is valid";
    else {
        cout << "Map is not valid";
        exit(0);
    }
}

void GameEngine::addplayer() {
    transition(T_ADD_PLAYER);
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

    std::random_shuffle(Players.begin(), Players.end(), 15);

}

void GameEngine::assigncountries() {
    transition(T_ASSIGN_COUNTRIES);
    cout << "Executing function assigncountries" << endl;
}

void GameEngine::issueorder() {
    transition(T_ISSUE_ORDER);
    cout << "Executing function issueorder" << endl;
}

void GameEngine::execorder() {
    transition(T_EXEC_ORDER);
    cout << "Executing function execorder" << endl;
}

void GameEngine::endexecorders() {
    transition(T_END_EXEC_ORDERS);
    cout << "Executing function endexecorders" << endl;
}

void GameEngine::endissueorders() {
    transition(T_END_ISSUE_ORDERS);
    cout << "Executing function endissueorders" << endl;
}

void GameEngine::win() {
    transition(T_WIN);
    cout << "Executing function win" << endl;
}

void GameEngine::end() {
    transition(T_END);
    cout << "Executing function end" << endl;
}

void GameEngine::play() {
    transition(T_PLAY);
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
    switch(ge.currentState) {

        case ST_START:
            out << "Current State: start" << endl;
            break;
        case ST_MAP_LOADED:
            out << "Current State: maploaded" << endl;
            break;
        case ST_MAP_VALIDATED:
            out << "Current State: mapvalidated" << endl;
            break;
        case ST_PLAYERS_ADDED:
            out << "Current State: playersadded" << endl;
            break;
        case ST_ASSIGN_REINFORCEMENT:
            out << "Current State: assignreinforcement" << endl;
            break;
        case ST_ISSUE_ORDERS:
            out << "Current State: issueorders" << endl;
            break;
        case ST_EXECUTE_ORDERS:
            out << "Current State: executeorders" << endl;
            break;
        case ST_WIN:
            out << "Current State: win" << endl;
            break;
        case ST_END:
            out << "Current State: end" << endl;
            break;
        default:
            try {
                throw ST_ERROR;
            } catch (State s) {
                cout << " An error has occurred. Exception: '" << s << "'" << endl;
            }            break;
    }
    return out;
}

void GameEngine::startupPhase(){
    loadmap();
    validatemap();

}