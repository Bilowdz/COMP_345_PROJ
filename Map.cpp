//
// Created by Sean on 2021-09-24.
//

#include "Map.h"

void Map::Validate() {

}

Map* MapLoader::Load(std::string fileName) {
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
    input >> name;
    while(name != "[countries]" && !input.eof()) {
        input >> reward >> color;
        std::cout << "Continent: " << name << ", With Reward: " << reward << std::endl;
        Continent *continent(new Continent(name, reward));
        map->map.push_back(*continent);
        input >> name;
    }

    // Read countries
    input >> str;
    while(strcmp(str, "[borders]") && !input.eof()) {
        sscanf(str, "%d", &id);
        input >> name >> continent >> miscData1 >> miscData2;
        std::cout << "Territory: " << name << ", In Continent: " << continent << std::endl;
        Territory *territory(new Territory(id, name));
        map->map[continent-1].territories.push_back(*territory);
        map->territories.push_back(*territory);
        input >> str;
    }

    // TODO: FIX THIS
    // Read adjacency's
    while(!input.eof()) {
        input.getline(str, 255);
        char *currentTerritory = strtok(str, " ");
        if(currentTerritory){
            sscanf(currentTerritory, "%d", &id);
            std::cout << "Territory: " << id << std::endl;
            Territory cur = map->territories[id];
            char *adjacentTerritory = strtok(NULL, " ");
            while(adjacentTerritory){
                sscanf(currentTerritory, "%d", &id);
                cur.adjacentTerritories.push_back(map->territories[id]);
                char *adjacentTerritory = strtok(NULL, " ");
            }
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
