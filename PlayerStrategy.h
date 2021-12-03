//
// Created by Ryan on 2021-11-26.
//

#ifndef GAMEENGINE_CPP_PLAYERSTRATEGY_H
#define GAMEENGINE_CPP_PLAYERSTRATEGY_H

#include <vector>
using namespace std;

class Player;
class Territory;

class PlayerStrategy {

public:
    virtual int neutralReturn();
    Player *p;
    virtual void issueOrder(vector<Player *> &) = 0;
    virtual vector<Territory*> toAttack() = 0;
    virtual vector<Territory*> toDefend() = 0;
private:

};


#endif//GAMEENGINE_CPP_PLAYERSTRATEGY_H
