//
// Created by Nicolo pt 2 on 2021-09-24.
//
#include <string>
#include <iostream>
#include "GameEngineDriver.h"

using namespace std;

GameEngineDriver::GameEngineDriver() {
    start();
}

// main function
void GameEngineDriver::start() {
    std::cout << "running driver class" << std::endl;

    GameEngine game;
    chooseCommand(&game.currentState, game);
}

// validates user commands using state/transitions
void GameEngineDriver::chooseCommand(State* currentState, GameEngine game) {

    // flag changed to 1 when valid input selected by user
    int flag = 0;

    // accept user input until valid user input selected
    while(flag == 0) {
        std::string input;

        cout << "Please choose an option:";
        // get user input
        cin >> input;

        // check if valid input/transition
        if(input == "loadmap" && (*currentState == ST_START || *currentState == ST_MAP_LOADED)) {

            // valid input, transition to state map loaded
            *currentState = ST_MAP_LOADED;

            // execute game engine function
            game.loadmap();

            // valid input, leave while loop
            flag = 1;
        } else if(input== "validatemap" && (*currentState == ST_MAP_LOADED)) {
            *currentState = ST_MAP_VALIDATED;
            game.validatemap();
            flag = 1;
        } else if(input== "addplayer" && (*currentState == ST_MAP_VALIDATED || *currentState == ST_PLAYERS_ADDED)) {
            *currentState = ST_PLAYERS_ADDED;
            game.addplayer();
            flag = 1;
        } else if(input== "assigncountries" && (*currentState == ST_PLAYERS_ADDED)) {
            *currentState = ST_ASSIGN_REINFORCEMENT;
            game.assigncountries();
            flag = 1;
        } else if(input== "issueorder" && (*currentState == ST_ASSIGN_REINFORCEMENT || *currentState == ST_ISSUE_ORDERS)) {
            *currentState = ST_ISSUE_ORDERS;
            game.issueorder();
            flag = 1;
        } else if(input== "execorder" && (*currentState == ST_ISSUE_ORDERS || *currentState == ST_EXECUTE_ORDERS)) {
            *currentState = ST_EXECUTE_ORDERS;
            game.execorder();
            flag = 1;
        } else if(input== "endexecorders" && (*currentState == ST_EXECUTE_ORDERS)) {
            *currentState = ST_ASSIGN_REINFORCEMENT;
            game.endexecorders();
            flag = 1;
        } else if(input== "endissueorders" && (*currentState == ST_ISSUE_ORDERS)) {
            *currentState = ST_EXECUTE_ORDERS;
            game.endissueorders();
            flag = 1;
        } else if(input== "win" && (*currentState == ST_EXECUTE_ORDERS)) {
            *currentState = ST_WIN;
            game.win();
            flag = 1;
        } else if(input== "end" && (*currentState == ST_WIN)) {
            *currentState = ST_END;
            game.end();
            flag = 1;
        } else if(input== "play" && (*currentState == ST_WIN)) {
            *currentState = ST_START;
            game.play();
            flag = 1;
        } else {
            cout << "invalid choice!" << endl;
        }
    }
}