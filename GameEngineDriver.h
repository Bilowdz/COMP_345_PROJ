//
// Created by Nicolo pt 2 on 2021-09-24.
//

#ifndef COMP_345_PROJ_GAMEENGINEDRIVER_H
#define COMP_345_PROJ_GAMEENGINEDRIVER_H
#include "GameEngine.h"


class GameEngineDriver {
public:
    GameEngine* game;
    bool isGameDone;
    GameEngineDriver();
    GameEngineDriver(const GameEngineDriver &);
    ~GameEngineDriver();

    void chooseCommand();
    GameEngineDriver& operator =(const GameEngineDriver &);

    friend std::ostream & operator << (std::ostream &, const GameEngineDriver &);
    //friend std::istream & operator << (std::istream &, const GameEngineDriver &);
};



#endif //COMP_345_PROJ_GAMEENGINEDRIVER_H