//
// Created by Nicolo pt 2 on 2021-09-24.
//
#include <iostream>
#include "GameEngine.h"
using namespace std;

GameEngine::GameEngine() {
    currentState = ST_START;
}

GameEngine::GameEngine(State s) {
    currentState = s;
}


void GameEngine::loadmap() {
    cout << "executing function loadmap" << endl;
}

void GameEngine::validatemap() {
    cout << "executing function validatemap" << endl;
}

void GameEngine::addplayer() {
    cout << "executing function addplayer" << endl;
}

void GameEngine::assigncountries() {
    cout << "executing function assigncountries" << endl;
}

void GameEngine::issueorder() {
    cout << "executing function issueorder" << endl;
}

void GameEngine::execorder() {
    cout << "executing function execorder" << endl;
}

void GameEngine::endexecorders() {
    cout << "executing function endexecorders" << endl;
}

void GameEngine::endissueorders() {
    cout << "executing function endissueorders" << endl;
}

void GameEngine::win() {
    cout << "executing function win" << endl;
}

void GameEngine::end() {
    cout << "executing function end" << endl;
}

void GameEngine::play() {
    cout << "executing function play" << endl;
}
