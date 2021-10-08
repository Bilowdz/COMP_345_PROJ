//
// Created by Sean on 2021-09-24.
//

#include "Map.h"

bool Map::Validate() {
    if(map.empty())
        return false;

    MarkMap(map.front());
    ClearAndCheckMap();

    int continentNum = 1;
    for(Continent *cont : continents){
        if(cont->territories.empty())
            return false;
        MarkContinent(cont->territories.front(), continentNum);
        ClearAndCheckContinent(cont);

        continentNum++;
    }

    // Check Last Clause

    return true;
}

void Map::Print() {
    std::cout << "Territories" << std::endl;
    for(Territory* t : map){
        std::cout << *t;
    }

    std::cout << "Continents" << std::endl;
    for(Continent* c : continents){
        std::cout << *c;
    }
}

bool Map::ClearAndCheckMap(){
    for(Territory *territory : map){
        if(territory->visited)
            territory->visited = false;
        else
            return false;
    }

    return  true;
}

bool Map::ClearAndCheckContinent(Continent *continent){
    for(Territory *territory : continent->territories){
        if(territory->visited)
            territory->visited = false;
        else
            return false;
    }

    return  true;
}

void Map::MarkContinent(Territory *cur, int continent) {
    for(Territory* adj : cur->adjacentTerritories){
        if(adj->continent == continent && !adj->visited){
            adj->visited = true;
            MarkContinent(adj, continent);
        }
    }
}

void Map::MarkMap(Territory *cur) {
    for(Territory* adj : cur->adjacentTerritories){
        if(!adj->visited){
            adj->visited = true;
            MarkMap(adj);
        }
    }
}

Map* MapLoader::Load(std::string fileName, bool debug) {
    Map *map (new Map);

    //Open map file
    std::ifstream input(fileName);

    std::streampos saveState;

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
    if(debug)
        std::cout << "\nReading Continents" << std::endl;

    saveState = input.tellg();
    input >> str;
    while(strcmp(str, "[countries]") && !input.eof()) {
        input.seekg(saveState);

        //Create continent object and populate from stream
        Continent *continent(new Continent("tmp", 0));
        input >> *continent;

        if(debug)
            std::cout << "Continent: " << continent->name << ", With Reward: " << continent->territorialReward << std::endl;

        map->continents.push_back(continent);

        saveState = input.tellg();
        input >> str;
    }

    // Read countries
    //      Checks if the first element is the start of borders before proceeding,
    //      Creates a new country and adds it to the temporary vector and its continent
    if(debug)
        std::cout << "\nReading Territories" << std::endl;

    saveState = input.tellg();
    input >> str;
    while(strcmp(str, "[borders]") && !input.eof()) {
        input.seekg(saveState);

        Territory *territory(new Territory(0, "tmp", 0));
        input >> *territory;

        if(debug)
            std::cout << "Territory: " << territory->name << ", In Continent: " << territory->continent << std::endl;

        auto curContinent = map->continents.at(territory->continent-1);
        curContinent->territories.push_back(territory);
        map->map.push_back(territory);

        saveState = input.tellg();
        input >> str;
    }

    // Read adjacency's
    //      Checks for the end of file before proceeding,
    //      Gets and splits the next line on space
    //      Saves the first element as the territory to edit
    //      Loops through the other elements adding them to the adjacency
    if(debug)
        std::cout << "\nReading Adjacency's" << std::endl;

    while(!input.eof()) {
        input.getline(str, 255);
        char *token = strtok(str, " ");

        if(token){
            sscanf(token, "%d", &id);

            if(debug)
                std::cout << "Territory: " << id << " is adjacent to: ";

            Territory* cur = map->map[id-1];
            token = strtok(NULL, " ");

            while(token){
                sscanf(token, "%d", &id);

                if(debug)
                    std::cout << "T#" << id << " ";

                cur->adjacentTerritories.push_back(map->map[id-1]);
                token = strtok(NULL, " ");
            }

            if(debug)
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
    this->continent = continent;
    this->unitsGarrisoned = 0;
    this->visited = false;
}

std::istream &operator>>(std::istream &in, Territory &territory) {
    in >> territory.id;
    in >> territory.name;
    in >> territory.continent;
    territory.visited = false;

    int miscData1, miscData2;
    in >> miscData1 >> miscData2;

    return in;
}

std::ostream &operator<<(std::ostream &out, const Territory &territory) {
    out << "{ Id: " << territory.id << ", Name: " << territory.name;
    out << ", Continent: " << territory.continent << " }" << std::endl;

    return out;
}
