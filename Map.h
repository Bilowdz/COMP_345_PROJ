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
    Territory(int id, std::string name, int continent);
    friend std::ostream & operator << (std::ostream &out, const Territory &territory);
    friend std::istream & operator >> (std::istream &in,  Territory &territory);
    int id;
    std::string name;
    int continent;
    int unitsGarrisoned;
    // Owner
    std::vector<Territory*> adjacentTerritories;
};

class Continent{
public:
    Continent(std::string name, int territorialReward);
    friend std::ostream & operator << (std::ostream &out, const Continent &continent);
    friend std::istream & operator >> (std::istream &in,  Continent &continent);
    std::string name;
    int territorialReward;
    // Owner
    std::vector<Territory*> territories;
    // Color
};

class Map {
public:
    std::vector<Continent*> continents;
    std::vector<Territory*> map;

    void Validate();
    void Print();
};

class MapLoader{
public:
    Map* Load(std::string fileName, bool debug);
};


#endif //COMP_345_PROJ_MAP_H
