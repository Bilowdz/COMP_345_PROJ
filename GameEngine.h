//
// Created by Nicolo pt 2 on 2021-09-24.
//

#ifndef COMP_345_PROJ_GAMEENGINE_H
#define COMP_345_PROJ_GAMEENGINE_H

enum State
{
    ST_START,
    ST_MAP_LOADED,
    ST_MAP_VALIDATED,
    ST_PLAYERS_ADDED,
    ST_ASSIGN_REINFORCEMENT,
    ST_ISSUE_ORDERS,
    ST_EXECUTE_ORDERS,
    ST_WIN,
    ST_END,
    ST_DEFAULT
};

class GameEngine {
    public:
        State currentState;
        GameEngine();
        GameEngine(State);
        void loadmap();
        void validatemap();
        void addplayer();
        void assigncountries();
        void issueorder();
        void execorder();
        void endexecorders();
        void endissueorders();
        void win();
        void end();
        void play();

};


#endif //COMP_345_PROJ_GAMEENGINE_H
