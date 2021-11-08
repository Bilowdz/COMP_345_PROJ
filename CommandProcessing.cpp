//
// Created by Nicolo pt 2 on 2021-11-07.
//

#include "CommandProcessing.h"
#include <iostream>

using namespace std;

Command::Command(): command(""), effect(""){}

Command::Command(string command): command(command) {}

Command::Command(string command, string effect): command(command), effect(effect){}

void Command::saveEffect(string e) {
    effect = e;
}

string Command::getEffect() {
    return effect;
}

Command* CommandProcessor::getCommand(State currentState) {
    bool flag = false;

    // accept user input until valid user input selected
    while(!flag) {
        // read command from command line
        string userInput = readCommand(currentState);

        // validate command
        string response = validate(userInput, currentState);

        // check if response is valid
        if(response == "valid") {
            flag = true;

            saveCommand(userInput);
        // invalid response, save command effect
        } else {

            // response is the error received from validate function
            saveCommand(userInput,response);
        }
    }

    return commands.front();
}

string CommandProcessor::readCommand(State currentState) {

    string input;
    cout << "Please choose an option:";
    // get user input
    // todo: parses strings delimited by space, loadmap <mapfile> read as 2 commands instead of 1!
    // todo: should read line instead of delimiting by space, or handle this somehow...
    cin >> input;

    return input;
}

void CommandProcessor::saveCommand(string command, string effect) {
    Command *c;
    c = new Command(command,effect);
    commands.push_back(c);
}

string CommandProcessor::validate(string command, State currentState) {
    string loadmap = "loadmap";
    string addplayer = "addplayer";
    string response;
    if(command.rfind(loadmap,0) == 0) {

        // check if map file was provided by comparing length of command against addplayer command
        if(command.length() == loadmap.length()) {
            response = "Command '" + command + "' does not specify mapfile!";
            cout << response << endl;
            return response;

        } else if (!(currentState == ST_START || currentState == ST_MAP_LOADED)) {
            response = "Cannot perform transition '" + command + "' from state '" + enum_state_str[currentState] + "'!";
            cout << response << endl;
            return response;
        }
    } else if(command == "validatemap"){
        if((currentState != ST_MAP_LOADED)) {
            response = "Cannot perform transition '" + command + "' from state '" + enum_state_str[currentState] + "'!";
            cout << response << endl;
            return response;
        }
    } else if(command == addplayer) {

        // check if player name was provided by comparing length of command against addplayer command
        if(command.length() == addplayer.length()) {
            response = "Command '" + command + "' does not specify player name!";
            cout << response << endl;
            return response;

        } else if (!((currentState == ST_MAP_VALIDATED || currentState == ST_PLAYERS_ADDED))) {
            response = "Cannot perform transition '" + command + "' from state '" + enum_state_str[currentState] + "'!";
            cout << response << endl;
            return response;
        }
    } else if(command == "gamestart"){
        if((currentState != ST_PLAYERS_ADDED)) {
            response = "Cannot perform transition '" + command + "' from state '" + enum_state_str[currentState] + "'!";
            cout << response << endl;
            return response;
        }
    } else if(command == "quit"){
        if((currentState != ST_WIN)) {
            response = "Cannot perform transition '" + command + "' from state '" + enum_state_str[currentState] + "'!";
            cout << response << endl;
            return response;
        }
    } else if(command == "replay"){
        if((currentState != ST_WIN)) {
            response = "Cannot perform transition '" + command + "' from state '" + enum_state_str[currentState] + "'!";
            cout << response << endl;
            return response;
        }
    } else {
        response = "'" + command + "' is an invalid transition!";
        cout << response << endl;
        return  response;
    }
    return "valid";
}