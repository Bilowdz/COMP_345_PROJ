//
// Created by Nicolo on 2021-09-24.
//
#include <string>
#include <iostream>
#include "GameEngineDriver.h"

using namespace std;
// constructors
GameEngineDriver::GameEngineDriver(): game(new GameEngine()) {}

// copy constructor
GameEngineDriver::GameEngineDriver(const GameEngineDriver &gameEngineDriver): game(new GameEngine(gameEngineDriver.game)) {}

// destructor
GameEngineDriver:: ~GameEngineDriver() {
    delete this->game;
}

// assignment operator overload
GameEngineDriver& GameEngineDriver::operator =(const GameEngineDriver &ged) {
    this->game = new GameEngine(ged.game);
    return *this;
}
bool GameEngineDriver::isGameDone() {
    return game->isGameDone;
}


// stream insertion operators overload

ostream & operator << (ostream &out, const GameEngineDriver &ged) {
    if(ged.game->isGameDone)
        out << "isGameDone: true " << *ged.game << endl;
    else
        out << "isGameDone: false " << *ged.game << endl;
    return out;
}

// validates user input and calls appropriate transition
istream & operator >> (istream &in,  GameEngineDriver &ged) {
    // flag changed to 1 when valid input selected by user
    int flag = 0;

    // accept user input until valid user input selected
    while(flag == 0) {
        string input;
        string error;
        cout << "Please choose an option:";
        // get user input
        cin >> input;

        // check if valid input
        if(input == "loadmap") {
            if(ged.game->transition(T_LOAD_MAP)) {
                flag = 1;
            } else {
                error = "cannot perform transition '" + input + "' from state '" + ged.game->getState() + "'!";
            }
        } else if(input== "validatemap") {
            if(ged.game->transition(T_VALIDATE_MAP)) {
                flag = 1;
            } else {
                error = "cannot perform transition '" + input + "' from state '" + ged.game->getState() + "'!";
            }
        } else if(input== "addplayer") {
            if(ged.game->transition(T_ADD_PLAYER)) {
                flag = 1;
            } else {
                error = "cannot perform transition '" + input + "' from state '" + ged.game->getState() + "'!";
            }
        } else if(input== "assigncountries") {
            if(ged.game->transition(T_ASSIGN_COUNTRIES)) {
                flag = 1;
            } else {
                error = "cannot perform transition '" + input + "' from state '" + ged.game->getState() + "'!";
            }
        } else if(input== "issueorder") {
            if(ged.game->transition(T_ISSUE_ORDER)) {
                flag = 1;
            } else {
                error = "cannot perform transition '" + input + "' from state '" + ged.game->getState() + "'!";
            }
        } else if(input== "execorder") {
            if(ged.game->transition(T_EXEC_ORDER)) {
                flag = 1;
            } else {
                error = "cannot perform transition '" + input + "' from state '" + ged.game->getState() + "'!";
            }
        } else if(input== "endexecorders") {
            if(ged.game->transition(T_END_EXEC_ORDERS)) {
                flag = 1;
            } else {
                error = "cannot perform transition '" + input + "' from state '" + ged.game->getState() + "'!";
            }
        } else if(input== "endissueorders") {
            if(ged.game->transition(T_END_ISSUE_ORDERS)) {
                flag = 1;
            } else {
                error = "cannot perform transition '" + input + "' from state '" + ged.game->getState() + "'!";
            }
        } else if(input== "win") {
            if(ged.game->transition(T_WIN)) {
                flag = 1;
            } else {
                error = "cannot perform transition '" + input + "' from state '" + ged.game->getState() + "'!";
            }
        } else if(input== "end") {
            if(ged.game->transition(T_END)) {
                flag = 1;

            } else {
                error = "cannot perform transition '" + input + "' from state '" + ged.game->getState() + "'!";
            }

        } else if(input== "play") {
            if(ged.game->transition(T_PLAY)) {
                flag = 1;
            } else {
                error = "cannot perform transition '" + input + "' from state '" + ged.game->getState() + "'!";
            }
        } else {
            error = "'" + input + "' is an invalid transition!";
        }

        if (flag == 0){
            cout << error << endl;
            error = "";
        }
    }
    return in;
}

