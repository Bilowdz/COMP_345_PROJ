//
// Created by Ryan on 2021-12-01.
//

#include "NeutralPlayerStrategy.h"

int NeutralPlayerStrategy::neutralReturn() {
    return 1;
}

NeutralPlayerStrategy::NeutralPlayerStrategy(Player *player) {
    this->p = player;
}

void NeutralPlayerStrategy::issueOrder(vector<Player *> &vPlayersInPlay) {
    std::cout << "NeutralPlayerStrategy issueOrder. Does not do anything, as player is neutral." << endl;
}

vector<Territory*> NeutralPlayerStrategy::toAttack() {
    vector<Territory *> territoriesToAttack;
    //loop through player owned territories
    for (int i = 0; i < p->getTerritorySize(); i++) {
        //loop through the adjacent territories of the owned territories
        for (int j = 0; j < p->getVTerritory().at(i)->adjacentTerritories.size(); j++) {
            //check if that territory is already owned, if its now owned then add to list
            if (this->p->isOwnedTerritory(p->getVTerritory().at(i)->adjacentTerritories.at(j)->id) == nullptr &&
                !(p->isTerritoryInList(territoriesToAttack, p->getVTerritory().at(i)->adjacentTerritories.at(j)->id))) {
                territoriesToAttack.push_back(p->getVTerritory().at(i)->adjacentTerritories.at(j));
            }
        }
    }
    return territoriesToAttack;
}

vector<Territory*> NeutralPlayerStrategy::toDefend() {
    vector<Territory *> territoriesToDefend;
    //loop through player owned territories
    for (int i = 0; i < p->getTerritorySize(); i++) {
        //loop through the adjacent territories of the owned territories
        for (int j = 0; j < p->getVTerritory().at(i)->adjacentTerritories.size(); j++) {
            //check if that territory is already owned, if the adjacent territory is not owned
            if (this->p->isOwnedTerritory(p->getVTerritory().at(i)->adjacentTerritories.at(j)->id) == nullptr &&
                !(p->isTerritoryInList(territoriesToDefend, p->getVTerritory().at(i)->id))) {
                territoriesToDefend.push_back(
                        p->getVTerritory().at(i));//push the territory we own into list of territories to defend
            }
        }
    }
    return territoriesToDefend;
}
