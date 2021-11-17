//
// Created by Ryan on 2021-09-24.
//

#include "Player.h"

/**
* Default Constructor
*/
Player::Player() = default;

/**
 * Constructor that only takes in a name pointer
 * @param name pointer for the name of the player
 */
Player::Player(string *name) {
    this->name = *name;
}

/**
* Constructor that takes in the following parameters
*
* @param vTerritories is the vector Territory pointer of all the territories the player owns
* @param vHand is the vector Hand pointer of all the hand the player owns
* @param ordersList is the vector Order pointer of all the orders the player can do
*/
Player::Player(vector<Territory *> vTerritories, Hand *vHand, OrdersList *ordersList) {
    this->vTerritory = vTerritories;
    this->vHand = vHand;
    this->ordersList = ordersList;
}

/**
 * Constructor that takes in the following parameters
 *
 * @param name is the name of the player
 * @param vTerritories is the vector Territory pointer of all the territories the player owns
 * @param vHand is the vector Hand pointer of all the hand the player owns
 * @param ordersList is the vector Order pointer of all the orders the player can do
 */
Player::Player(string *name, vector<Territory *> vTerritories, Hand *vHand, OrdersList *ordersList) {
    (*this).name = *name;
    this->vTerritory = vTerritories;
    this->vHand = vHand;
    this->ordersList = ordersList;
    this->reinforcements = 0;
}

/**
 * Copy constructor
 *
 * @param copyPlayer is the Class we would like to copy
 */
Player::Player(Player const &copyPlayer) {
    name = copyPlayer.name;
    for (int i = 0; i < copyPlayer.vTerritory.size(); i++) {
        vTerritory.at(i) = copyPlayer.vTerritory.at(i);
    }
    for (int i = 0; i < copyPlayer.vHand->cardsHeld.size(); i++) {
        vHand->cardsHeld.at(i) = copyPlayer.vHand->cardsHeld.at(i);
    }
    ordersList = copyPlayer.ordersList;
}

/**
 * Assignment operator
 *
 * @param p constant player class
 * @return address of Player.
 */
Player &Player::operator=(const Player &copyPlayer) {

    this->name = copyPlayer.name;
    for (int i = 0; i < copyPlayer.vTerritory.size(); i++) {
        this->vTerritory.at(i) = copyPlayer.vTerritory.at(i);
    }
    for (int i = 0; i < copyPlayer.vHand->cardsHeld.size(); i++) {
        this->vHand->cardsHeld.at(i) = copyPlayer.vHand->cardsHeld.at(i);
        this->vHand->cardsHeld.at(i) = copyPlayer.vHand->cardsHeld.at(i);
    }
    this->ordersList = copyPlayer.ordersList;
    return *this;
}

/**
 * Destructor
 */
Player::~Player() {
    for (auto &i: vTerritory) {
        delete i;
    }
    for (auto &i: vHand->cardsHeld) {
        delete i;
    }
    cout << "Destructor !" << endl;
}

/**
 * Ostream operator to output territory, hand and order of each player
 *
 * @param output operator
 * @param player is the player we are currently looking at
 * @return the output to the terminal
 */
ostream &operator<<(ostream &output, Player &player) {

    output << "Player Name: " << player.getName() << endl;
    output << "Territories Owned: \n";
    for (int j = 0; j < player.getTerritorySize(); j++) {
        // output << "\t" + player.getTerritoriesOwned(j) << endl;
    }
    output << "Cards Owned: \n";
    for (int k = 0; k < player.getHandSize(); k++) {
        output << "\tCard Number: " + to_string(player.getCardsOwned(k)) << endl;
    }
    output << "Orders Sent: \n";
//    for (int l = 0; l < player.getNumberOfOrders(); ++l) {
//        output << "\t" + player.getOrder(l) << " " + to_string(l + 1) << endl;
//    }
    output << "Territories to defend: \n";
    player.toDefend();
    output << "\n";

    return output;
}

