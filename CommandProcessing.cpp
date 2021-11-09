//
// Created by Nicolo pt 2 on 2021-11-07.
//

#include "CommandProcessing.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

Command::Command(): command(""), effect(""){}

Command::Command(string command): command(command) {}

Command::Command(string command, string effect): command(command), effect(effect){}

void Command::saveEffect(string e) {
    effect = e;
}

string Command::getEffect() const {
    return effect;
}

string Command::getCommand() const {
    return command;
}

// stream insertion operator overloads
ostream & operator << (ostream &out, const Command &c)
{
    out << "Command: " << c.getCommand() << " Effect: " << c.getEffect() << endl;
    return out;
}

CommandProcessor::CommandProcessor(GameEngine *ge): ge(ge) {}

Command* CommandProcessor::getCommand() {
    cout << "calling getCommand from CommandProcessor" << endl;

    // read command from command line
    string userInput = readCommand();

    // validate command
    string response = validate(userInput);

    // check if response is valid
    if(response == "valid") {
        saveCommand(userInput);
    // invalid response, save command effect
    } else {
        // response is the error received from validate function
        saveCommand(userInput,response);
    }

    return commands.back();
}

string CommandProcessor::readCommand() {

    string input;
    cout << "Please choose an option:";
    // get user input
    getline(cin,input);

    cout << input;
    return input;
}

Command* CommandProcessor::saveCommand(string command, string effect) {
    Command *c;
    c = new Command(command,effect);
    commands.push_back(c);
    return c;
}

string CommandProcessor::validate(string command) {
    string loadmap = "loadmap";
    string addplayer = "addplayer";
    string response;
    if(command.rfind(loadmap,0) == 0) {
        string delimiter = " ";

        // check if map file was provided by comparing length of command against addplayer command
        if(command.length() == loadmap.length()) {
            response = "Command '" + command + "' does not specify mapfile!";
            cout << response << endl;
            return response;

        } else if (!(ge.getState() == ST_START || ge.getState() == ST_MAP_LOADED)) {
            response = "Cannot perform transition '" + command + "' from state '" + enum_state_str[ge.getState()] + "'!";
            cout << response << endl;
            return response;
        } else {
            string token = command.substr(8,command.find(delimiter));
            if(token.length() == 0) {
                response = "Command '" + command + "' does not specify mapfile!";
                cout << response << endl;
                return response;
            }
        }
    } else if(command == "validatemap"){
        if((ge.getState() != ST_MAP_LOADED)) {
            response = "Cannot perform transition '" + command + "' from state '" + enum_state_str[ge.getState()] + "'!";
            cout << response << endl;
            return response;
        }
    } else if(command.rfind(addplayer,0) == 0) {
        string delimiter = " ";

        // check if player name was provided by comparing length of command against addplayer command
        if(command.length() == addplayer.length()) {
            response = "Command '" + command + "' does not specify player name!";
            cout << response << endl;
            return response;

        } else if (!((ge.getState() == ST_MAP_VALIDATED || ge.getState() == ST_PLAYERS_ADDED))) {
            response = "Cannot perform transition '" + command + "' from state '" + enum_state_str[ge.getState()] + "'!";
            cout << response << endl;
            return response;
        } else {
            string token = command.substr(10,command.find(delimiter));
            if(token.length() == 0) {
                response = "Command '" + command + "' does not specify player name!";
                cout << response << endl;
                return response;
            }
        }
    } else if(command == "gamestart"){
        if((ge.getState() != ST_PLAYERS_ADDED)) {
            response = "Cannot perform transition '" + command + "' from state '" + enum_state_str[ge.getState()] + "'!";
            cout << response << endl;
            return response;
        }
    } else if(command == "quit"){
        if((ge.getState() != ST_WIN)) {
            response = "Cannot perform transition '" + command + "' from state '" + enum_state_str[ge.getState()] + "'!";
            cout << response << endl;
            return response;
        }
    } else if(command == "replay"){
        if((ge.getState() != ST_WIN)) {
            response = "Cannot perform transition '" + command + "' from state '" + enum_state_str[ge.getState()] + "'!";
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

FileLineReader::FileLineReader(string path): path(path), pos(0), length(0) {
    this->load();
}
void FileLineReader::load() {
    string line;
    ifstream file(path);
    while(getline(file,line)) {
        fileData.push_back(line);
        length++;
    }
}

string FileLineReader::next() {
    return fileData[pos++];
}

bool FileLineReader::isEof() {
    return pos == (length - 1);
}

FileCommandProcessorAdapter::FileCommandProcessorAdapter(FileLineReader flr, GameEngine* ge): CommandProcessor(ge), flr(flr) {}

Command* FileCommandProcessorAdapter::getCommand() {
    Command* c;
    bool flag = false;
    while(!flag) {
        string input = readCommand();
        string response = validate(input);

        if(response == "valid") {
            flag = true;
            c = saveCommand(input);
        } else {
            c = saveCommand(input, response);
        }
        cout << *c << endl;
    }
    return c;
}

string FileCommandProcessorAdapter::readCommand() {
    return flr.next();
}
bool FileCommandProcessorAdapter::isEof() {
    return flr.isEof();
}