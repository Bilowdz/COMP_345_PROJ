//
// Created by Ryan on 2021-12-01.
//

#ifndef GAMEENGINE_CPP_CHEATERPLAYERSTRATEGY_H
#define GAMEENGINE_CPP_CHEATERPLAYERSTRATEGY_H

#include "PlayerStrategy.h"

class CheaterPlayerStrategy : public PlayerStrategy {

public:
    void issueOrder() override;
    void toAttack() override;
    void toDefend() override;
};


#endif//GAMEENGINE_CPP_CHEATERPLAYERSTRATEGY_H