//
// Created by Nicolo on 2021-09-24.
//
#include "GameEngine.h"
#include "CommandProcessing.h"
using namespace std;

// constructor
GameEngine::GameEngine(): isGameDone(false), currentState(ST_START) {
    cout << "GameEngine constructor called" << endl;
}

// copy constructors
GameEngine::GameEngine(const GameEngine &game): isGameDone(false), currentState(game.currentState) {
    cout << "GameEngine copy constructor called" << endl;
}

GameEngine::GameEngine(GameEngine *const pGameEngine): isGameDone(false), currentState(pGameEngine->currentState) {
    cout << "GameEngine copy constructor 2 called" << endl;
}

// destructor
GameEngine:: ~GameEngine() = default;

// validate and execute transitions based on current state
bool GameEngine::transition(Command *c) {
    string command= c->getCommand();
    string loadmap = "loadmap";
    string addplayer = "addplayer";

    if(command.rfind(loadmap,0) == 0) {
        // only transition from valid states
        if(currentState == ST_START || currentState == ST_MAP_LOADED) {

            // valid transition to state map loaded, so travel to state
            currentState = ST_MAP_LOADED;

            // execute game engine function
            this->loadmap(c);
            return true;
        }
    }else if(command == "validatemap") {
        if(currentState == ST_MAP_LOADED) {
            currentState = ST_MAP_VALIDATED;
            this->validatemap();
            return true;
        }
    }else if(command == "addplayer") {
        if(currentState == ST_MAP_VALIDATED || currentState == ST_PLAYERS_ADDED) {
            currentState = ST_PLAYERS_ADDED;
            this->addplayer(c);
            return true;
        }
    }else if(command == "assigncountries") {
        if(currentState == ST_PLAYERS_ADDED) {
            currentState = ST_ASSIGN_REINFORCEMENT;
            this->assigncountries();
            return true;
        }
    }else if(command == "issueorders") {
        if(currentState == ST_ASSIGN_REINFORCEMENT || currentState == ST_ISSUE_ORDERS) {
            currentState = ST_ISSUE_ORDERS;
            this->issueorder();
            return true;
        }
    }else if(command == "endissueorders") {
        if(currentState == ST_ISSUE_ORDERS) {
            currentState = ST_EXECUTE_ORDERS;
            this->endissueorders();
            return true;
        }
    }else if(command == "execorder") {
        if(currentState == ST_ISSUE_ORDERS || currentState == ST_EXECUTE_ORDERS) {
            currentState = ST_EXECUTE_ORDERS;
            this->execorder();
            return true;
        }
    }else if(command == "endexecorders") {
        if(currentState == ST_EXECUTE_ORDERS) {
            currentState = ST_ASSIGN_REINFORCEMENT;
            this->endexecorders();
            return true;
        }
    }else if(command == "win") {
        if(currentState == ST_EXECUTE_ORDERS) {
            currentState = ST_WIN;
            this->win();
            return true;
        }
    }else if(command == "play") {
        if(currentState == ST_WIN) {
            currentState = ST_START;
            this->play();
            return true;
        }
    }else if(command == "end") {
        if(currentState == ST_WIN) {
            currentState = ST_END;
            this->end();
            this->isGameDone = true;
            return true;
        }
    }

    /*
         try {
             throw T_ERROR;
         } catch (Transition t) {
             cout << " An error has occurred. Exception: '" << t << "'" << endl;
         }
         */
    return false;
}

// return enum value currentState
State GameEngine::getState() {
    return currentState;
}

void GameEngine::loadmap(Command *c) {
    /*
    cout << "Chose between any of the following files:\n" <<
        "1: Europe\n"<<
        "2: Canada\n"<<
        "3: Zertina\n"<<endl;
*/
    string command = c->getCommand(); //command = "loadmap zertina.map"
    int mapChosen;

    if(command == "loadmap zertina.map") {
        mapChosen=3;
    } else if(command == "loadmap bigeurope.map") {
        mapChosen=1;
    } else if(command == "loadmap canada.map") {
        mapChosen=2;

        // invalid map
    } else {

    }

    MapLoader load;
    gameMap = *load.maps.at(mapChosen-1);

}

void GameEngine::validatemap() {
    cout << "Validating Map";
    if(gameMap.Validate())
        cout << "Map is valid";
    else {
        cout << "Map is not valid";
        exit(0);
    }
}

