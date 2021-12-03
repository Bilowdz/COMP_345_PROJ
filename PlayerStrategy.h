//
// Created by Ryan on 2021-11-26.
//

#ifndef GAMEENGINE_CPP_PLAYERSTRATEGY_H
#define GAMEENGINE_CPP_PLAYERSTRATEGY_H

#include "Player.h"

class PlayerStrategy {
    
Player *p;
public:
    virtual void issueOrder() = 0;
    virtual void toAttack() = 0;
    virtual void toDefend() = 0;
private:

};


#endif//GAMEENGINE_CPP_PLAYERSTRATEGY_H
