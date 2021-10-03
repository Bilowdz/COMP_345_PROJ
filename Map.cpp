//
// Created by Sean on 2021-09-24.
//

#include "Map.h"

void Map::Validate() {

}

Map* MapLoader::Load(std::string fileName) {
    std::vector<Territory*> territories;
    Map *map (new Map);

    std::ifstream input(fileName);
    char str[256];

    std::string name; int reward; std::string color;
    int id, continent, miscData1, miscData2;

    // Skip to continents header
    while(strcmp(str, "[continents]") && !input.eof()) {
        // std::cout << "Skipped Line: " << str << std::endl;
        input.getline(str, 255);
    }

    // Read continents
    std::cout << "\nReading Continents" << std::endl;

    input >> name;
    while(name != "[countries]" && !input.eof()) {
        input >> reward >> color;
        std::cout << "Continent: " << name << ", With Reward: " << reward << std::endl;
        Continent *continent(new Continent(name, reward));
        map->map.push_back(*continent);
        input >> name;
    }

    // Read countries
    std::cout << "\nReading Territories" << std::endl;

    input >> str;
    while(strcmp(str, "[borders]") && !input.eof()) {
        sscanf(str, "%d", &id);
        input >> name >> continent >> miscData1 >> miscData2;
        std::cout << "Territory: " << name << ", In Continent: " << continent << std::endl;
        Territory *territory(new Territory(id, name));
        map->map[continent-1].territories.push_back(*territory);
        territories.push_back(territory);
        input >> str;
    }

    // Read adjacency's
    std::cout << "\nReading Adjacency's" << std::endl;

    while(!input.eof()) {
        input.getline(str, 255);
        char *token = strtok(str, " ");
        if(token){
            sscanf(token, "%d", &id);
            std::cout << "Territory: " << id << " is adjacent to: ";
            Territory* cur = territories[id-1];
            token = strtok(NULL, " ");
            while(token){
                sscanf(token, "%d", &id);
                std::cout << "territory #" << id << " ";
                cur->adjacentTerritories.push_back(*territories[id-1]);
                token = strtok(NULL, " ");
            }
            std::cout << std::endl;
        }
    }

    return map;
}

Continent::Continent(std::string name, int territorialReward) {
    this->name = name;
    this->territorialReward = territorialReward;
}

Territory::Territory(int id, std::string name) {
    this->id = id;
    this->name = name;
    this->unitsGarrisoned = 0;
}
