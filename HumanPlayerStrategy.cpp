//
// Created by Ryan on 2021-12-01.
//

#include "HumanPlayerStrategy.h"
void HumanPlayerStrategy::issueOrder() {
}
vector<Territory*> HumanPlayerStrategy::toAttack() {
    
    vector<Territory *> territoriesToAttack;
    //loop through player owned territories
    for (int i = 0; i < p->getTerritorySize(); i++) {
        //loop through the adjacent territories of the owned territories
        for (int j = 0; j < p->getTerritoriesOwned(i)->adjacentTerritories.size(); j++) {
            //check if that territory is already owned, if its now owned then add to list
            if (this->p->isOwnedTerritory(p->getTerritoriesOwned(i)->adjacentTerritories.at(j)->id) == nullptr &&
                !(p->isTerritoryInList(territoriesToAttack, p->getTerritoriesOwned(i)->adjacentTerritories.at(j)->id))) {
                territoriesToAttack.push_back(p->getTerritoriesOwned(i)->adjacentTerritories.at(j));
            }
        }
    }
    return territoriesToAttack;
}
vector<Territory*> HumanPlayerStrategy::toDefend() {
    vector<Territory *> territoriesToDefend;
    return territoriesToDefend;
}
