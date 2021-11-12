//
// Created by Nicolo on 2021-09-24.
//
#include <iostream>
#include "GameEngine.h"
using namespace std;

// constructor
GameEngine::GameEngine(): isGameDone(false), currentState(ST_START) {}

// copy constructors
GameEngine::GameEngine(const GameEngine &game): isGameDone(false), currentState(game.currentState) {}

GameEngine::GameEngine(GameEngine *const pGameEngine): isGameDone(false), currentState(pGameEngine->currentState) {}

// destructor
GameEngine:: ~GameEngine() = default;

// validate and execute transitions based on current state
bool GameEngine::transition(Transition t) {
    switch(t) {
        case T_LOAD_MAP:

            // only transition from valid states
            if(currentState == ST_START || currentState == ST_MAP_LOADED) {

                    // valid transition to state map loaded, so travel to state
                    currentState = ST_MAP_LOADED;

                // execute game engine function
                this->loadmap();
                return true;
            }

            break;
        case T_VALIDATE_MAP:
            if(currentState == ST_MAP_LOADED) {
                currentState = ST_MAP_VALIDATED;
                this->validatemap();
                return true;
            }

            break;

        case T_ADD_PLAYER:
            if(currentState == ST_MAP_VALIDATED || currentState == ST_PLAYERS_ADDED) {
                currentState = ST_PLAYERS_ADDED;
                this->addplayer();
                return true;
            }
            break;
        case T_ASSIGN_COUNTRIES:
            if(currentState == ST_PLAYERS_ADDED) {
                currentState = ST_ASSIGN_REINFORCEMENT;
                this->assigncountries();
                return true;
            }
            break;
        case T_ISSUE_ORDER:
            if(currentState == ST_ASSIGN_REINFORCEMENT || currentState == ST_ISSUE_ORDERS) {
                currentState = ST_ISSUE_ORDERS;
                this->issueorder();
                return true;
            }
            break;
        case T_END_ISSUE_ORDERS:
            if(currentState == ST_ISSUE_ORDERS) {
                currentState = ST_EXECUTE_ORDERS;
                this->endissueorders();
                return true;
            }
            break;
        case T_EXEC_ORDER:
            if(currentState == ST_ISSUE_ORDERS || currentState == ST_EXECUTE_ORDERS) {
                currentState = ST_EXECUTE_ORDERS;
                this->execorder();
                return true;
            }
            break;
        case T_END_EXEC_ORDERS:
            if(currentState == ST_EXECUTE_ORDERS) {
                currentState = ST_ASSIGN_REINFORCEMENT;
                this->endexecorders();
                return true;
            }
            break;
        case T_WIN:
            if(currentState == ST_EXECUTE_ORDERS) {
                currentState = ST_WIN;
                this->win();
                return true;
            }
            break;
        case T_PLAY:
            if(currentState == ST_WIN) {
                currentState = ST_START;
                this->play();
                return true;
            }
            break;
        case T_END:
            if(currentState == ST_WIN) {
                currentState = ST_END;
                this->end();
                this->isGameDone = true;
                return true;
            }
            break;
        default:
            try {
                throw T_ERROR;
            } catch (Transition t) {
                cout << " An error has occurred. Exception: '" << t << "'" << endl;
            }
    }
    return false;
}

// return string equivalent of enum value currentState
string GameEngine::getState() {
    switch(currentState) {
        case ST_START:
            return "start";
        case ST_MAP_LOADED:
            return "maploaded";
        case ST_MAP_VALIDATED:
            return "mapvalidated";
        case ST_PLAYERS_ADDED:
            return "playersadded";
        case ST_ASSIGN_REINFORCEMENT:
            return "assignreinforcement";
        case ST_ISSUE_ORDERS:
            return "issueorders";
        case ST_EXECUTE_ORDERS:
            return "executeorders";
        case ST_WIN:
            return "win";
        case ST_END:
            return "end";
        default:
            return "error";
    }
}

void GameEngine::loadmap() {
    cout << "Executing function loadmap" << endl;
}

void GameEngine::validatemap() {
    cout << "Executing function validatemap" << endl;
}

void GameEngine::addplayer() {
    cout << "Executing function addplayer" << endl;
}

void GameEngine::assigncountries() {
    cout << "Executing function assigncountries" << endl;
}

void GameEngine::issueorder() {
    cout << "Executing function issueorder" << endl;
}

void GameEngine::execorder() {
    cout << "Executing function execorder" << endl;
}

void GameEngine::endexecorders() {
    cout << "Executing function endexecorders" << endl;
}

void GameEngine::endissueorders() {
    cout << "Executing function endissueorders" << endl;
}

void GameEngine::win() {
    cout << "Executing function win" << endl;
}

void GameEngine::end() {
    cout << "Executing function end" << endl;
}

void GameEngine::play() {
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
    switch(ge.currentState) {

        case ST_START:
            out << "Current State: start" << endl;
            break;
        case ST_MAP_LOADED:
            out << "Current State: maploaded" << endl;
            break;
        case ST_MAP_VALIDATED:
            out << "Current State: mapvalidated" << endl;
            break;
        case ST_PLAYERS_ADDED:
            out << "Current State: playersadded" << endl;
            break;
        case ST_ASSIGN_REINFORCEMENT:
            out << "Current State: assignreinforcement" << endl;
            break;
        case ST_ISSUE_ORDERS:
            out << "Current State: issueorders" << endl;
            break;
        case ST_EXECUTE_ORDERS:
            out << "Current State: executeorders" << endl;
            break;
        case ST_WIN:
            out << "Current State: win" << endl;
            break;
        case ST_END:
            out << "Current State: end" << endl;
            break;
        default:
            try {
                throw ST_ERROR;
            } catch (State s) {
                cout << " An error has occurred. Exception: '" << s << "'" << endl;
            }            break;
    }
    return out;
}

//added by ryan
//TODO implement this shit
//TODO mainGameLoop loops the reinforcment, issueorder and executeorder phases
//TODO continues until one player owns all territories
//TODO must also remove players that do not own any territories

//reinforcement phase: number of territories they own, (# of territories owned divided by 3, rounded down)
void GameEngine::mainGameLoop() {


}

/*
Reinforcement Phase: Players are given a number of armies that depends on the number of territories
they own, (# of territories owned divided by 3, rounded down). If the player owns all the territories of an
entire continent, the player is given a number of armies corresponding to the continent’s control bonus
value. In any case, the minimal number of reinforcement armies per turn for any player is 3. These armies
are placed in the player’s reinforcement pool. This must be implemented in a function/method named
reinforcementPhase() in the game engine.
 */
void GameEngine::reinforcementPhase() {



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

}


/*
Orders Execution Phase—Once all the players have signified in the same turn that they are not issuing
one more order, the game engine proceeds to execute the top order on the list of orders of each player in
a round-robin fashion (i.e. the “Order Execution Phase”—see below). Once all the players’ orders have
been executed, the main game loop goes back to the reinforcement phase. This must be implemented in
a function/method named executeOrdersPhase() in the game engine
 */
void GameEngine::executeOrdersPhase() {


}
//end ryan