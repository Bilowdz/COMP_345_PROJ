//
// Created by Nicolo on 2021-09-24.
//
#include "GameEngine.h"
#include "CommandProcessing.h"
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

// constructor
GameEngine::GameEngine() : isGameDone(false), currentState(ST_START) {
    if(this->debug)
        cout << "GameEngine constructor called" << endl;
}

// copy constructors
GameEngine::GameEngine(const GameEngine &game) : isGameDone(false), currentState(game.currentState) {
    if(this->debug)
        cout << "GameEngine copy constructor called" << endl;
}

//Second copy constructor
GameEngine::GameEngine(GameEngine *const pGameEngine) : isGameDone(false), currentState(pGameEngine->currentState) {
    if(this->debug)
        cout << "GameEngine copy constructor 2 called" << endl;
}

// destructor
GameEngine::~GameEngine() = default;

// validate and execute transitions based on current state
bool GameEngine::transition(Command *c) {
    string command = c->getCommand();
    string loadmap = "loadmap";
    string addplayer = "addplayer";

    if (command.rfind(loadmap, 0) == 0) {
        // only transition from valid states
        if (currentState == ST_START || currentState == ST_MAP_LOADED) {

            // valid transition to state map loaded, so travel to state
            currentState = ST_MAP_LOADED;
            Notify(this);

            // execute game engine function
            this->loadmap(c);
            return true;
        }
    } else if (command == "validatemap") {
        if (currentState == ST_MAP_LOADED) {
            currentState = ST_MAP_VALIDATED;
            Notify(this);
            this->validatemap();
            return true;
        }
    } else if (command.rfind(addplayer, 0) == 0) {
        if (currentState == ST_MAP_VALIDATED || currentState == ST_PLAYERS_ADDED) {
            currentState = ST_PLAYERS_ADDED;
            Notify(this);
            this->addplayer(c);
            return true;
        }
    } else if (command == "assigncountries") {
        if (currentState == ST_PLAYERS_ADDED) {
            currentState = ST_ASSIGN_REINFORCEMENT;
            Notify(this);
            this->assigncountries();
            return true;
        }
    } else if (command == "issueorders") {
        if (currentState == ST_ASSIGN_REINFORCEMENT || currentState == ST_ISSUE_ORDERS) {
            currentState = ST_ISSUE_ORDERS;
            Notify(this);
            this->issueorder();
            return true;
        }
    } else if (command == "endissueorders") {
        if (currentState == ST_ISSUE_ORDERS) {
            currentState = ST_EXECUTE_ORDERS;
            Notify(this);
            this->endissueorders();
            return true;
        }
    } else if (command == "execorder") {
        if (currentState == ST_ISSUE_ORDERS || currentState == ST_EXECUTE_ORDERS) {
            currentState = ST_EXECUTE_ORDERS;
            Notify(this);
            this->execorder();
            return true;
        }
    } else if (command == "endexecorders") {
        if (currentState == ST_EXECUTE_ORDERS) {
            currentState = ST_ASSIGN_REINFORCEMENT;
            Notify(this);
            this->endexecorders();
            return true;
        }
    } else if (command == "win") {
        if (currentState == ST_EXECUTE_ORDERS) {
            currentState = ST_WIN;
            Notify(this);
            this->win();
            return true;
        }
    } else if (command == "replay") {
        if (currentState == ST_WIN) {
            currentState = ST_START;
            Notify(this);
            this->play();
            return true;
        }
    } else if (command == "quit") {
        if (currentState == ST_WIN) {
            currentState = ST_END;
            Notify(this);
            this->end();
            this->isGameDone = true;
            return true;
        }
    } else if (command =="gamestart") {
        if (currentState == ST_PLAYERS_ADDED) {
            gamestart();
            mainGameLoop();
            return true;
        }
    }
    return false;
}

// return enum value currentState
State GameEngine::getState() {
    return currentState;
}
/**
 *Loads the map depending on the command
 * @param c is the command that gets passed in
 */
