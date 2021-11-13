//
// Created by Nicolo on 2021-09-24.
//
#include <iostream>
using namespace std;
#include <algorithm>
#include "Map.h"
#include "Player.h"
#include "Card.h"

#ifndef COMP_345_PROJ_GAMEENGINE_H
#define COMP_345_PROJ_GAMEENGINE_H
#include "State.h"
class Command;
class CommandProcessor;

class GameEngine {
    private:
        State currentState;
        Map gameMap;
        Deck *MainDeck;
        std::vector<Player*> Players;
        void loadmap(Command *);
        void validatemap();
        void addplayer(Command *);
        void gamestart();
        void assigncountries();
        void issueorder();
        void execorder();
        void endexecorders();
        void endissueorders();
        void win();
        void end();
        void play();

    public:
        bool isGameDone;
        GameEngine();
        GameEngine(const GameEngine &);
        GameEngine(GameEngine *);
        ~GameEngine();
        void startupPhase(CommandProcessor cp, GameEngine *);

        State getState();
        bool transition(Command *);

        GameEngine& operator =(const GameEngine &);
        friend ostream & operator << (ostream &, const GameEngine &ge);
};

#endif //COMP_345_PROJ_GAMEENGINE_H