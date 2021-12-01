//
// Created by Nicolo pt 2 on 2021-11-07.
//

#include "CommandProcessing.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

/**
 * --- --- --- Command ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
 **/

// constructors
Command::Command(): command(""), effect(""){
    if(this->debug)
        cout << "CommandProcessor constructor called (no params)" << endl;
}

Command::Command(string command): command(command) {
    if(this->debug)
        cout << "CommandProcessor constructor called (1 param)" << endl;
}

Command::Command(string command, string effect): command(command), effect(effect) {
    if(this->debug)
        cout << "CommandProcessor constructor called (2 params)" << endl;
}

// copy constructors
Command::Command(Command *const pc): command(pc->command), effect(pc->effect) {
    if(this->debug)
        cout << "Command copy constructor called (pointer)" << endl;
}

Command::Command(const Command &c): command(c.command), effect(c.effect) {
    if(this->debug)
        cout << "Command copy constructor called (object)" << endl;
}

// destructor
Command:: ~Command() = default;

//Saves the current effect
void Command::saveEffect(string e) {
    effect = e;
    Notify(this);
}

//Returns the current effect
string Command::getEffect() const {
    return effect;
}

//Gets the command
string Command::getCommand() const {
    return command;
}

// assignment operator overload
Command& Command::operator =(const Command &c) {
    this->command = c.command;
    this->effect = c.effect;

    return *this;
}

// stream insertion operator overloads
ostream & operator << (ostream &out, const Command &c)
{
    out << "Command: " << c.getCommand() << " Effect: " << c.getEffect() << endl;
    return out;
}

// Logging function for the Command
string Command::stringToLog() {
    string log = "Log :: Effect: " + getEffect();
    return log;
}

/**
 * --- --- --- CommandProcessor ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
 **/
// constructors
CommandProcessor::CommandProcessor() {
    if(this->debug)
        cout << "CommandProcessor constructor called" << endl;
}

// copy constructors
CommandProcessor::CommandProcessor(CommandProcessor *const cp): commands(cp->commands) {
    if(this->debug)
        cout << "CommandProcessor copy constructor called (pointer)" << endl;
}

CommandProcessor::CommandProcessor(const CommandProcessor & c): commands(c.commands) {
    if(this->debug)
        cout << "CommandProcessor copy constructor called (object)" << endl;
}

// destructor
CommandProcessor:: ~CommandProcessor() = default;

/**
 * Gets the command
 * @param ge game engine gets passed in
 * @return a command pointer
 */
