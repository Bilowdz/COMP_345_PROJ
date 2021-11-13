//
// Created by Nicolo on 2021-09-24.
//
#include <iostream>
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
    cout << "Executing function loadmap" << endl;
}

void GameEngine::validatemap() {
    cout << "Executing function validatemap" << endl;
}

void GameEngine::addplayer() {
    cout << "Executing function addplayer" << endl;
}

void GameEngine::assigncountries() {
    cout << "Executing function assigncountries" << endl;
}

void GameEngine::issueorder() {
    cout << "Executing function issueorder" << endl;
}

void GameEngine::execorder() {
    cout << "Executing function execorder" << endl;
}

void GameEngine::endexecorders() {
    cout << "Executing function endexecorders" << endl;
}

void GameEngine::endissueorders() {
    cout << "Executing function endissueorders" << endl;
}

void GameEngine::win() {
    cout << "Executing function win" << endl;
}

void GameEngine::end() {
    cout << "Executing function end" << endl;
}

void GameEngine::play() {
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