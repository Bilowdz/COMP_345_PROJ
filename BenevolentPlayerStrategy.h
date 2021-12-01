//
// Created by Ryan on 2021-12-01.
//

#ifndef GAMEENGINE_CPP_BENEVOLENTPLAYERSTRATEGY_H
#define GAMEENGINE_CPP_BENEVOLENTPLAYERSTRATEGY_H

#include "PlayerStrategy.h"

class BenevolentPlayerStrategy : public PlayerStrategy {

public:
    void issueOrder() override;
    void toAttack() override;
    void toDefend() override;
};


#endif//GAMEENGINE_CPP_BENEVOLENTPLAYERSTRATEGY_H
