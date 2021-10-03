//
// Created by Sean on 2021-09-24.
//

#ifndef COMP_345_PROJ_MAP_H
#define COMP_345_PROJ_MAP_H

#include <iostream>
#include <fstream>
#include <vector>

class Territory{
public:
    Territory(int id, std::string name);
    int id;
    std::string name;
    int unitsGarrisoned;
    // Owner
    std::vector<Territory> adjacentTerritories;
};

class Continent{
public:
    Continent(std::string name, int territorialReward);
    std::string name;
    int territorialReward;
    // Owner
    std::vector<Territory> territories;
    // Color
};

class Map {
public:
    std::vector<Continent> map;
    void Validate();
};

class MapLoader{
public:
    Map* Load(std::string fileName);
};


#endif //COMP_345_PROJ_MAP_H