void GameEngine::loadmap(Command *c) {

    string command = c->getCommand();
    string mapChosen;

    if (command == "loadmap zertina.map") {
        mapChosen = "../Maps/zertina.map";
    } else if (command == "loadmap bigeurope.map") {
        mapChosen = "../Maps/bigeurope.map";
    } else if (command == "loadmap canada.map") {
        mapChosen = "../Maps/canada.map";
    } else if (command == "loadmap minimap.map") {
        mapChosen = "../Maps/minimap.map";
        // invalid map
    } else {

    }

    MapLoader load;
    load.Load(mapChosen);
    gameMap = *load.maps.at(0);

}

/**
 * Runs the validate function that indicates if the map is valid
 */
void GameEngine::validatemap() {
    if (gameMap.Validate()) {
        cout << "Validating Map..." << endl;
        cout << "Map is valid!" << endl;
    }else {
        cout << "Validating Map..." << endl;
        cout << "Map is not valid!" << endl;
        exit(0);
    }
}

/**
 *Each player gets initialized and added with their vector of territories,
 * vector of hand and a orders list
 * @param c
 */
void GameEngine::addplayer(Command *c) {

    // get the name from command object
    string *name = new string((c->getCommand()).substr(10));
    vector<Territory*> vTerritories;
    Hand *vHand = new Hand();
    OrdersList *ordersList = new OrdersList();
    for(Observer* observer : *_observers)
        ordersList->Attach(observer);

    Player *newPlayer = new Player(name, vTerritories, vHand, ordersList);
    newPlayer->setDeckLink(MainDeck);
    newPlayer->setMapLink(gameMap);
    newPlayer->setTerritoriesOwnedPerContinent();
    newPlayer->addReinforcements(50);
    this->Players.push_back(newPlayer);

}

/**
 * Sets up the initial game startup for each player
 * Creates the link to the neutral player
 */
void GameEngine::gamestart() {
    gameMap.countTerritoriesPerContinent();
    Player::neutralPlayer().setDeckLink(MainDeck);
    Player::neutralPlayer().setMapLink(gameMap);
    Player::neutralPlayer().setTerritoriesOwnedPerContinent();
    std::shuffle(std::begin(Players), std::end(Players), std::default_random_engine());
    cout << "\nThe player order is: " << endl;
    for (int i = 0; i < Players.size(); i++) {
        cout << i + 1 << ": " << Players.at(i)->getName() << endl;
    }
    MainDeck = *new Deck(Players.size());
    for (auto &Player: Players) {
        MainDeck.Draw(Player->getHand());
        MainDeck.Draw(Player->getHand());
    }

    this->transition(new Command("assigncountries"));
}
/**
 * Assign the countries in the map randomly to each player
 */
void GameEngine::assigncountries() {
    for (int i = 0; i < gameMap.map.size(); i++) {
        int randomPlayer = i % Players.size();
        Players.at(randomPlayer)->addTerritory(gameMap.map.at(i));
        gameMap.map.at(i)->playerLink = Players.at(randomPlayer);
    }
}

//Calls the issueOrdersPhase function
void GameEngine::issueorder() {
    issueOrdersPhase();
}
//Calls the executeOrdersPhase function
void GameEngine::execorder() {
    executeOrdersPhase();
}
//Outputs to the terminal the end of execute orders fuction
void GameEngine::endexecorders() {
    cout << "Executing function endexecorders" << endl;
}
//Outputs the end of issue orders function
void GameEngine::endissueorders() {
    cout << "Executing function endissueorders" << endl;
}
//Outputs to the terminal the win execution will begin
void GameEngine::win() {

}
//Outputs to the terminal the end exeuction will begin
void GameEngine::end() {
    cout << "--- Good bye! ---" << endl;
}
//Outputs to the terminal the play execution will begin
void GameEngine::play() {
    cout << "Executing function play" << endl;
}

// assignment operator overload
GameEngine &GameEngine::operator=(const GameEngine &ge) {
    this->currentState = ge.currentState;

    return *this;
}

