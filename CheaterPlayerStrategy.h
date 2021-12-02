//
// Created by Ryan on 2021-12-01.
//

#ifndef GAMEENGINE_CPP_CHEATERPLAYERSTRATEGY_H
#define GAMEENGINE_CPP_CHEATERPLAYERSTRATEGY_H

#include "PlayerStrategy.h"
#include "Player.h"

class CheaterPlayerStrategy : public PlayerStrategy {

public:
    explicit CheaterPlayerStrategy(Player*);
    void issueOrder(vector<Player *> &vPlayersInPlay) override;
    vector<Territory*> toAttack() override;
    vector<Territory*> toDefend() override;
};


#endif//GAMEENGINE_CPP_CHEATERPLAYERSTRATEGY_H
