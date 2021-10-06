//
// Created by Ryan on 2021-09-25.
//

#include <iostream>
#include "Territory.h"

Territory::Territory() {
    std::cout << "I own these territories" << std::endl;
}

Territory::Territory(int id, std::string name) {
    this->id = id;
    this->name = name;
    this->unitsGarrisoned = 0;
}


Territory::Territory(int *numOfTerritories) {
    this->numOfTerritories = *numOfTerritories;
}

void Territory::setNumTerritories(int *numOfTerritories) {
    this->numOfTerritories = *numOfTerritories;
}

int& Territory::getNumTerritories() {
    return numOfTerritories;
}

void Territory::identify() {
    std::cout << "This is a territory" << std::endl;
}
