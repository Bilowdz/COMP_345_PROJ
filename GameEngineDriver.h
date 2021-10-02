//
// Created by Nicolo pt 2 on 2021-09-24.
//

#ifndef COMP_345_PROJ_GAMEENGINEDRIVER_H
#define COMP_345_PROJ_GAMEENGINEDRIVER_H
#include "GameEngine.h"


class GameEngineDriver {
public:
    GameEngineDriver();
    void start();
    void chooseCommand(State* s, GameEngine g);
};



#endif //COMP_345_PROJ_GAMEENGINEDRIVER_H
