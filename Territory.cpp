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

Territory::~Territory() = default;


void Territory::setNumTerritories(int *numOfTerritories) {
    this->numOfTerritories = *numOfTerritories;
}

int Territory::getNumTerritories() const {
    return numOfTerritories;
}

void Territory::identify() {
    std::cout << "This is a territory" << std::endl;
}

std::string Territory::getName() const {
    return name;
}

int Territory::getId() const {
    return id;
}

void Territory::setSize(int territorySize) {
    this->size = territorySize;
}

int Territory::getSize() const {
    return size;
}
