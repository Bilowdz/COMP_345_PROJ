//
// Created by Ryan on 2021-12-01.
//

#include "CheaterPlayerStrategy.h"

/**
 * Default constructor
 * @param player it is linked to
 */
CheaterPlayerStrategy::CheaterPlayerStrategy(Player *player) {
    this->p = player;
    p->setName("Cheater");
}

/**
 * Issue order inherited from PlayerStrategy
 *
 * @param vPlayersInPlay all the other players in the game
 */
void CheaterPlayerStrategy::issueOrder(vector<Player *> &vPlayersInPlay) {

    bool flag = true;

    //conquer all territories that are adjacent to its own territories
    for (int i = 0; i < this->toAttack().size(); i++) {

        //loop through other players
        for (int j = 0; j < vPlayersInPlay.size(); j++) {
            //check if another player owns the territory
            if (vPlayersInPlay.at(j)->isTerritoryInList(this->toAttack(), this->toAttack().at(i)->id)) {
                //if owned then remove from list
                vPlayersInPlay.at(j)->removeTerritory(this->toAttack().at(i));

                //add the territory to cheater list
                p->addTerritory(this->toAttack().at(i));
                flag = false;
                break;//end the loop
            }
        }
        if(flag) {
            //add the territory to cheater list
            p->addTerritory(this->toAttack().at(i));
        }
        flag = true;
    }
}

/**
 * Displays all adjacent territories to owned territories
 *
 * @return vector of all adjacent territories
 */
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

/**
 * Displays territories owned that are adjacent to other unowned territories
 *
 * @return vector of all adjacent territories
 */
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