void GameEngine::addplayer(Command * c) {

    // get the name from command object
    string *name = new string((c->getCommand()).substr(10));

    Players.push_back(new Player(name));

    //shuffle(Players.begin(), Players.end(), 15); todo uncommment
}

void GameEngine::gamestart() {
    *MainDeck = *new Deck(Players.size());
    for(auto & Player : Players){
        MainDeck->Draw(Player->getHand());
        MainDeck->Draw(Player->getHand());
    }
    assigncountries();
}

void GameEngine::assigncountries() {
    for(int i = 0; i < gameMap.map.size(); i++)
    {
        Players.at(i%Players.size())->addTerritory(gameMap.map.at(i));
    }
}

void GameEngine::issueorder() {
    //transition(T_ISSUE_ORDER);
    cout << "Executing function issueorder" << endl;
}

void GameEngine::execorder() {
    //transition(T_EXEC_ORDER);
    cout << "Executing function execorder" << endl;
}

void GameEngine::endexecorders() {
    //transition(T_END_EXEC_ORDERS);
    cout << "Executing function endexecorders" << endl;
}

void GameEngine::endissueorders() {
    //transition(T_END_ISSUE_ORDERS);
    cout << "Executing function endissueorders" << endl;
}

void GameEngine::win() {
    //transition(T_WIN);
    cout << "Executing function win" << endl;
}

void GameEngine::end() {
    //transition(T_END);
    cout << "Executing function end" << endl;
}

void GameEngine::play() {
    //transition(T_PLAY);
    cout << "Executing function play" << endl;
}

// assignment operator overload
GameEngine& GameEngine::operator =(const GameEngine &ge) {
    this->currentState = ge.currentState;

    return *this;
}

// stream insertion operator overloads
ostream & operator << (ostream &out, const GameEngine &ge)
{
    out << "Current State:" << enum_state_str[ge.currentState] << endl;
    return out;
}

void GameEngine::startupPhase(CommandProcessor cp, GameEngine *ge){
    while(true) {

        // get command
        Command *c = cp.getCommand(ge);
        string commandName = c->getCommand();

        // stop startup phase once game started
        if(commandName == "gamestart") {
            break;
        } else {
            transition(c);
        }
    }
}


//added by ryan
//TODO implement this shit
//TODO mainGameLoop loops the reinforcment, issueorder and executeorder phases
//TODO continues until one player owns all territories
//TODO must also remove players that do not own any territories

//vector<Territory *> generateTerritories(int numTerritoryOwned);
//vector<Hand *> generateHand(int numberCardsPerPlayer);
//
//static int territoryNumber = 1;
//static int cardNumber = 1;
//static const int territoriesOwnedPerPlayer = 5;
//static const int numCardsPerPlayer = 3;
//
//vector<Territory *> generateTerritories(int numTerritoryOwned) {
//    vector<Territory *> vTerritory;
//    Territory *pPlayerTerritory;
//    for (int i = 0; i < numTerritoryOwned; i++) {
//        pPlayerTerritory = new Territory(i, "Territory " + to_string(territoryNumber), 1);
//        vTerritory.push_back(pPlayerTerritory);
//        territoryNumber++;
//    }
//    return vTerritory;
//}
//
///**
// * Generates the cards for each player
// *
// * @param numCardsPerPlayer the initial amount of cards per player
// * @return vector of Hands that gets passed into the player vector
// */
//vector<Hand *> generateHand(int numberCardsPerPlayer) {
//    vector<Hand *> vHand;
//    Hand *pHand;
//    for (unsigned i = 0; i < numberCardsPerPlayer; i++) {
//        pHand = new Hand();
//        pHand->ReceiveCard(new Card( "Bomb"));
//        vHand.push_back(pHand);
//        cardNumber++;
//    }
//    return vHand;
//}

