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
#include "LoggingObserver.h"

using namespace std;

// holds data of commands
class Command : public Subject, public ILoggable {
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

    // logging output
    std::string stringToLog() override;
};

// controls how commands are processed
class CommandProcessor : public Subject, public ILoggable {
private:
    Command* currentCommand;
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

    // logging output
    std::string stringToLog() override;
};

// loads file to memory, reads line by line
class FileLineReader {
private:
    bool debug = false;
    string path;
    vector<string> fileData;
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
    bool hasCommand();

    // assignment operator
    FileCommandProcessorAdapter& operator =(const FileCommandProcessorAdapter &);

    // stream insertion operator overload
    friend ostream & operator << (ostream &, const FileCommandProcessorAdapter &fcpa);
};

class FileCommandWriter {
public:
    string writeTournamentFile(vector<string>,vector<string>,int);
    vector<string> parseMap(string);
    vector<string> parsePlayer(string);
    int parseNumGames(string);
    int parseMaxDepth(string);

private:
    vector<string> parseList(string,regex);
    int parseInt(string, regex);
};

#endif //CMAKELISTS_TXT_COMMANDPROCESSING_H