// stream insertion operator overloads
ostream &operator<<(ostream &out, const GameEngine &ge) {
    out << "Current State:" << enum_state_str[ge.currentState] << endl;
    return out;
}

/**
 * Initializes the game and creates the map
 * @param cp to get the command processor
 * @param ge to get a pointer to the game engine
 */
void GameEngine::startupPhase(CommandProcessor cp, GameEngine *ge) {
    while (true) {

        // get command
        Command *c = cp.getCommand(ge);
        string commandName = c->getCommand();
        string effect = c->getEffect();

        // process commands that have no errors
        if(effect.length() == 0) {

            // stop startup phase once game started
            if (commandName == "gamestart") {
                gamestart();
                mainGameLoop();
                break;
            } else {
                transition(c);
            }
        } else {

            // output the error message
            cout << "ERROR: " << effect << endl;
        }
    }
}

/**
 * Includes the three phases and loops until there is one winner
 */
void GameEngine::mainGameLoop() {

    bool noWinner = false;
    int numTurns = 0;
    while (!noWinner) {
        //Call to reinforcement phase
        reinforcementPhase();

        this->transition(new Command("issueorders"));
        this->transition(new Command("endissueorders"));
        this->transition(new Command("endissueorders"));
        this->transition(new Command("execorder"));

        //Check to see if players owns a territory, if they dont remove them from game
        for (int i = 0; i < Players.size(); i++) {
            if (Players.at(i)->getTerritorySize() == 0) {
                //delete this player from the vector
                //delete Players.at(Players.begin() + i);
                Players.erase(Players.begin() + i);
            }
        }

        //Check to see if final player owns all territories on the map
        if (Players.size() == 1) {
            int doneCounter = 0;
            for (int i = 0; i < gameMap.numberOfTerritoriesPerContinent.size(); i++) {
                if (Players.at(0)->getTerritoriesOwnedPerContinent().at(i) == gameMap.numberOfTerritoriesPerContinent.at(i)) {
                    doneCounter++;
                }
            }
            if (doneCounter == gameMap.continents.size()) {
                //if there are neutral territories then he might not win
                noWinner = true;
                cout << "---- ---- ---- The winner is " << Players.at(0)->getName() << "!! ---- ---- ----";
                gameResults.push_back(Players.at(0)->getName());
                this->transition(new Command("win"));
                return;
            } else {
                //requests last player if they want to end the game
                int ending;
                cout << "Do you want to end the game? (1 for yes, 0 for no)" << endl;
                cin >> ending;
                if (ending == 1) {
                    noWinner = true;
                    cout << "---- ---- ---- The winner is " << Players.at(0)->getName() << "!! ---- ---- ----";
                    gameResults.push_back(Players.at(0)->getName());
                    this->transition(new Command("win"));
                    return;
                }
            }
        }

        numTurns++;
        if(numTurns==maxTurns)
        {
            noWinner = true;
            cout << "---- ---- ---- The game Ends in a Draw";
            gameResults.push_back("Draw");
            this->transition(new Command("win"));
            return;
        }
        this->transition(new Command("endexecorders"));
    }


}



/**
 * Armies are given out depending on territories owned
 * If player owns a continent then they get extra reinforcements
 */
void GameEngine::reinforcementPhase() {
    this->currentState = ST_ASSIGN_REINFORCEMENT;
    //Adds armies to the reinforcement pool
    for (int i = 0; i < Players.size(); i++) {
        //sets the number of armies based on territory size
        int numArmies = floor(Players.at(i)->getTerritorySize() / 3);
        Players.at(i)->addReinforcements(numArmies);

        for (int j = 0; j < gameMap.numberOfTerritoriesPerContinent.size()-1; j++) {
            if (gameMap.numberOfTerritoriesPerContinent.at(j) == Players.at(i)->getTerritoriesOwnedPerContinent().at(j)) {
                //give reward
                Players.at(i)->setReinforcements(Players.at(i)->getReinforcements() +
                                                    gameMap.continents.at(j)->territorialReward);
            }
        }
    }
}

