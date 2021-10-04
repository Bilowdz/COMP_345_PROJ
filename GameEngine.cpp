//
// Created by Nicolo pt 2 on 2021-09-24.
//
#include <iostream>
#include "GameEngine.h"
using namespace std;

// constructor
GameEngine::GameEngine() {
    currentState = ST_START;
    cout << "executing constructor with no params from GameEngine class" << endl;
}

// copy constructors
GameEngine::GameEngine(const GameEngine &game) {
    cout << "executing copy constructor from GameEngine class" << endl;
    currentState = game.currentState;
}

GameEngine::GameEngine(GameEngine *const pGameEngine) {
    cout << "executing copy constructor from GameEngine class (pointer)" << endl;
    currentState = pGameEngine->currentState;
}

// destructor
GameEngine:: ~GameEngine() {
    /* TODO what to implement here? */
    cout << "executing destructor operation from GameEngine class" << endl;
}

// handles state transitions
bool GameEngine::transition(Transition t) {
    switch(t) {
        case T_LOAD_MAP:
            if(currentState == ST_START || currentState == ST_MAP_LOADED) {
                // valid input, transition to state map loaded
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
                return true;
            }
            break;
        default:
            cout << "throw error!" << endl;
            break;
    }
    return false;
}

void GameEngine::loadmap() {
    cout << "executing function loadmap" << endl;
}

void GameEngine::validatemap() {
    cout << "executing function validatemap" << endl;
}

void GameEngine::addplayer() {
    cout << "executing function addplayer" << endl;
}

void GameEngine::assigncountries() {
    cout << "executing function assigncountries" << endl;
}

void GameEngine::issueorder() {
    cout << "executing function issueorder" << endl;
}

void GameEngine::execorder() {
    cout << "executing function execorder" << endl;
}

void GameEngine::endexecorders() {
    cout << "executing function endexecorders" << endl;
}

void GameEngine::endissueorders() {
    cout << "executing function endissueorders" << endl;
}

void GameEngine::win() {
    cout << "executing function win" << endl;
}

void GameEngine::end() {
    cout << "executing function end" << endl;
}

void GameEngine::play() {
    cout << "executing function play" << endl;
}

// assignment operator overload
GameEngine& GameEngine::operator =(const GameEngine &ge) {
    cout << "using assignment operator '=' from GameEngine class" << endl;
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
            out << "throw error!" << endl;
            break;
    }
    return out;
}


// TODO how do i allow user to input from a string to an enum?
istream & operator >> (istream &in,  GameEngine &ge)
{
    cout << "Enter Current State ";
    //in >> ge.currentState;
    return in;
}