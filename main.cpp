#include <iostream>
#include "Map.h"
#include "Orders.h"
#include "Card.h"
#include "Player.h"
#include "CommandProcessing.h"
#include <memory>
using namespace std;

void runGameEngine(){
    /*
    GameEngine game;
    int flag = 0;

    // accept user input until valid user input selected
    while(flag == 0) {
        string input;
        string error;
        cout << "Please choose an option:";
        // get user input
        cin >> input;

        // check if valid input
        if(input=="loadmap") {
            if(game.transition("loadmap")) {
                flag = 1;
            } else {
                error = "cannot perform transition '" + input + "' from state '" + enum_state_str[game.getState()] + "'!";
            }
        } else if(input=="validatemap") {
            if(game.transition("validatemap")) {
                flag = 1;
            } else {
                error = "cannot perform transition '" + input + "' from state '" + enum_state_str[game.getState()] + "'!";
            }
        } else if(input=="addplayer") {
            if(game.transition("addplayer")) {
                flag = 1;
            } else {
                error = "cannot perform transition '" + input + "' from state '" + enum_state_str[game.getState()] + "'!";
            }
        } else if(input=="assigncountries") {
            if(game.transition("assigncountries")) {
                flag = 1;
            } else {
                error = "cannot perform transition '" + input + "' from state '" + enum_state_str[game.getState()] + "'!";
            }
        } else if(input=="issueorder") {
            if(game.transition("issueorder")) {
                flag = 1;
            } else {
                error = "cannot perform transition '" + input + "' from state '" + enum_state_str[game.getState()] + "'!";
            }
        } else if(input=="execorder") {
            if(game.transition("execorder")) {
                flag = 1;
            } else {
                error = "cannot perform transition '" + input + "' from state '" + enum_state_str[game.getState()] + "'!";
            }
        } else if(input=="endexecorders") {
            if(game.transition("endexecorders")) {
                flag = 1;
            } else {
                error = "cannot perform transition '" + input + "' from state '" + enum_state_str[game.getState()] + "'!";
            }
        } else if(input=="endissueorders") {
            if(game.transition("endissueorders")) {
                flag = 1;
            } else {
                error = "cannot perform transition '" + input + "' from state '" + enum_state_str[game.getState()] + "'!";
            }
        } else if(input=="win") {
            if(game.transition("win")) {
                flag = 1;
            } else {
                error = "cannot perform transition '" + input + "' from state '" + enum_state_str[game.getState()] + "'!";
            }
        } else if(input=="end") {
            if(game.transition("end")) {
                flag = 1;

            } else {
                error = "cannot perform transition '" + input + "' from state '" + enum_state_str[game.getState()] + "'!";
            }

        } else if(input=="play") {
            if(game.transition("play")) {
                flag = 1;
            } else {
                error = "cannot perform transition '" + input + "' from state '" + enum_state_str[game.getState()] + "'!";
            }
        } else {
            error = "'" + input + "' is an invalid transition!";
        }

        if (flag == 0){
            cout << error << endl;
            error = "";
        }
    }
     */
}

void driveMap() {
    auto* loader(new MapLoader());

    std::cout << *loader;

    std::cout << loader->maps.size() << std::endl;

    delete loader;
}

int main() {

    FileLineReader flr("../CommandProcessorFiles/commands.txt");
    //flr.load();
    //while(!flr.isEof()) {
    //    cout << flr.next() << endl;
    //}

    GameEngine* ge = new GameEngine();
    cout << &ge << endl;
    CommandProcessor cp;
    ge->startupPhase(cp, ge);
    //FileCommandProcessorAdapter adapter(flr, ge);

    return 0;
}
