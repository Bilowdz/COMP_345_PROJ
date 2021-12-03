//
// Created by Ryan on 2021-12-01.
//

#include "BenevolentPlayerStrategy.h"

/**
 * Default constructor
 * @param player link
 */
BenevolentPlayerStrategy::BenevolentPlayerStrategy(Player* player) {
    this->p = player;
    p->setName("Benevolent");
}

/**
 * Issue order inherited from PlayerStrategy
 *
 * @param vPlayersInPlay all the other players in the game
 */
void BenevolentPlayerStrategy::issueOrder(vector<Player *> &vPlayersInPlay) {
    int numArmiesDeployed = 0;
    int toDeploy;
    int weakest;
    int weakestUnits;
    int currentUnits;
    int difference;

    vector<Territory *> ownedTerritories = p->getVTerritory();
    vector<int> territoryUnits;
    for(int i = 0; i < ownedTerritories.size(); i++)
        territoryUnits.push_back(ownedTerritories.at(i)->unitsGarrisoned);

    // Reinforce whenever possible
    if (p->getHand()->isCardOwned("Reinforcement")) {
        int reinforcementCardReward = 5;
        this->p->setReinforcements(this->p->getReinforcements() + reinforcementCardReward);
        p->getHand()->removeCard(p->getHand()->getCardIndex("Reinforcement"));
    }

    // Use reinforcement pool
    while (p->getReinforcements() != numArmiesDeployed){
        weakest = -1;
        for(int i = 0; i < ownedTerritories.size(); i++){
            Territory * cur = ownedTerritories.at(i);
            currentUnits = cur->unitsGarrisoned;

            if(weakest == -1) {
                weakest = 0;
                weakestUnits = currentUnits;
                toDeploy = p->getReinforcements() - numArmiesDeployed;
                continue;
            }

            difference = abs(weakestUnits - currentUnits);

            if(weakestUnits > currentUnits){
                toDeploy = difference;
                weakest = i;
                weakestUnits = currentUnits;
            }
            else if(difference < toDeploy)
                toDeploy = difference;
        }

        if(toDeploy == 0)
            toDeploy = 1;

        territoryUnits.at(weakest) = territoryUnits.at(weakest) + toDeploy;
        numArmiesDeployed += toDeploy;

        auto *newDeploy = new Deploy(toDeploy, *ownedTerritories.at(weakest));
        newDeploy->setPlayerLink(*p);
        this->p->getOrdersList()->addDeploy(newDeploy);
    }

    // todo: Fortifies weakest territories

}

/**
 * Displays all adjacent territories to owned territories
 *
 * @return vector of all adjacent territories
 */
vector<Territory*> BenevolentPlayerStrategy::toAttack() {
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
vector<Territory*> BenevolentPlayerStrategy::toDefend() {
    vector<Territory *> territoriesToDefend;
    //loop through player owned territories
    for (int i = 0; i < p->getTerritorySize(); i++) {
        //loop through the adjacent territories of the owned territories
        for (int j = 0; j < p->getVTerritory().at(i)->adjacentTerritories.size(); j++) {
            //check if that territory is already owned, if the adjacent territory is not owned
            if (this->p->isOwnedTerritory(p->getVTerritory().at(i)->adjacentTerritories.at(j)->id) == nullptr &&
                !(p->isTerritoryInList(territoriesToDefend, p->getVTerritory().at(i)->id))) {
                territoriesToDefend.push_back(
                        p->getVTerritory().at(i)); //push the territory we own into list of territories to defend
            }
        }
    }
    return territoriesToDefend;
}