void Player::displayTerritoriesOwned() {
    for (int i = 0; i < vTerritory.size(); i++) {
        cout << "Name: " << vTerritory.at(i)->name << " ID: " << vTerritory.at(i)->id << endl;
    }
}

/**
 * All the territories adjacent to the player that he can attack
 *
 * @param vPlayer the vector of all Players in the game
 */
vector<Territory *> Player::toAttack() {

    vector<Territory *> territoriesToAttack;
    //loop through player owned territories
    for (int i = 0; i < getTerritorySize(); i++) {
        //loop through the adjacent territories of the owned territories
        for (int j = 0; j < vTerritory.at(i)->adjacentTerritories.size(); j++) {
            //check if that territory is already owned, if its now owned then add to list
            if (this->isOwnedTerritory(vTerritory.at(i)->adjacentTerritories.at(j)->id) == nullptr &&
                !(isTerritoryInList(territoriesToAttack, vTerritory.at(i)->adjacentTerritories.at(j)->id))) {
                territoriesToAttack.push_back(vTerritory.at(i)->adjacentTerritories.at(j));
            }
        }
    }
    return territoriesToAttack;
}

/**
 * All the territories that the current player can defend
 * Returns a list of territories that the player owns
 */
vector<Territory *> Player::toDefend() {

    vector<Territory *> territoriesToDefend;
    //loop through player owned territories
    for (int i = 0; i < getTerritorySize(); i++) {
        //loop through the adjacent territories of the owned territories
        for (int j = 0; j < vTerritory.at(i)->adjacentTerritories.size(); j++) {
            //check if that territory is already owned, if the adjacent territory is not owned
            if (this->isOwnedTerritory(vTerritory.at(i)->adjacentTerritories.at(j)->id) == nullptr &&
                !(isTerritoryInList(territoriesToDefend, vTerritory.at(i)->id))) {
                territoriesToDefend.push_back(
                        vTerritory.at(i)); //push the territory we own into list of territories to defend
            }
        }
    }
    return territoriesToDefend;
}

void Player::displayAdjacentTerritoriesNotOwned() {

    for (int i = 0; i < this->toAttack().size(); i++) {
        cout << "Name: " << this->toAttack().at(i)->name <<
             " ID: " << this->toAttack().at(i)->id << endl;
    }
}

void Player::displayOwnedAdjacentTerritories() {

    for (int i = 0; i < this->toDefend().size() - 1; i++) {
        cout << "Name: " << this->toDefend().at(i)->name <<
             " ID: " << this->toDefend().at(i)->id << endl;
    }
}

/**
 * Pass in a territory id to see if its in the given list of Territories
 *
 * @param listOfTerritories
 * @param idOfTerritory
 * @return
 */
bool Player::isTerritoryInList(vector<Territory *> listOfTerritories, int idOfTerritory) {
    for (int i = 0; i < listOfTerritories.size(); i++) {
        if (idOfTerritory == listOfTerritories.at(i)->id) {
            return true;
        }
    }
    return false;
}

/**
 * Set the territories that the player owns
 *
 * @param vTerritories vector Territory that gets passed in
 */
void Player::setTerritoriesOwned(vector<Territory *> vTerritories) {
    vTerritory = vTerritories;
}

/**
 * Gets all the territories the current player owns.
 *
 * @param vIndex is the current territory from the list of territories
 * @return the name of the territory
 */
Territory *Player::getTerritoriesOwned(int vIndex) {
    return vTerritory.at(vIndex);
}

/**
 * Gets the size of all the territories the player owns
 *
 * @return an int of the size
 */
int Player::getTerritorySize() const {
    return vTerritory.size();
}

/**
 * Gets the number of cards the player has in its hand
 *
 * @param vIndex the current card from the list of Hands
 * @return the number of the current card
 */
int Player::getCardsOwned(int vIndex) {
    return 0;
    //return vHand->at(vIndex).size(); todo uncommment
}

/**
 * Gets the number of cards in the players hand
 *
 * @return the int for amount of cards
 */
int Player::getHandSize() const {
    return vHand->cardsHeld.size();
}

