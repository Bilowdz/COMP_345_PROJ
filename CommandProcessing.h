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
    bool debug = false;
    string command;
    string effect;
public:
    // constructors
    Command();
    Command(string command);
    Command(string command, string effect);

    // copy constructors
    Command(Command *);
    Command(const Command &);

    // destructor
    ~Command();

    // setter for effect
    void saveEffect(string effect);

    // getter for command
    string getCommand() const;

    // getter for effect
    string getEffect() const;

    // assignment operator
    Command& operator =(const Command &);

    // stream insertion operator overload
    friend ostream & operator << (ostream &, const Command &c);
};

// controls how commands are processed
class CommandProcessor {
private:
    bool debug = false;
    vector<Command*> commands;
protected:
    // reads command from console
    virtual string readCommand();

    // creates command object and saves to commands vector
    Command* saveCommand(string command, string effect ="");

    // validate command is valid in current state, returns effect
    string validate(string command, GameEngine *);

public:
    // constructors
    CommandProcessor();

    // copy constructors
    CommandProcessor(CommandProcessor *);
    CommandProcessor(const CommandProcessor &);

    // destructor
    virtual ~CommandProcessor();

    // allows user to read/save command
    virtual Command* getCommand(GameEngine *);

    // assignment operator
    CommandProcessor& operator =(const CommandProcessor &);

    // stream insertion operator overload
    friend ostream & operator << (ostream &, const CommandProcessor &cp);
};

// loads file to memory, reads line by line
class FileLineReader {
private:
    bool debug = false;
    string path;
    vector<string> fileData;
    int length;
    int pos;
public:
    // constructor
    FileLineReader(string path);

    // copy constructors
    FileLineReader(FileLineReader *);
    FileLineReader(const FileLineReader &);

    // destructor
    ~FileLineReader();

    void load();
    string next();
    bool isEof();


    // assignment operator
    FileLineReader& operator =(const FileLineReader &);

    // stream insertion operator overload
    friend ostream & operator << (ostream &, const FileLineReader &fr);
};

// parses line from file, executes command line by line
class FileCommandProcessorAdapter: public CommandProcessor {
private:
    bool debug = false;
    FileLineReader flr;

    bool isEof();
public:
    FileCommandProcessorAdapter(FileLineReader);

    // copy constructors
    FileCommandProcessorAdapter(FileCommandProcessorAdapter *);
    FileCommandProcessorAdapter(const FileCommandProcessorAdapter &);


    string readCommand();
    Command* getCommand(GameEngine *);

    // assignment operator
    FileCommandProcessorAdapter& operator =(const FileCommandProcessorAdapter &);

    // stream insertion operator overload
    friend ostream & operator << (ostream &, const FileCommandProcessorAdapter &fcpa);
};

#endif //CMAKELISTS_TXT_COMMANDPROCESSING_H