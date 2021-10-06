//
// Created by Sean on 2021-09-24.
//

#include "Map.h"

void Map::Validate() {

}

Map* MapLoader::Load(std::string fileName) {
    Map *map (new Map);

    //Open map file
    std::ifstream input(fileName);

    //Variables used in the reading of the file
    char str[256];
    std::string name; int reward; std::string color;
    int id, continent, miscData1, miscData2;

    // Skip to continents header
    while(strcmp(str, "[continents]") && !input.eof()) {
        input.getline(str, 255);
    }

    // Read continents
    //      Checks if the first element is the start of countries before proceeding,
    //      Creates a new continent and adds it to the map
    std::cout << "\nReading Continents" << std::endl;
    input >> name;
    while(name != "[countries]" && !input.eof()) {
        input >> reward >> color;
        std::cout << "Continent: " << name << ", With Reward: " << reward << std::endl;
        Continent *continent(new Continent(name, reward));
        map->continents.push_back(continent);
        input >> name;
    }

    // Read countries
    //      Checks if the first element is the start of borders before proceeding,
    //      Creates a new country and adds it to the temporary vector and its continent
    std::cout << "\nReading Territories" << std::endl;
    input >> str;
    while(strcmp(str, "[borders]") && !input.eof()) {
        sscanf(str, "%d", &id);
        input >> name >> continent >> miscData1 >> miscData2;
        std::cout << "Territory: " << name << ", In Continent: " << continent << std::endl;
        Territory *territory(new Territory(id, name, continent));
        auto curContinent = map->continents.at(continent-1);
        curContinent->territories.push_back(territory);
        map->map.push_back(territory);
        input >> str;
    }

    // Read adjacency's
    //      Checks for the end of file before proceeding,
    //      Gets and splits the next line on space
    //      Saves the first element as the territory to edit
    //      Loops through the other elements adding them to the adjacency
    std::cout << "\nReading Adjacency's" << std::endl;
    while(!input.eof()) {
        input.getline(str, 255);
        char *token = strtok(str, " ");
        if(token){
            sscanf(token, "%d", &id);
            std::cout << "Territory: " << id << " is adjacent to: ";
            Territory* cur = map->map[id-1];
            token = strtok(NULL, " ");
            while(token){
                sscanf(token, "%d", &id);
                std::cout << "T#" << id << " ";
                cur->adjacentTerritories.push_back(map->map[id-1]);
                token = strtok(NULL, " ");
            }
            std::cout << std::endl;
        }
    }

    input.close();

    return map;
}

Continent::Continent(std::string name, int territorialReward) {
    this->name = name;
    this->territorialReward = territorialReward;
}

std::istream &operator>>(std::istream &in, Continent &continent) {
    in >> continent.name;
    in >> continent.territorialReward;

    std::string color;

    in >> color;

    return in;
}

std::ostream &operator<<(std::ostream &out, const Continent &continent) {
    out << "{ Name: " << continent.name << ", Reward: " << continent.territorialReward << " }" << std::endl;

    return out;
}

Territory::Territory(int id, std::string name, int continent) {
    this->id = id;
    this->name = name;
    this->unitsGarrisoned = 0;
}

std::istream &operator>>(std::istream &in, Territory &territory) {
    in >> territory.id;
    in >> territory.name;
    in >> territory.continent;

    int miscData1, miscData2;

    in >> miscData1 >> miscData2;

    return in;
}

std::ostream &operator<<(std::ostream &out, const Territory &territory) {
    out << "{ Id: " << territory.id << ", Name: " << territory.name;
    out << ", Continent: " << territory.continent << " }" << std::endl;

    return out;
}