Orders *Player::getOrder(int vIndex) {
    return this->ordersList->getListMember(vIndex);
}

OrdersList *Player::getOrdersList() {
    return this->ordersList;
}

/**
 * Gets the name of the current player
 *
 * @return the name of the player
 */
string Player::getName() const {
    //same as (*this).name
    return this->name;
}

/**
 * Sets the name of the player
 */
void Player::setName(string s) {
    this->name = std::move(s);
}

void Player::setReinforcements(int armies) {
    this->reinforcements = armies;
}

int Player::getReinforcements() {
    return this->reinforcements;
}

void Player::issueOrder(vector<Player *> &vPlayersInPlay) {


    if (vHand->isCardOwned("Reinforcement")) {
        string input;
        cout << "You own a reinforcement card, would you like to use it (type y if yes)? ";
        cin >> input;
        if (input == "y") {
            int reinforcementCardReward = 5;
            this->setReinforcements(this->getReinforcements() + reinforcementCardReward);
            vHand->removeCard(vHand->getCardIndex("Reinforcement"));
        }
    }

    cout << "You have " << this->getReinforcements() << " armies to Deploy.\n";
    bool isOutOfReinforcementsToDeploy = false;
    int numArmiesDeployed = 0;
    while (!isOutOfReinforcementsToDeploy) {
        int numArmiesDeploy;
        int idOfTerri;
        cout << "You have " << this->getReinforcements()-numArmiesDeployed << " armies left to deploy." << endl;
        cout << "How many armies do you want to deploy?:";
        cin >> numArmiesDeploy;
        numArmiesDeployed = numArmiesDeployed + numArmiesDeploy;
        bool isCorrectTerriName = false;
        while (!isCorrectTerriName) {
            cout << "Here are all the territories you own:" << endl;
            this->displayTerritoriesOwned();

            cout << "Here are the adjacent territories to enemy territories that you own:" << endl;
            this->displayOwnedAdjacentTerritories();

            cout << "What territory do you want to deploy to? (write in a territory id):" << endl;
            cin >> idOfTerri;
            Territory *myTerri = isOwnedTerritory(idOfTerri);
            if (myTerri) {
                auto *newDeploy = new Deploy(numArmiesDeploy, *myTerri);
                newDeploy->setPlayerLink(*this);
                this->ordersList->addDeploy(newDeploy);
                isCorrectTerriName = true;
            } else {
                cout << "Please enter a territory id that you own." << endl;
            }
        }
        //check to see if there are still reinforcements to deploy
        if (numArmiesDeployed >= this->getReinforcements()) {
            isOutOfReinforcementsToDeploy = true;
        }
    }

    //display the cards owned by the player:
    cout << "Cards owned by Player " << this->getName() << ":" << endl;

    if (vHand->cardsHeld.size() == 0) {
        cout << "You do not own any cards." << endl;
    } else {
        for (int i = 0; i < vHand->cardsHeld.size(); i++) {
            cout << "Name of Card: " << vHand->cardsHeld.at(i)->cardType << endl;
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

            vector<Territory *> listOfTerritoriesToDefend = this->toDefend();
            vector<Territory *> listOfTerritoriesToAttack = this->toAttack();

            cout << "How many armies do you want to advance?:";
            cin >> numArmiesAdvance;
            bool isCorrectTerriNameAdvanceSource = false;
            while (!isCorrectTerriNameAdvanceSource) {
                this->displayTerritoriesOwned();
                cout << "From which territory do you want to move units? (write in territory id):" << endl;
                cin >> idOfTerriSource;
                Territory *myTerriSource = isOwnedTerritory(idOfTerriSource);
                if (myTerriSource) {
                    isCorrectTerriNameAdvanceSource = true;
                    bool isCorrectTerriNameAdvanceTarget = false;
                    while (!isCorrectTerriNameAdvanceTarget) {
                        this->displayAdjacentTerritoriesNotOwned();
                        cout << "To which territory do you want to move units? (write in territory id):" << endl;
                        cin >> idOfTerriTarget;

                        bool isValidTargetTerritoryToDefend = this->isTerritoryInList(listOfTerritoriesToDefend,
                                                                                      idOfTerriTarget);

                        bool isValidTargetTerritoryToAttack = this->isTerritoryInList(listOfTerritoriesToAttack,
                                                                                      idOfTerriTarget);

                        if (isValidTargetTerritoryToDefend || isValidTargetTerritoryToAttack) {
                            Territory *myTerriTarget = this->mapLink->getTerritory(idOfTerriTarget);
                            isCorrectTerriNameAdvanceTarget = true;
                            Advance *advanceOrder = new Advance(numArmiesAdvance, *myTerriSource, *myTerriTarget);
                            advanceOrder->setPlayerLink(*this);
                            this->ordersList->addAdvance(advanceOrder);
                        } else {
                            cout << "Entered territory that does not exist. Enter a valid territory id.";
                        }
                    }
                } else {
                    cout << "Entered territory that does not exist. Enter a valid territory id.";
                }
            }
        } else if (choice == 2) { // Bomb order

            //check to see if we own Bomb card
            if (!vHand->isCardOwned("Bomb")) {
                cout << "You do not own a Bomb card" << endl;
                return;
            }

            int idOfTerriToBomb;
            bool isCorrectBomb = false;
            while (!isCorrectBomb) {
                this->mapLink->displayTerritories();
                cout << "Where would you like to bomb?" << endl;
                cin >> idOfTerriToBomb;
                Territory *territoryToBomb = this->mapLink->isTerritory(idOfTerriToBomb);
                if (territoryToBomb) {
                    isCorrectBomb = true;
                    Bomb *bombOrder = new Bomb(*territoryToBomb);
                    bombOrder->setPlayerLink(*this);
                    this->ordersList->addBomb(bombOrder);
                    vHand->removeCard(vHand->getCardIndex("Bomb"));
                } else {
                    cout << "Entered territory that does not exist. Enter a valid territory id.";
                }
            }
        } else if (choice == 3) { // Blockade order

            if (!vHand->isCardOwned("Blockade")) {
                cout << "You do not own a Blockade card" << endl;
                return;
            }

            //make sure the target territory is a real terri
            int idOfTerriToBlockade;
            bool isCorrectBlockade = false;
            while (!isCorrectBlockade) {
                this->displayOwnedAdjacentTerritories();
                cout << "Where would you like to blockade" << endl;
                cin >> idOfTerriToBlockade;
                Territory *territoryToBlockade = this->mapLink->isTerritory(idOfTerriToBlockade);
                if (territoryToBlockade) {
                    isCorrectBlockade = true;
                    Blockade *blockadeOrder = new Blockade(*territoryToBlockade);
                    blockadeOrder->setPlayerLink(*this);
                    this->ordersList->addBlockade(blockadeOrder);
                    vHand->removeCard(vHand->getCardIndex("Blockade"));
                } else {
                    cout << "Entered territory that does not exist. Enter a valid territory id.";
                }
            }
        } else if (choice == 4) { // Airlift order

            if (!vHand->isCardOwned("Airlift")) {
                cout << "You do not own a Airlift card" << endl;
                return;
            }

            // number of armies that we move from source territory to target territory
            int numberOfArmiesToSend;
            int idOfTerriSource;
            int idOfTerriTarget;

            bool isCorrectAirlift = false;
            while (!isCorrectAirlift) {
                this->displayTerritoriesOwned();
                cout << "From which territory do you want to move units? (write in territory id):" << endl;
                cin >> idOfTerriSource;
                Territory *myTerriSource = isOwnedTerritory(idOfTerriSource);
                if (myTerriSource) {
                    isCorrectAirlift = true;
                    cout << "How many armies do you want to advance?:";
                    cin >> numberOfArmiesToSend;
                    bool isCorrectTerriNameAirLift = false;
                    while (!isCorrectTerriNameAirLift) {
                        this->mapLink->displayTerritories();
                        cout << "To which territory do you want to move units? (write in territory id):" << endl;
                        cin >> idOfTerriTarget;
                        Territory *myTerriTarget = this->mapLink->isTerritory(idOfTerriTarget);
                        if (myTerriTarget) {
                            isCorrectTerriNameAirLift = true;
                            Airlift *airliftOrder = new Airlift(numberOfArmiesToSend, *myTerriSource, *myTerriTarget);
                            airliftOrder->setPlayerLink(*this);
                            this->ordersList->addAirlift(airliftOrder);
                            vHand->removeCard(vHand->getCardIndex("Airlift"));
                        } else {
                            cout << "Entered territory that does not exist. Enter a valid territory id.";
                        }
                    }
                } else {
                    cout << "Entered territory that does not exist. Enter a valid territory id.";
                }
            }
        } else if (choice == 5) { // Negotiate order

            if (!vHand->isCardOwned("Diplomacy")) {
                cout << "You do not own a Diplomacy card" << endl;
                return;
            }

            string nameOfPlayerToNegotiate;
            bool isNameValid = false;
            int playerIndex;
            while (!isNameValid) {
                cout << "Which player do you want to negotiate with?" << endl;
                cin >> nameOfPlayerToNegotiate;
                playerIndex = validPlayer(vPlayersInPlay, nameOfPlayerToNegotiate);

                if (playerIndex != -1) {
                    isNameValid = true;
                    Negotiate *negotiating = new Negotiate(*vPlayersInPlay.at(playerIndex));
                    negotiating->setPlayerLink(*this);
                    this->ordersList->addNegotiate(negotiating);
                    vHand->removeCard(vHand->getCardIndex("Diplomacy"));
                } else {
                    cout << "That name is not on the list. Please enter a valid name" << endl;
                }
            }
        } else {
            cout << "Please enter a valid number." << endl;
            return;
        }
    }
}

