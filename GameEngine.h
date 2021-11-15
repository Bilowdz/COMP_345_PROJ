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

#include "Player.h"

//enum State
//{
//    ST_START,
//    ST_MAP_LOADED,
//    ST_MAP_VALIDATED,
//    ST_PLAYERS_ADDED,
//    ST_ASSIGN_REINFORCEMENT,
//    ST_ISSUE_ORDERS,
//    ST_EXECUTE_ORDERS,
//    ST_WIN,
//    ST_END,
//    ST_ERROR
//};

//enum Transition {
//    T_LOAD_MAP,
//    T_VALIDATE_MAP,
//    T_ADD_PLAYER,
//    T_ASSIGN_COUNTRIES,
//    T_ISSUE_ORDER,
//    T_END_ISSUE_ORDERS,
//    T_EXEC_ORDER,
//    T_END_EXEC_ORDERS,
//    T_WIN,
//    T_PLAY,
//    T_END,
//    T_ERROR
//};
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

        //added from ryan
        //TODO implement this shit
        void mainGameLoop(Map*, vector<Player*>);
        void reinforcementPhase(Player &, Map &);
        void issueOrdersPhase(Player &);
        void executeOrdersPhase();
        //end ryan

        //string getState();
        //bool transition(Transition);
        State getState();
        bool transition(Command *);

        GameEngine& operator =(const GameEngine &);
        friend ostream & operator << (ostream &, const GameEngine &ge);
};

#endif //COMP_345_PROJ_GAMEENGINE_H