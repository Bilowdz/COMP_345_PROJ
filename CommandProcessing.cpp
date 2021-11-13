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
    cout << "CommandProcessor constructor called (no params)" << endl;
}

Command::Command(string command): command(command) {
    cout << "CommandProcessor constructor called (1 param)" << endl;
}

Command::Command(string command, string effect): command(command), effect(effect) {
    cout << "CommandProcessor constructor called (2 params)" << endl;
}

// copy constructors
Command::Command(Command *const pc): command(pc->command), effect(pc->effect) {
    cout << "Command copy constructor called (pointer)" << endl;
}

Command::Command(const Command &c): command(c.command), effect(c.effect) {
    cout << "Command copy constructor called (object)" << endl;
}

// destructor
Command:: ~Command() = default;


void Command::saveEffect(string e) {
    effect = e;
}

string Command::getEffect() const {
    return effect;
}

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

/**
 * --- --- --- CommandProcessor ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
 **/
// constructors
CommandProcessor::CommandProcessor() {
    cout << "CommandProcessor constructor called" << endl;
}

// copy constructors
CommandProcessor::CommandProcessor(CommandProcessor *const cp): commands(cp->commands) {
    cout << "CommandProcessor copy constructor called (pointer)" << endl;
}

CommandProcessor::CommandProcessor(const CommandProcessor & c): commands(c.commands) {
    cout << "CommandProcessor copy constructor called (object)" << endl;
}

// destructor
CommandProcessor:: ~CommandProcessor() = default;

Command* CommandProcessor::getCommand(GameEngine * ge) {
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

string CommandProcessor::validate(string command, GameEngine *ge) {
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

        } else if (!(ge->getState() == ST_START || ge->getState() == ST_MAP_LOADED)) {
            response = "Cannot perform transition '" + command + "' from state '" + enum_state_str[ge->getState()] + "'!";
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
        if((ge->getState() != ST_MAP_LOADED)) {
            response = "Cannot perform transition '" + command + "' from state '" + enum_state_str[ge->getState()] + "'!";
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

        } else if (!((ge->getState() == ST_MAP_VALIDATED || ge->getState() == ST_PLAYERS_ADDED))) {
            response = "Cannot perform transition '" + command + "' from state '" + enum_state_str[ge->getState()] + "'!";
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
        if((ge->getState() != ST_PLAYERS_ADDED)) {
            response = "Cannot perform transition '" + command + "' from state '" + enum_state_str[ge->getState()] + "'!";
            cout << response << endl;
            return response;
        }
    } else if(command == "quit"){
        if((ge->getState() != ST_WIN)) {
            response = "Cannot perform transition '" + command + "' from state '" + enum_state_str[ge->getState()] + "'!";
            cout << response << endl;
            return response;
        }
    } else if(command == "replay"){
        if((ge->getState() != ST_WIN)) {
            response = "Cannot perform transition '" + command + "' from state '" + enum_state_str[ge->getState()] + "'!";
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
    cout << "FileLineReader copy constructor called (pointer)" << endl;
}

FileLineReader::FileLineReader(const FileLineReader & fr): path(fr.path), pos(fr.pos), length(fr.length) {
    this->load();
    cout << "FileLineReader copy constructor called (object)" << endl;
}

FileLineReader:: ~FileLineReader() = default;

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
    cout << "FileCommandProcessorAdapter copy constructor called (pointer)" << endl;
}

// FileCommandProcessorAdapter is a child of base class CommandProcessor, so instance of fcpa can be passed to CommandProcessor() via its copy constructor
FileCommandProcessorAdapter::FileCommandProcessorAdapter(const FileCommandProcessorAdapter &fcpa): CommandProcessor(fcpa), flr(fcpa.flr) {
    cout << "FileCommandProcessorAdapter copy constructor called (object)" << endl;
}

Command* FileCommandProcessorAdapter::getCommand(GameEngine * ge) {
    Command* c;
    string input = readCommand();
    string response = validate(input, ge);

    if(response == "valid") {
        c = saveCommand(input);
    } else {
        c = saveCommand(input, response);
    }
    cout << *c << endl;
    return c;
}

string FileCommandProcessorAdapter::readCommand() {

    // check if end of file reached
    if(isEof()) {
        return "Error: end of file reached!";
    } else {
        return flr.next();
    }
}
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