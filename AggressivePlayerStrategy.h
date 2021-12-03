//
// Created by Ryan on 2021-12-01.
//

#ifndef GAMEENGINE_CPP_AGGRESSIVEPLAYERSTRATEGY_H
#define GAMEENGINE_CPP_AGGRESSIVEPLAYERSTRATEGY_H

#include "PlayerStrategy.h"
#include "Player.h"

class AggressivePlayerStrategy : public PlayerStrategy {

public:
    AggressivePlayerStrategy(Player * player);
    void issueOrder(vector<Player *> &vPlayersInPlay) override;
    vector<Territory*> toAttack() override;
    vector<Territory*> toDefend() override;
};


#endif//GAMEENGINE_CPP_AGGRESSIVEPLAYERSTRATEGY_H