Command* CommandProcessor::getCommand(GameEngine * ge) {
    ge->printAvailableOptions();
    if(this->debug)
        cout << "calling getCommand from CommandProcessor" << endl;

    // read command from command line
    string userInput = readCommand();

    // validate command
    string response = validate(userInput, ge);

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

//Reads the command and calls the getline function
string CommandProcessor::readCommand() {

    string input;
    cout << "Please choose an option:";
    // get user input
    getline(cin,input);

    cout << input;
    return input;
}

//saves the command and pushes to the commands vector
Command* CommandProcessor::saveCommand(string command, string effect) {
    Command *c;
    c = new Command(command);
    currentCommand = c;
    commands.push_back(c);

    Notify(this);

    for(Observer* observer : *_observers)
        c->Attach(observer);
    c->saveEffect(effect);

    return c;
}

//validates the command based on the input andgame engine
string CommandProcessor::validate(string command, GameEngine *ge) {
    string loadmap = "loadmap";
    string addplayer = "addplayer";
    string response;
    if(command.rfind(loadmap,0) == 0) {
        string delimiter = " ";

        // check if map file was provided by comparing length of command against addplayer command
        if(command.length() == loadmap.length()) {
            response = "Command '" + command + "' does not specify mapfile!";
            if(this->debug)
                cout << response << endl;
            return response;

        } else if (!(ge->getState() == ST_START || ge->getState() == ST_MAP_LOADED)) {
            response = "Cannot perform transition '" + command + "' from state '" + enum_state_str[ge->getState()] + "'!";
            if(this->debug)
                cout << response << endl;
            return response;
        } else {
            string token = command.substr(8,command.find(delimiter));
            if(token.length() == 0) {
                response = "Command '" + command + "' does not specify mapfile!";
                if(this->debug)
                    cout << response << endl;
                return response;
            }
        }
    } else if(command == "validatemap"){
        if((ge->getState() != ST_MAP_LOADED)) {
            response = "Cannot perform transition '" + command + "' from state '" + enum_state_str[ge->getState()] + "'!";
            if(this->debug)
                cout << response << endl;
            return response;
        }
    } else if(command.rfind(addplayer,0) == 0) {
        string delimiter = " ";

        // check if player name was provided by comparing length of command against addplayer command
        if(command.length() == addplayer.length()) {
            response = "Command '" + command + "' does not specify player name!";
            if(this->debug)
                cout << response << endl;
            return response;

        } else if (!((ge->getState() == ST_MAP_VALIDATED || ge->getState() == ST_PLAYERS_ADDED))) {
            response = "Cannot perform transition '" + command + "' from state '" + enum_state_str[ge->getState()] + "'!";
            if(this->debug)
                cout << response << endl;
            return response;
        } else {
            string token = command.substr(10,command.find(delimiter));
            if(token.length() == 0) {
                response = "Command '" + command + "' does not specify player name!";
                if(this->debug)
                    cout << response << endl;
                return response;
            }
        }
    } else if(command == "gamestart"){
        if((ge->getState() != ST_PLAYERS_ADDED)) {
            response = "Cannot perform transition '" + command + "' from state '" + enum_state_str[ge->getState()] + "'!";
            if(this->debug)
                cout << response << endl;
            return response;
        }
    } else if(command == "quit"){
        if((ge->getState() != ST_WIN)) {
            response = "Cannot perform transition '" + command + "' from state '" + enum_state_str[ge->getState()] + "'!";
            if(this->debug)
                cout << response << endl;
            return response;
        }
    } else if(command == "replay"){
        if((ge->getState() != ST_WIN)) {
            response = "Cannot perform transition '" + command + "' from state '" + enum_state_str[ge->getState()] + "'!";
            if(this->debug)
                cout << response << endl;
            return response;
        }
    } else {
        response = "'" + command + "' is an invalid transition!";
        if(this->debug)
            cout << response << endl;
        return  response;
    }
    return "valid";
}

// assignment operator overload
CommandProcessor& CommandProcessor::operator =(const CommandProcessor &cp) {
    this->commands = cp.commands;

    return *this;
}

// stream insertion operator overloads
ostream & operator << (ostream &out, const CommandProcessor &cp)
{
    out << "CommandProcessor: " << endl;
    for(Command *c : cp.commands){
        out << "Command: " << *c << " " << endl;
    }

    return out;
}

// Logging function for the CommandProcessor
string CommandProcessor::stringToLog() {
    string log = "Log :: Command: " + currentCommand->getCommand();
    return log;
}

/**
 * --- --- --- FileLineReader ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
 **/
// constructor
FileLineReader::FileLineReader(string path): path(path), pos(0), length(0) {
    this->load();
}

// copy constructors
FileLineReader::FileLineReader(FileLineReader *const fr): path(fr->path), pos(fr->pos), length(fr->length) {
    this->load();
    if(this->debug)
        cout << "FileLineReader copy constructor called (pointer)" << endl;
}

FileLineReader::FileLineReader(const FileLineReader & fr): path(fr.path), pos(fr.pos), length(fr.length) {
    this->load();
    if(this->debug)
        cout << "FileLineReader copy constructor called (object)" << endl;
}

//Default constructor
FileLineReader:: ~FileLineReader() = default;

//Loads the line that was passed in
void FileLineReader::load() {
    string line;
    ifstream file(path);
    while(getline(file,line)) {
        fileData.push_back(line);
        length++;
    }
}

//Gets the next position in the filelinereader
string FileLineReader::next() {
    return fileData[pos++];
}

//checks if at the end of file
bool FileLineReader::isEof() {
    return pos == (length - 1);
}

// assignment operator overload
FileLineReader& FileLineReader::operator =(const FileLineReader &fr) {
    this->path = fr.path;
    this->length = fr.length;
    this->pos = fr.pos;

    return *this;
}

// stream insertion operator overloads
ostream & operator << (ostream &out, const FileLineReader &fr)
{
    out << "FileLineReader: " << endl;
    out << "Path:" << fr.path << ", Length: " << fr.length << ", Position: " << fr.pos << " " << endl;

    return out;
}

/**
 * --- --- --- FileCommandProcessorAdapter ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
 **/
 // constructors
FileCommandProcessorAdapter::FileCommandProcessorAdapter(FileLineReader flr): CommandProcessor(), flr(flr) {}

// copy constructors
FileCommandProcessorAdapter::FileCommandProcessorAdapter(FileCommandProcessorAdapter *const fcpa): CommandProcessor(fcpa), flr(fcpa->flr) {
    if(this->debug)
        cout << "FileCommandProcessorAdapter copy constructor called (pointer)" << endl;
}

// FileCommandProcessorAdapter is a child of base class CommandProcessor, so instance of fcpa can be passed to CommandProcessor() via its copy constructor
FileCommandProcessorAdapter::FileCommandProcessorAdapter(const FileCommandProcessorAdapter &fcpa): CommandProcessor(fcpa), flr(fcpa.flr) {
    if(this->debug)
        cout << "FileCommandProcessorAdapter copy constructor called (object)" << endl;
}

//gets the command based on the game engine
Command* FileCommandProcessorAdapter::getCommand(GameEngine * ge) {
    Command* c;
    string input = readCommand();
    string response = validate(input, ge);

    if(response == "valid") {
        c = saveCommand(input);
    } else {
        c = saveCommand(input, response);
    }
    if(this->debug)
        cout << *c << endl;
    return c;
}

//reads the current command
string FileCommandProcessorAdapter::readCommand() {

    // check if end of file reached
    if(isEof()) {
        return "Error: end of file reached!";
    } else {
        return flr.next();
    }
}
//Checks if we are at end of file
bool FileCommandProcessorAdapter::isEof() {
    return flr.isEof();
}

// assignment operator overload
FileCommandProcessorAdapter& FileCommandProcessorAdapter::operator =(const FileCommandProcessorAdapter &fcpa) {
    this->flr = fcpa.flr;

    return *this;
}

// stream insertion operator overloads
ostream & operator << (ostream &out, const FileCommandProcessorAdapter &fcpa)
{
    out << "FileCommandProcessorAdapter: " << endl;
    //out << fcpa.flr << endl;

    return out;
}

bool FileCommandProcessorAdapter::hasCommand() {
    return !flr.isEof();
}

// based on given tournament parameters, create a commands file which the file command processor can read from
string FileCommandWriter::writeTournamentFile(vector<string> maps, vector<string> players, int numGames) {
    string gameFile = "../CommandProcessorFiles/commands_tournament.txt";
    ofstream output;
    output.open(gameFile,ios_base::trunc);

    // loop over each map
    for(int i = 0; i < maps.size(); i++) {

        // loop over each game
        for(int j = 0; j < numGames; j++) {
            output << "loadmap " + maps[i] << endl;
            output << "validatemap" << endl;

            // loop over each player
            for(int k = 0; k < players.size(); k++) {
                output << "addplayer " + players[k] << endl;
            }
            output << "gamestart" << endl;

            // check if last iteration
            if(i == (maps.size() - 1) && j == (numGames - 1)) {
                output << "quit";
            } else {
                output << "replay" << endl;
            }
        }
    }
    output.close();

    return gameFile;
}