/**
 * Loop through all the players and allow them to issue orders from the Player.cpp issueOrders fucntion
 */
void GameEngine::issueOrdersPhase() {
    //loop through each player and allow them to issue orders
    for (int i = 0; i < Players.size(); i++) {
        cout << endl << Players.at(i)->getName() << "\'s turn to issue orders:\n\n";
        Players.at(i)->issueOrder(Players);
    }
}

/**
 * Once all the orders have been issued from each player, they get validated. If they are
 * valid then they get executed.
 */
void GameEngine::executeOrdersPhase() {
    //TODO destroy all the pointers
    //Order of execution is which order was passed into the orderslist first
    cout << "\nExecuting orders:" << endl;
    for (int i = 0; i < Players.size(); i++) {
        cout << Players.at(i)->getName() << "\'s orders:" << endl;
        int numberOfOrders = Players.at(i)->getOrdersList()->getList().size();
        for (int j = 0; j < numberOfOrders; j++) {
            //validates the order and executes the order if it is good.
            Players.at(i)->getOrdersList()->getList().at(0)->validate(*Players.at(i));
            Players.at(i)->getOrdersList()->remove(0);
        }
    }
    for (int i = 0; i < Players.size(); i++) {
        int sizeOfNegotiating = Players.at(i)->negotiatingWith.size();
        for (int j = 0; j < sizeOfNegotiating; j++) {
            Players.at(i)->removeNegotiations(0);
        }
    }
}

void GameEngine::printAvailableOptions() {
    cout << endl;
    cout << "Available options:" << endl;
    if(this->getState() == ST_START){
        cout << "loadmap <mapfile>" << endl;
    } else if(this->getState() == ST_MAP_LOADED){
        cout << "loadmap <mapfile>" << endl;
        cout << "validatemap" << endl;
    } else if(this->getState() == ST_MAP_VALIDATED){
        cout << "addplayer <playername>" << endl;
    } else if(this->getState() == ST_PLAYERS_ADDED){
        cout << "addplayer <playername>" << endl;
        cout << "gamestart" << endl;
    } else if(this->getState() == ST_WIN) {
        cout << "replay" << endl;
        cout << "quit" << endl;
    }
}

/**
 * Creates a string with the current game state
 * @return the game state
 */
string GameEngine::stringToLog(){
    string state = enum_state_str[currentState];
    string log = "Log :: New Game State : " + state;
    return log;
}


bool GameEngine::validateTournamentPhase(string toValidate) {
    std:: regex reg ("(T|t)ournament -M(\\s[\\w]+\\.map,)*(\\s[\\w]+\\.map\\s)-P\\s((Aggressive,\\s)|(Benevolent,\\s)|(Neutral,\\s)|(Cheater,\\s))+((Aggressive\\s)|(Benevolent\\s)|(Neutral\\s)|(Cheater\\s))-G(\\s\\d+\\s)-D(\\s\\d+)");
    if(!std::regex_match(toValidate, reg))
    {
        cout << "Invalid tournament..." << endl;
        return false;
    }
    else
    {
        return true;
    }
}

void GameEngine::PrintResults()
{
    vector<string> resultsVector;
    string result;
    resultsVector.push_back("\t");

    for(int i = 0; i < numGames; i++)
    {
        resultsVector.at(0).append("Game " + to_string((i+1)) + "\t");
    }

    resultsVector.at(0).append("\n");

    int resultPos = 0;
    for(int i = 0; i < tourneyMaps.size(); i++)
    {
        resultsVector.push_back("Map " + to_string((i+1)) + "\t");

        for(int j = 0; j < numGames; j++)
        {
            resultsVector.at(i+1).append(gameResults.at(resultPos) + "\t");
            resultPos++;
        }
    }

    for(auto & i : resultsVector)
    {
        result.append(i + "\n");
    }
    cout << result;
}