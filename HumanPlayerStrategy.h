//
// Created by Ryan on 2021-12-01.
//

#ifndef GAMEENGINE_CPP_HUMANPLAYERSTRATEGY_H
#define GAMEENGINE_CPP_HUMANPLAYERSTRATEGY_H

#include "PlayerStrategy.h"
#include "Player.h"

class HumanPlayerStrategy : public PlayerStrategy {

public:
    HumanPlayerStrategy(Player*);
    void issueOrder(vector<Player *>&) override;
    vector<Territory*> toAttack() override;
    vector<Territory*> toDefend() override;
};


#endif//GAMEENGINE_CPP_HUMANPLAYERSTRATEGY_H
