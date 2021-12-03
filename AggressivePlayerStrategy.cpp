//
// Created by Ryan on 2021-12-01.
//

#include "AggressivePlayerStrategy.h"

/**
 * Default constructor
 * @param player link
 */
AggressivePlayerStrategy::AggressivePlayerStrategy(Player * player) {
    this->p = player;
}

/**
 * Issue order inherited from PlayerStrategy
 *
 * @param vPlayersInPlay all the other players in the game
 */
void AggressivePlayerStrategy::issueOrder(vector<Player *> &vPlayersInPlay) {
    for (int i = 0; i < toDefend().size(); i++) {
        if (toDefend().at(i)->IsAdjacent(*toAttack().at(0))) {
            i = toDefend().size();
            auto * deploy = new Deploy(p->getReinforcements(), *toDefend().at(i));
            p->getOrdersList()->addDeploy(deploy);
            int advancingarmies = p->getReinforcements() + toDefend().at(i)->unitsGarrisoned;
            auto * advance = new Advance(advancingarmies,*toDefend().at(i) , *toAttack().at(0));
            p->getOrdersList()->addAdvance(advance);
        }
    }
}

/**
 * Displays all adjacent territories to owned territories
 *
 * @return vector of all adjacent territories
 */
vector<Territory*> AggressivePlayerStrategy::toAttack() {
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
vector<Territory*> AggressivePlayerStrategy::toDefend() {
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
