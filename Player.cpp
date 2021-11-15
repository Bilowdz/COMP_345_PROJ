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
Player::Player(vector<Territory *> vTerritories, Hand* vHand, OrdersList * ordersList) {
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
Player::Player(string *name, vector<Territory *> vTerritories, Hand * vHand, OrdersList * ordersList) {
    (*this).name = *name;
    this->vTerritory = vTerritories;
    this->vHand = vHand;
    this->ordersList = ordersList;
}

/**
 * Copy constructor
 *
 * @param copyPlayer is the Class we would like to copy
 */
Player::Player(Player const &copyPlayer) {
    name = copyPlayer.name;
    for (int i = 0; i < copyPlayer.vTerritory.size(); ++i) {
        vTerritory.at(i) = copyPlayer.vTerritory.at(i);
    }
    for (int i = 0; i < copyPlayer.vHand->cardsHeld.size(); ++i) {
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
    for (int i = 0; i < copyPlayer.vTerritory.size(); ++i) {
        this->vTerritory.at(i) = copyPlayer.vTerritory.at(i);
    }
    for (int i = 0; i < copyPlayer.vHand->cardsHeld.size(); ++i) {
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
    for (int j = 0; j < player.getTerritorySize(); ++j) {
       // output << "\t" + player.getTerritoriesOwned(j) << endl;
    }
    output << "Cards Owned: \n";
    for (int k = 0; k < player.getHandSize(); ++k) {
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

/**
 * All the territories that the current player can defend
 */
void Player::toDefend() {
    for (int i = 0; i < vTerritory.size(); ++i) {
        cout << "\t" + vTerritory.at(i)->name << endl;
    }
}

/**
 * All the territories the player can attack
 *
 * @param vPlayer the vector of all Players in the game
 */
void Player::toAttack(vector<Player *> vPlayers) {
    for (int i = 0; i < vPlayers.size(); ++i) {
        //Compare the names of the players
        if (vPlayers.at(i)->getName().compare(name) != 0) {
            for (int j = 0; j < vPlayers.at(i)->getTerritorySize(); ++j) {
                cout << "\t" + vPlayers.at(i)->vTerritory.at(j)->name << endl;
            }
        }
    }
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
Territory * Player::getTerritoriesOwned(int vIndex) {
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

///**
// * Gets the number of cards the player has in its hand
// *
// * @param vIndex the current card from the list of Hands
// * @return the number of the current card
// */
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

Orders* Player::getOrder(int vIndex) {
    return this->ordersList->getListMember(vIndex);
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

void Player::issueOrder() {
    //make a menu to select what order to add
    bool isOrderDone = false;
    while(!isOrderDone) {
        int choice;
        cout << "1. Deploy order\n"
                "2. Advance army\n"
                "3. Bomb\n"
                "4. Blockade\n"
                "5. Airlift\n"
                "6. Negotiate\n"
                "0. Finished adding orders\n";
        cout << "What order would you like to issue:";
        cin >> choice;

        if (choice == 0) // finish adding orders
                isOrderDone = true;
        else if (choice == 1) { // Deploy order
            int numArmiesDeploy;
            int idOfTerri;
            cout << "How many armies do you want to deploy?:";
            cin >> numArmiesDeploy;
            bool isCorrectTerriName = false;
            while (!isCorrectTerriName) {
                this->displayTerritoriesOwned();
                cout << "What territory do you want to deploy to? (write in territory id):" << endl;
                cin >> idOfTerri;
                Territory *myTerri = isOwnedTerritory(idOfTerri);
                if (myTerri) {
                    auto *newDeploy = new Deploy(numArmiesDeploy, *myTerri);
                    this->ordersList->addDeploy(newDeploy);
                    isCorrectTerriName = true;
                } else {
                    cout << "Please enter a territory id that you own." << endl;
                }
            }
        }
        else if (choice == 2) { // Advance order
            int numArmiesAdvance;
            int idOfTerriSource;
            int idOfTerriTarget;
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
                        this->mapLink->displayTerritories();
                        cout << "To which territory do you want to move units? (write in territory id):" << endl;
                        cin >> idOfTerriTarget;
                        Territory *myTerriTarget = this->mapLink->isTerritory(idOfTerriTarget);
                        if (myTerriTarget) {
                            isCorrectTerriNameAdvanceTarget = true;
                            Advance *advanceOrder = new Advance(numArmiesAdvance, *myTerriSource, *myTerriTarget);
                            this->ordersList->addAdvance(advanceOrder);
                        } else {
                            cout << "Entered territory that does not exist. Enter a valid territory id.";
                        }
                    }
                } else {
                    cout << "Entered territory that does not exist. Enter a valid territory id.";
                }
            }
        }
        else if (choice == 3) { // Bomb order
            cout << "choice 3";
        }
        else if (choice == 4) { // Blockade order
            cout << "choice 4";
        }
        else if (choice == 5) { // Airlift order
            cout << "choice 5";
        }
        else if (choice == 6) { // Negotiate order
            cout << "choice 6";
        }
    }
}


Territory * Player::isOwnedTerritory(int id) {
    for (int i = 0; i < vTerritory.size(); i++) {
        if(vTerritory.at(i)->id == id) {
            return vTerritory.at(i);
        }
    }
    return nullptr;
}

void Player::displayTerritoriesOwned() {
    for (int i = 0; i < vTerritory.size(); i++) {
        cout << "Name: " << vTerritory.at(i)->name << " ID: " << vTerritory.at(i)->id << endl;
    }
}

void Player::addTerritory(Territory * territory) {
    vTerritory.push_back(territory);
}

void Player::removeTerritory(Territory *territory) {

    for (int i = 0; i < vTerritory.size(); ++i) {

        if(territory->id == vTerritory.at(i)->id) {
            vTerritory.erase(vTerritory.begin() + i);
        }
    }

}

Hand * Player::getHand() {
    return this->vHand;
}

const vector<int *> &Player::getTerritoriesOwnedPerContinent() const {
    return territoriesOwnedPerContinent;
}

void Player::setTerritoriesOwnedPerContinent(int size) {
    for (int i = 0; i < size; ++i) {
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





