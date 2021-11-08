//
// Created by Nicolo pt 2 on 2021-11-07.
//

#ifndef CMAKELISTS_TXT_COMMANDPROCESSING_H
#define CMAKELISTS_TXT_COMMANDPROCESSING_H

#include <filesystem>
#include <vector>
#include <map>
#include "State.h"

using namespace std;

// holds data of commands
class Command {
private:
    string command;
    string effect;
public:
    Command();
    Command(string command);
    Command(string command, string effect);

    // saves effect of command
    void saveEffect(string effect);

    // gets effect of command
    string getEffect();
};

// controls how commands are processed
class CommandProcessor {
private:
    vector<Command*> commands;


    // reads command from console
    string readCommand();

    // validate command is valid in current state, returns effect
    string validate(string command, State currentState);

    // creates command object and saves to commands vector
    void saveCommand(string command,string effect ="");

public:
    // allows user to read/save command
    Command* getCommand(State currentState);
};

// parses line from file, executes command line by line
class FileCommandProcessorAdapter {

};

// reads line from file
class FileLineReader {

};

#endif //CMAKELISTS_TXT_COMMANDPROCESSING_H