Territory *Player::isOwnedTerritory(int id) {
    for (int i = 0; i < vTerritory.size() - 1; i++) {
        if (vTerritory.at(i)->id == id) {
            return vTerritory.at(i);
        }
    }
    return nullptr;
}


void Player::addTerritory(Territory *territory) {
    vTerritory.push_back(territory);
    this->setIncrementTerritoryCount(territory->continent-1);
}

void Player::removeTerritory(Territory *territory) {
    for (int i = 0; i < vTerritory.size(); i++) {
        if (territory->id == vTerritory.at(i)->id) {
            vTerritory.erase(vTerritory.begin() + i);
        }
    }
    this->setDecrementTerritoryCount(territory->continent-1);
}

Hand *Player::getHand() {
    return this->vHand;
}

//Hand * Player::setHand() {
//
//}

const vector<int> &Player::getTerritoriesOwnedPerContinent() const {
    return territoriesOwnedPerContinent;
}

void Player::setTerritoriesOwnedPerContinent() {
    for (int i = 0; i < mapLink->continents.size(); i++) {
        //if the total number of continents is 3 then it will loop 3 times and set the vector to a size of 3
        this->territoriesOwnedPerContinent.push_back(0);
    }
}

void Player::setIncrementTerritoryCount(int index) {
    this->territoriesOwnedPerContinent.at(index) = this->territoriesOwnedPerContinent.at(index) + 1;
}

void Player::setDecrementTerritoryCount(int index) {
    this->territoriesOwnedPerContinent.at(index) = this->territoriesOwnedPerContinent.at(index) - 1;
}

int Player::validPlayer(vector<Player *> validPlayers, string name) {
    for (int i = 0; i < validPlayers.size(); i++) {
        if (name.compare(validPlayers.at(i)->getName()) == 0) {
            return i;
        } else {
            return -1;
        }
    }
    return -1;
}

void Player::setMapLink(Map *map) {
    this->mapLink = map;
}

void Player::setDeckLink(Deck *deck) {
    this->deckLink = deck;
}

void Player::addReinforcements(int armiesToAdd) {
    this->reinforcements += armiesToAdd;
}

void Player::removeReinforcements(int armiesToRemove) {
    this->reinforcements -= armiesToRemove;
}



