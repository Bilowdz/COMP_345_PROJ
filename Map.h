//
// Created by Sean on 2021-09-24.
//

#ifndef COMP_345_PROJ_MAP_H
#define COMP_345_PROJ_MAP_H

#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>

class Territory{
public:
    // what I added
    int armies;
    int getArmies();
    void setArmies(int armies);
    void addArmies(int armiesToAdd);
    // ends here
    int id;
    std::string name;
    int continent;
    int unitsGarrisoned;
    bool visited;
    std::vector<Territory*> adjacentTerritories;

    bool IsAdjacent(Territory &adj);

    Territory& operator =(const Territory &);
    friend std::ostream & operator << (std::ostream &out, const Territory &territory);
    friend std::istream & operator >> (std::istream &in,  Territory &territory);

    Territory(int id, std::string name, int continent);
    Territory(const Territory &t1);
    Territory();// added this
    ~Territory();
};

class Continent{
public:
    std::string name;
    int territorialReward;
    std::vector<Territory*> territories;

    Continent& operator =(const Continent &);
    friend std::ostream & operator << (std::ostream &out, const Continent &continent);
    friend std::istream & operator >> (std::istream &in,  Continent &continent);

    Continent(std::string name, int territorialReward);
    Continent(const Continent &c1);
    ~Continent();
};

class Map {
public:
    std::vector<Continent*> continents;
    std::vector<Territory*> map;

    Map& operator =(const Map &);
    friend std::ostream & operator << (std::ostream &out, const Map &map);

    bool Validate();

    Map();
    Map(const Map &m1);
    ~Map();
private:
    void MarkContinent(Territory* cur, int continent);
    void MarkMap(Territory* cur);
    bool ClearAndCheckMap();
    bool ClearAndCheckContinent(Continent* continent);
};

class MapLoader{
public:
    std::vector<Map*> maps;

    friend std::ostream & operator << (std::ostream &out, const MapLoader &mapLoader);

    MapLoader& operator =(const MapLoader &);
    void Load(const std::string& fileName);

    MapLoader();
    MapLoader(const MapLoader &ml1);
    ~MapLoader();
};


#endif //COMP_345_PROJ_MAP_H
