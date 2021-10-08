//
// Created by Nicolo on 2021-09-24.
//
#include <string>
#include <iostream>
#include "GameEngineDriver.h"

using namespace std;
/* Grading sheet Part 5: Game Engine
  [x] The state of the game is held as a data member of the GameEngine class.
  [x] Console input is used to get commands from the user.
  [x] Depending on the command and the state, a transition is made to another state by changing the value held by the state variable.
  [x] If the user enter an invalid command for the current state, the command is rejected and an error message is output to the console.
  [x] The state transitions are implemented exactly as depicted in the assignment handout.
  [x] All data members of user-defined class type are of pointer type.
  [x] Classes declared in header file. Functions implemented in cpp file. Absence of inline functions.
  [ ] All classes implement a correct copy constructor, assignment operator, and stream insertion operator.
  [ ] Absence of memory leaks.
  [ ] Driver clearly demonstrates that commands can be used to navigate through the different states as depicted in the assignment handout.
 * TODO
 * [ ] ask if enums can be defined in .h file
 */

// constructors
GameEngineDriver::GameEngineDriver(): isGameDone(false) {
    cout << "executing constructor with no params from GameEngineDriver class" << endl;
    this->game = new GameEngine();
}

// copy constructor
GameEngineDriver::GameEngineDriver(const GameEngineDriver &gameEngineDriver) : isGameDone(false) {
    cout << "executing copy constructor from GameEngineDriver class" << endl;
    this->game = new GameEngine(gameEngineDriver.game);
}

// destructor
GameEngineDriver:: ~GameEngineDriver() = default;

// validates user input and calls appropriate transition
void GameEngineDriver::chooseCommand() {

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
            if(game->transition(T_LOAD_MAP)) {
                flag = 1;
            } else {
                flag = 0;
                error = "cannot perform transition '" + input + "' from state '" + game->getState() + "'!";
            }
        } else if(input== "validatemap") {
            if(game->transition(T_VALIDATE_MAP)) {
                flag = 1;
            } else {
                flag = 0;
                error = "cannot perform transition '" + input + "' from state '" + game->getState() + "'!";
            }
        } else if(input== "addplayer") {
            if(game->transition(T_ADD_PLAYER)) {
                flag = 1;
            } else {
                flag = 0;
                error = "cannot perform transition '" + input + "' from state '" + game->getState() + "'!";
            }
        } else if(input== "assigncountries") {
            if(game->transition(T_ASSIGN_COUNTRIES)) {
                flag = 1;
            } else {
                flag = 0;
                error = "cannot perform transition '" + input + "' from state '" + game->getState() + "'!";
            }
        } else if(input== "issueorder") {
            if(game->transition(T_ISSUE_ORDER)) {
                flag = 1;
            } else {
                flag = 0;
                error = "cannot perform transition '" + input + "' from state '" + game->getState() + "'!";
            }
        } else if(input== "execorder") {
            if(game->transition(T_EXEC_ORDER)) {
                flag = 1;
            } else {
                flag = 0;
                error = "cannot perform transition '" + input + "' from state '" + game->getState() + "'!";
            }
        } else if(input== "endexecorders") {
            if(game->transition(T_END_EXEC_ORDERS)) {
                flag = 1;
            } else {
                flag = 0;
                error = "cannot perform transition '" + input + "' from state '" + game->getState() + "'!";
            }
        } else if(input== "endissueorders") {
            if(game->transition(T_END_ISSUE_ORDERS)) {
                flag = 1;
            } else {
                flag = 0;
                error = "cannot perform transition '" + input + "' from state '" + game->getState() + "'!";
            }
        } else if(input== "win") {
            if(game->transition(T_WIN)) {
                flag = 1;
            } else {
                flag = 0;
                error = "cannot perform transition '" + input + "' from state '" + game->getState() + "'!";
            }
        } else if(input== "end") {
            if(game->transition(T_END)) {
                flag = 1;
            } else {
                flag = 0;
                error = "cannot perform transition '" + input + "' from state '" + game->getState() + "'!";
            }

            if(flag == 1) {
                isGameDone = true;
            }
        } else if(input== "play") {
            if(game->transition(T_PLAY)) {
                flag = 1;
            } else {
                flag = 0;
                error = "cannot perform transition '" + input + "' from state '" + game->getState() + "'!";
            }
        } else {
            error = "'" + input + "' is an invalid transition!";
        }

        if (flag == 0){
            cout << error << endl;
            error = "";
        }
    }
}

GameEngineDriver& GameEngineDriver::operator =(const GameEngineDriver &ged) {
    cout << "using assignment operator '=' from GameEngineDriver class" << endl;
    this->game = new GameEngine(ged.game);
    return *this;
}


ostream & operator << (ostream &out, const GameEngineDriver &ged)
{
    cout << "using ostream operator '<<' from GameEngineDriver class" << endl;
    if(ged.isGameDone)
        out << "isGameDone: true " << *ged.game << endl;
    else
        out << "isGameDone: false " << *ged.game << endl;
    return out;
}

// TODO if game engine handles receiving input, what should gameenginedriver allow as input?
istream & operator >> (istream &in,  GameEngineDriver &ged)
{
    cout << "using istream operator '>>' from GameEngineDriver class" << endl;
    cout << "Enter SOIMETHING ";
    in >> ged.isGameDone;
    return in;
}