//reinforcement phase: number of territories they own, (# of territories owned divided by 3, rounded down)
void GameEngine::mainGameLoop() {
//call issue order to each player
    //TODO add a loop until one player wins, and remove players that do not own anymore territories
    //TODO implement all of the below functions into this mainGameLoop function

//    OrdersList * ordersListObj = new OrdersList();
//    Territory * territory = new Territory(5, "territory 1", 1);
//    Deploy * deploy1 = new Deploy(11, *territory);
//    ordersListObj->addDeploy(deploy1);
//
//    string ryan = "Ryan";
//
//    auto *player1 = new Player(&ryan, generateTerritories(territoriesOwnedPerPlayer),
//                               generateHand(numCardsPerPlayer), ordersListObj);
//
//    deploy1->setPlayerLink(*player1);
//
//    player1->setReinforcements(12);
//
//    for (int i = 0; i < territoriesOwnedPerPlayer; i++) {
//        cout << player1->getTerritoriesOwned(i)->id << endl;
//    }
//
//    //player1->getOrder(0)->validate(player1);
//
//    player1->issueOrder();
//
//    delete ordersListObj;
//    delete territory;
//    delete deploy1;
//    delete player1;
}

/*
Reinforcement Phase: Players are given a number of armies that depends on the number of territories
they own, (# of territories owned divided by 3, rounded down). If the player owns all the territories of an
entire continent, the player is given a number of armies corresponding to the continent’s control bonus
value. In any case, the minimal number of reinforcement armies per turn for any player is 3. These armies
are placed in the player’s reinforcement pool. This must be implemented in a function/method named
reinforcementPhase() in the game engine.
 */
void GameEngine::reinforcementPhase(Player & player, Map & map) {

    //sets the number of armies based on territory size
    int numArmies = floor(player.getTerritorySize() / 3);
    player.setReinforcements(numArmies);

    //TODO this must be done right after the map loads and the players are chosen
    map.countTerritoriesPerContinent(); //TODO this should only be run once
    player.setTerritoriesOwnedPerContinent(map.numberOfTerritoriesPerContinent.size()); //TODO this should only be run once

    for (int i = 0; i < map.numberOfTerritoriesPerContinent.size(); ++i) {
        if (map.numberOfTerritoriesPerContinent.at(i) == player.getTerritoriesOwnedPerContinent().at(i)) {
            //give reward
            player.setReinforcements(player.getReinforcements() + map.continents.at(i)->territorialReward);
        }
    }

    Continent * playerOwnedContinentTemp; //temp continent
    bool continentOwned = false;
    //TODO make a variable in map.cpp to keep track if someone owns a continent

    //check to see if player owns all terri in a continent
    //TODO this is disgusting change it
    for (int i = 0; i < map.continents.size(); ++i) {



        for (int j = 0; j < player.getTerritorySize(); ++j) {
            Territory * currentTerritory = player.getTerritoriesOwned(j);
            int terriCounter = 0;
            for (int k = 0; k < map.continents.at(i)->territories.size(); ++k) {
                if (currentTerritory->id == map.continents.at(i)->territories.at(k)->id) {
                    terriCounter++;
                }
                if (terriCounter == map.continents.at(i)->territories.size()) {
                    //the player owns all the territories in this continent, do something
                    playerOwnedContinentTemp = new Continent(*map.continents.at(i)); //used just to get the terri reward
                    continentOwned = true;
                }
            }
            delete currentTerritory;
        }
    }

    //add armies to the players army pool based on the terri reward
    if(continentOwned) {
        player.setReinforcements(player.getReinforcements() + playerOwnedContinentTemp->territorialReward);
    }

    //delete pointer of the temp Continent after done
    delete playerOwnedContinentTemp;

}
/*
Issuing Orders Phase: Players issue orders and place them in their order list through a call to the
Player::issueOrder() method. This method is called in round-robin fashion across all players by the
game engine. This must be implemented in a function/method named issueOrdersPhase() in the game
engine
 */
//find which neighboring territories the player can attack
void GameEngine::issueOrdersPhase(Player &player) {
//TODO must call Player:issueOrder() func to add to the vector list
    player.issueOrder();

}


/*
Orders Execution Phase—Once all the players have signified in the same turn that they are not issuing
one more order, the game engine proceeds to execute the top order on the list of orders of each player in
a round-robin fashion (i.e. the “Order Execution Phase”—see below). Once all the players’ orders have
been executed, the main game loop goes back to the reinforcement phase. This must be implemented in
a function/method named executeOrdersPhase() in the game engine
 */
void GameEngine::executeOrdersPhase() {
//TODO destroy all the pointers


}
//end ryan