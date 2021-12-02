//
// Created by Ryan on 2021-12-01.
//

#include "BenevolentPlayerStrategy.h"

BenevolentPlayerStrategy::BenevolentPlayerStrategy(Player* player) {
    this->p = player;
}

void BenevolentPlayerStrategy::issueOrder(vector<Player *> &vPlayersInPlay) {
    //Reinforce whenever possible
    if (p->getHand()->isCardOwned("Reinforcement")) {
        int reinforcementCardReward = 5;
        this->p->setReinforcements(this->p->getReinforcements() + reinforcementCardReward);
        p->getHand()->removeCard(p->getHand()->getCardIndex("Reinforcement"));
    }

    //Use reinforcement pool
    while (p->getReinforcements() )

    cout << "You have " << this->p->getReinforcements() << " armies to Deploy.\n";
    bool isOutOfReinforcementsToDeploy = false;
    int numArmiesDeployed = 0;
    while (!isOutOfReinforcementsToDeploy) {
        int numArmiesDeploy;
        int idOfTerri;
        cout << "You have " << this->p->getReinforcements()-numArmiesDeployed << " armies left to deploy." << endl;
        cout << "How many armies do you want to deploy?:";
        cin >> numArmiesDeploy;
        numArmiesDeployed = numArmiesDeployed + numArmiesDeploy;
        bool isCorrectTerriName = false;
        while (!isCorrectTerriName) {
            cout << "Here are all the territories you own:" << endl;
            this->p->displayTerritoriesOwned();

            cout << "Here are the adjacent territories to enemy territories that you own:" << endl;
            this->p->displayOwnedAdjacentTerritories();

            cout << "What territory do you want to deploy to? (write in a territory id):" << endl;
            cin >> idOfTerri;
            Territory *myTerri = p->isOwnedTerritory(idOfTerri);
            if (myTerri) {
                auto *newDeploy = new Deploy(numArmiesDeploy, *myTerri);
                newDeploy->setPlayerLink(*p);
                this->p->getOrdersList()->addDeploy(newDeploy);
                isCorrectTerriName = true;
            } else {
                cout << "Please enter a territory id that you own." << endl;
            }
        }
        //check to see if there are still reinforcements to deploy
        if (numArmiesDeployed >= this->p->getReinforcements()) {
            isOutOfReinforcementsToDeploy = true;
        }
    }
}

vector<Territory*> BenevolentPlayerStrategy::toAttack() {
    vector<Territory *> territoriesToAttack;
    return territoriesToAttack;
}

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
