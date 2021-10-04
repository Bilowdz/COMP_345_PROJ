//
// Created by Nicolo pt 2 on 2021-09-24.
//
#include <string>
#include <iostream>
#include "GameEngineDriver.h"

using namespace std;
/* Grading sheet Part 5: Game Engine
  [ ] The state of the game is held as a data member of the GameEngine class.
  [ ] Console input is used to get commands from the user.
  [ ] Depending on the command and the state, a transition is made to another state by changing the value held by the state variable.
  [ ] If the user enter an invalid command for the current state, the command is rejected and an error message is output to the console.
  [ ] The state transitions are implemented exactly as depicted in the assignment handout.
  [ ] All data members of user-defined class type are of pointer type.
  [ ] Classes declared in header file. Functions implemented in cpp file. Absence of inline functions.
  [ ] All classes implement a correct copy constructor, assignment operator, and stream insertion operator.
  [ ] Absence of memory leaks.
  [ ] Driver clearly demonstrates that commands can be used to navigate through the different states as depicted in the assignment handout.
 * TODO
 * [ ] ask if enums can be defined in .h file
 * [ ] TEST copy constructor
 * [ ] TEST assignment operator
 * [ ] TEST stream insertion  operator
 */

// constructors
GameEngineDriver::GameEngineDriver(): isGameDone(false) {
    cout << "executing constructor with no params from GameEngineDriver class" << endl;
    game = new GameEngine();
}

// copy constructor
GameEngineDriver::GameEngineDriver(const GameEngineDriver &gameEngineDriver) : isGameDone(false) {
    cout << "executing copy constructor from GameEngineDriver class" << endl;
    game = gameEngineDriver.game;
}

// destructor
GameEngineDriver:: ~GameEngineDriver() {
    cout << "executing destructor operation from GameEngineDriver class" << endl;
    delete game;
}

// main function
/*
void GameEngineDriver::start() {
    std::cout << "running driver class" << std::endl;

    GameEngine game;
    chooseCommand(&game.currentState, game);
}

*/

// validates user input and calls appropriate transition
void GameEngineDriver::chooseCommand() {

    // flag changed to 1 when valid input selected by user
    int flag = 0;

    // accept user input until valid user input selected
    while(flag == 0) {
        std::string input;

        cout << "Please choose an option:";
        // get user input
        cin >> input;

        // check if valid input
        if(input == "loadmap") {
            flag = (game->transition(T_LOAD_MAP)) ? 1 : 0;
        } else if(input== "validatemap") {
            flag = (game->transition(T_VALIDATE_MAP)) ? 1 : 0;
        } else if(input== "addplayer") {
            flag = (game->transition(T_ADD_PLAYER)) ? 1 : 0;
        } else if(input== "assigncountries") {
            flag = (game->transition(T_ASSIGN_COUNTRIES)) ? 1 : 0;
        } else if(input== "issueorder") {
            flag = (game->transition(T_ISSUE_ORDER)) ? 1 : 0;
        } else if(input== "execorder") {
            flag = (game->transition(T_EXEC_ORDER)) ? 1 : 0;
        } else if(input== "endexecorders") {
            flag = (game->transition(T_END_EXEC_ORDERS)) ? 1 : 0;
        } else if(input== "endissueorders") {
            flag = (game->transition(T_END_ISSUE_ORDERS)) ? 1 : 0;
        } else if(input== "win") {
            flag = (game->transition(T_WIN)) ? 1 : 0;
        } else if(input== "end") {
            flag = (game->transition(T_END)) ? 1 : 0;

            if(flag == 1) {
                isGameDone = true;
            }
        } else if(input== "play") {
            flag = (game->transition(T_PLAY)) ? 1 : 0;
        }

        if (flag == 0){
            cout << "invalid choice!" << endl;
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
    if(ged.isGameDone)
        out << "isGameDone: true " << ged.game << endl;
    else
        out << "isGameDone: false " << ged.game << endl;
    return out;
}

// TODO how do i allow user to input from a string to an enum?
istream & operator >> (istream &in,  GameEngineDriver &ged)
{
    cout << "Enter SOIMETHING ";
    //in >> ged.;
    return in;
}

