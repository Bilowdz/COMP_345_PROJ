//
// Created by Ryan on 2021-12-01.
//

#include "CheaterPlayerStrategy.h"

CheaterPlayerStrategy::CheaterPlayerStrategy(Player *player) {
    this->p = player;
}

void CheaterPlayerStrategy::issueOrder(vector<Player *> &vPlayersInPlay) {

    //conquer all territories that are adjacent to its own territories
    for (int i = 0; i < this->toAttack().size(); i++) {

        //loop through other players
        for (int j = 0; j < vPlayersInPlay.size(); j++) {
            //check if another player owns the territory
            if (vPlayersInPlay.at(j)->isTerritoryInList(this->toAttack(), this->toAttack().at(i)->id)){
                //if owned then remove from list
                vPlayersInPlay.at(j)->removeTerritory(this->toAttack().at(i));

                //add the territory to cheater list
                p->addTerritory(this->toAttack().at(i));
                break; //end the loop
            }
        }
        //add the territory to cheater list
        p->addTerritory(this->toAttack().at(i));
    }
}

    vector<Territory *> CheaterPlayerStrategy::toAttack() {
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
    vector<Territory *> CheaterPlayerStrategy::toDefend() {
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
