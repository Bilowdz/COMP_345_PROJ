//
// Created by Nicolo pt 2 on 2021-11-07.
//

#ifndef CMAKELISTS_TXT_COMMANDPROCESSING_H
#define CMAKELISTS_TXT_COMMANDPROCESSING_H

#include <filesystem>
#include <vector>
#include <map>
#include "State.h"
#include "GameEngine.h"

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

    // setter for effect
    void saveEffect(string effect);

    // getter for command
    string getCommand() const;

    // getter for effect
    string getEffect() const;

    friend ostream & operator << (ostream &, const Command &c);
};

// controls how commands are processed
class CommandProcessor {
private:
    vector<Command*> commands;
    GameEngine ge;

protected:
    // reads command from console
    virtual string readCommand();

    // creates command object and saves to commands vector
    Command* saveCommand(string command, string effect ="");

    // validate command is valid in current state, returns effect
    string validate(string command);

public:
    CommandProcessor(GameEngine *);
    // allows user to read/save command
    virtual Command* getCommand();
};

// loads file to memory, reads line by line
class FileLineReader {
private:
    string path;
    vector<string> fileData;
    int length;
    int pos;
public:
    FileLineReader(string path);
    void load();
    string next();
    bool isEof();
};

// parses line from file, executes command line by line
class FileCommandProcessorAdapter: public CommandProcessor {
private:
    FileLineReader flr;
public:
    FileCommandProcessorAdapter(FileLineReader, GameEngine *);
    string readCommand();
    Command* getCommand();
    bool isEof();
};

#endif //CMAKELISTS_TXT_COMMANDPROCESSING_H
/*
// accept user input until valid user input selected
while(!flag) {
// read command from command line
string userInput = readCommand();

// validate command
string response = validate(userInput);

// check if response is valid
if(response == "valid") {
flag = true;

saveCommand(userInput);
// invalid response, save command effect
} else {

// response is the error received from validate function
saveCommand(userInput,response);
}
 */