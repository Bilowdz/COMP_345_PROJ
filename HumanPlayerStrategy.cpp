//
// Created by Ryan on 2021-12-01.
//

#include "HumanPlayerStrategy.h"

HumanPlayerStrategy::HumanPlayerStrategy(Player* player) {
    this->p = player;
}

void HumanPlayerStrategy::issueOrder(vector<Player *> &vPlayersInPlay) {
    //Checks if the current player own a Reinforcement card
    //If he does he can choose to use it right away, otherwise
    // he will have to wait until next turn
    if (p->getHand()->isCardOwned("Reinforcement")) {
        string input;
        cout << "You own a reinforcement card, would you like to use it (type y if yes)? ";
        cin >> input;
        if (input == "y") {
            int reinforcementCardReward = 5;
            this->p->setReinforcements(this->p->getReinforcements() + reinforcementCardReward);
            p->getHand()->removeCard(p->getHand()->getCardIndex("Reinforcement"));
        }
    }

    //Loops until the player deploys all the territories in their reinforcement pool
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

    //display the cards owned by the player:
    cout << "Cards owned by Player " << this->p->getName() << ":" << endl;

    if (p->getHand()->cardsHeld.size() == 0) {
        cout << "You do not own any cards." << endl;
    } else {
        for (int i = 0; i < p->getHand()->cardsHeld.size(); i++) {
            cout << "Name of Card: " << p->getHand()->cardsHeld.at(i)->cardType << endl;
        }
    }

    cout << "==========MENU==========" << endl;
    bool isOrderDone = false;
    while (!isOrderDone) {
        int choice;
        cout << "\n1. Advance army\n"
                "2. Bomb\n"
                "3. Blockade\n"
                "4. Airlift\n"
                "5. Negotiate\n"
                "0. Finished adding orders\n";
        cout << "What order would you like to issue:";
        cin >> choice;

        if (choice == 0) {// finish adding orders
            isOrderDone = true;
        } else if (choice == 1) { // Advance order
            int numArmiesAdvance;
            int idOfTerriSource;
            int idOfTerriTarget;
            //List of territories to attack and defend
            vector<Territory *> listOfTerritoriesToDefend = this->toDefend();
            vector<Territory *> listOfTerritoriesToAttack = this->toAttack();

            this->p->displayTerritoriesOwned();
            cout << "How many armies do you want to advance?:";
            cin >> numArmiesAdvance;
            bool isCorrectTerriNameAdvanceSource = false;
            while (!isCorrectTerriNameAdvanceSource) {
                cout << "From which territory do you want to move units? (write in territory id):" << endl;
                cin >> idOfTerriSource;
                Territory *myTerriSource = p->isOwnedTerritory(idOfTerriSource);
                if (myTerriSource) {
                    isCorrectTerriNameAdvanceSource = true;
                    bool isCorrectTerriNameAdvanceTarget = false;
                    while (!isCorrectTerriNameAdvanceTarget) {
                        this->p->displayAdjacentTerritoriesNotOwned();
                        cout << "To which territory do you want to move units? (write in territory id):" << endl;
                        cin >> idOfTerriTarget;

                        bool isValidTargetTerritoryToDefend = this->p->isTerritoryInList(listOfTerritoriesToDefend,
                                                                                      idOfTerriTarget);

                        bool isValidTargetTerritoryToAttack = this->p->isTerritoryInList(listOfTerritoriesToAttack,
                                                                                      idOfTerriTarget);

                        if (isValidTargetTerritoryToDefend || isValidTargetTerritoryToAttack) {
                            Territory *myTerriTarget = this->p->mapLink->getTerritory(idOfTerriTarget);
                            isCorrectTerriNameAdvanceTarget = true;
                            Advance *advanceOrder = new Advance(numArmiesAdvance, *myTerriSource, *myTerriTarget);
                            advanceOrder->setPlayerLink(*p);
                            this->p->getOrdersList()->addAdvance(advanceOrder);
                        } else {
                            cout << "Entered territory that does not exist. Enter a valid territory id." << endl;
                        }
                    }
                } else {
                    cout << "Entered territory that does not exist. Enter a valid territory id." << endl;
                }
            }
        } else if (choice == 2) { // Bomb order

            //check to see if we own Bomb card
            if (!p->getHand()->isCardOwned("Bomb")) {
                cout << "You do not own a Bomb card" << endl;
                continue;
            }

            int idOfTerriToBomb;
            bool isCorrectBomb = false;
            while (!isCorrectBomb) {
                this->p->mapLink->displayTerritories();
                cout << "Where would you like to bomb?" << endl;
                cin >> idOfTerriToBomb;
                Territory *territoryToBomb = this->p->mapLink->isTerritory(idOfTerriToBomb);
                if (territoryToBomb) {
                    isCorrectBomb = true;
                    Bomb *bombOrder = new Bomb(*territoryToBomb);
                    bombOrder->setPlayerLink(*p);
                    this->p->getOrdersList()->addBomb(bombOrder);
                } else {
                    cout << "Entered territory that does not exist. Enter a valid territory id.";
                }
            }
        } else if (choice == 3) { // Blockade order
            //Checks to see if we own a blockade card in our hand
            if (!p->getHand()->isCardOwned("Blockade")) {
                cout << "You do not own a Blockade card" << endl;
                continue;
            }

            //make sure the target territory is a real terri
            int idOfTerriToBlockade;
            bool isCorrectBlockade = false;
            while (!isCorrectBlockade) {
                this->p->displayOwnedAdjacentTerritories();
                cout << "Where would you like to blockade" << endl;
                cin >> idOfTerriToBlockade;
                Territory *territoryToBlockade = this->p->mapLink->isTerritory(idOfTerriToBlockade);
                if (territoryToBlockade) {
                    isCorrectBlockade = true;
                    Blockade *blockadeOrder = new Blockade(*territoryToBlockade);
                    blockadeOrder->setPlayerLink(*p);
                    p->getOrdersList()->addBlockade(blockadeOrder);
                    p->getHand()->removeCard(p->getHand()->getCardIndex("Blockade"));
                } else {
                    cout << "Entered territory that does not exist. Enter a valid territory id.";
                }
            }
        } else if (choice == 4) { // Airlift order
            //Checks to see if player owns an airlift card
            if (!p->getHand()->isCardOwned("Airlift")) {
                cout << "You do not own a Airlift card" << endl;
                continue;
            }

            // number of armies that we move from source territory to target territory
            int numberOfArmiesToSend;
            int idOfTerriSource;
            int idOfTerriTarget;

            bool isCorrectAirlift = false;
            while (!isCorrectAirlift) {
                p->displayTerritoriesOwned();
                cout << "From which territory do you want to move units? (write in territory id):" << endl;
                cin >> idOfTerriSource;
                Territory *myTerriSource = p->isOwnedTerritory(idOfTerriSource);
                if (myTerriSource) {
                    isCorrectAirlift = true;
                    cout << "How many armies do you want to advance?:";
                    cin >> numberOfArmiesToSend;
                    bool isCorrectTerriNameAirLift = false;
                    while (!isCorrectTerriNameAirLift) {
                        p->mapLink->displayTerritories();
                        cout << "To which territory do you want to move units? (write in territory id):" << endl;
                        cin >> idOfTerriTarget;
                        Territory *myTerriTarget = p->mapLink->isTerritory(idOfTerriTarget);
                        if (myTerriTarget) {
                            isCorrectTerriNameAirLift = true;
                            Airlift *airliftOrder = new Airlift(numberOfArmiesToSend, *myTerriSource, *myTerriTarget);
                            airliftOrder->setPlayerLink(*p);
                            p->getOrdersList()->addAirlift(airliftOrder);
                            p->getHand()->removeCard(p->getHand()->getCardIndex("Airlift"));
                        } else {
                            cout << "Entered territory that does not exist. Enter a valid territory id.";
                        }
                    }
                } else {
                    cout << "Entered territory that does not exist. Enter a valid territory id.";
                }
            }
        } else if (choice == 5) { // Negotiate order
            //Checks in hand if the player owns a diplomacy
            if (!p->getHand()->isCardOwned("Diplomacy")) {
                cout << "You do not own a Diplomacy card" << endl;
                continue;
            }

            string nameOfPlayerToNegotiate;
            bool isNameValid = false;
            int playerIndex;
            while (!isNameValid) {
                cout << "Which player do you want to negotiate with?" << endl;
                cin >> nameOfPlayerToNegotiate;
                playerIndex = p->validPlayer(vPlayersInPlay, nameOfPlayerToNegotiate);

                if (playerIndex != -1) {
                    isNameValid = true;
                    Negotiate *negotiating = new Negotiate(*vPlayersInPlay.at(playerIndex));
                    negotiating->setPlayerLink(*p);
                    p->getOrdersList()->addNegotiate(negotiating);
                    int lastOrder = p->getOrdersList()->getList().size();
                    p->getOrdersList()->getList().at(lastOrder-1)->validate(*p);
                    p->getOrdersList()->remove(lastOrder-1);
                } else {
                    cout << "That name is not on the list. Please enter a valid name" << endl;
                }
            }
        } else {
            //If they did not eneter a number in the menu it runs again
            cout << "Please enter a valid number." << endl;
        }
    }
}
vector<Territory*> HumanPlayerStrategy::toAttack() {
    
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
vector<Territory*> HumanPlayerStrategy::toDefend() {
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
