#include <iostream>
#include "Map.h"
#include "Orders.h"
#include "Card.h"
#include "Player.h"
#include "CommandProcessing.h"
#include <memory>
using namespace std;

void driveMap() {
    auto* loader(new MapLoader());

    std::cout << *loader;

    std::cout << loader->maps.size() << std::endl;

    delete loader;
}

void chooseComandProcessor() {
    cout << "Choose between accepting the commands from the console (1) or from a file (2): " << endl;
    int input = 0;
    cin >> input;

    // user selected console
    if(input == 1) {
        cout << "hello world" << endl;
    } else {
        cout << "goodbye world" << endl;
        string filename;

        cout << "Please enter a filename (commands.txt is the only available file):" << endl;
        cin >> filename;
        cout << "Your filename is: " << filename << endl;
        // user selected from file
    }
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
