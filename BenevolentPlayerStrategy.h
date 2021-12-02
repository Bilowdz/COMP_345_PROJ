//
// Created by Ryan on 2021-12-01.
//

#ifndef GAMEENGINE_CPP_BENEVOLENTPLAYERSTRATEGY_H
#define GAMEENGINE_CPP_BENEVOLENTPLAYERSTRATEGY_H

#include "PlayerStrategy.h"

class BenevolentPlayerStrategy : public PlayerStrategy {

public:
    void issueOrder(vector<Player *> &vPlayersInPlay) override;
    vector<Territory*> toAttack() override;
    vector<Territory*> toDefend() override;
};


#endif//GAMEENGINE_CPP_BENEVOLENTPLAYERSTRATEGY_H
