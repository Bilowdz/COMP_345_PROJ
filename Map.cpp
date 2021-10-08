//
// Created by Sean on 2021-09-24.
//

#include "Map.h"

// Validates the map is correctly structured
bool Map::Validate() {
    // If the map has no nodes then it is not a map
    if(map.empty())
        return false;

    // Mark all adjacency's in the map
    MarkMap(map.front());

    // Check and reset that all nodes are visited
    if(!ClearAndCheckMap())
        return false;

    //Check that each continent is a subgraph
    int continentNum = 1;
    for(Continent *cont : continents){
        // Check that each continent has a territory
        if(cont->territories.empty())
            return false;

        // Mark all adjacency's within the continent
        MarkContinent(cont->territories.front(), continentNum);

        // Check and reset that all nodes are visited
        if(!ClearAndCheckContinent(cont))
            return false;

        continentNum++;
    }

    // Check Last Clause

    return true;
}

// Prints the maps contents in a visual way
void Map::FancyPrint() {
    for(Continent* c : continents){
        std::cout << "Continent: "<< *c;
        for(Territory* t : c->territories){
            std::cout << *t;
        }
        std::cout << std::endl;
    }
}

// Makes sure that all nodes are marked checked
// if they are returns true, if not return false
// resets the status of all nodes
bool Map::ClearAndCheckMap(){
    for(Territory *territory : map){
        if(territory->visited)
            territory->visited = false;
        else
            return false;
    }

    return  true;
}

// Makes sure that all nodes in continent are marked checked
// if they are returns true, if not return false
// resets the status of all nodes
bool Map::ClearAndCheckContinent(Continent *continent){
    for(Territory *territory : continent->territories){
        if(territory->visited)
            territory->visited = false;
        else
            return false;
    }

    return  true;
}

// Recursively follows adjacency's marking checked
// Ignores territories with mismatching continents
// Ignores checked territories
void Map::MarkContinent(Territory *cur, int continent) {
    for(Territory* adj : cur->adjacentTerritories){
        if(adj->continent == continent && !adj->visited){
            adj->visited = true;
            MarkContinent(adj, continent);
        }
    }
}

// Recursively follows adjacency's marking checked
// Ignores checked territories
void Map::MarkMap(Territory *cur) {
    for(Territory* adj : cur->adjacentTerritories){
        if(!adj->visited){
            adj->visited = true;
            MarkMap(adj);
        }
    }
}

// Destructor for the map class
Map::~Map() = default;

// Default constructor for the mapLoader
// Loads all maps in the maps directory
MapLoader::MapLoader() {
    using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;

    std::filesystem::current_path("..");
    for (const auto& dirEntry : recursive_directory_iterator("Maps")){
        Load(dirEntry.path().string());
    }
}

// Loads a map file into an instance of the map class
// Saves the map into the mapLoader if the map is valid
void MapLoader::Load(const std::string& fileName) {
    // Start map object to populate
    Map *map (new Map);

    //Open map file
    std::ifstream input(fileName);

    //Variables used in the reading of the file
    std::streampos saveState;
    char str[256];
    int id;

    // Skip to continents header
    while(strcmp(str, "[continents]") != 0 && !input.eof()) {
        input.getline(str, 255);
    }

    // Save current state of read
    saveState = input.tellg();

    // Read next flow
    input >> str;

    // While not the start of countries or end of file read continent
    while(strcmp(str, "[countries]") != 0 && !input.eof()) {

        // Return to previous state (to be able to read the continent in full)
        input.seekg(saveState);

        // Create continent object and populate from stream
        auto *continent(new Continent("tmp", 0));
        input >> *continent;

        // Add to the map's continents
        map->continents.push_back(continent);

        // Save current state of read
        saveState = input.tellg();

        // Read next flow
        input >> str;
    }

    // Save current state of read
    saveState = input.tellg();

    // Read next flow
    input >> str;

    // While not the start of adjacency's or end of file read territories
    while(strcmp(str, "[borders]") && !input.eof()) {

        // Return to previous state (to be able to read the territory in full)
        input.seekg(saveState);

        // Create territory object and populate from stream
        auto *territory(new Territory(0, "tmp", 0));
        input >> *territory;

        // Add territory to its continent
        auto curContinent = map->continents.at(territory->continent-1);
        curContinent->territories.push_back(territory);

        // Add territory to the map
        map->map.push_back(territory);

        // Save current state of read
        saveState = input.tellg();

        // Read next flow
        input >> str;
    }

    // While not end of file read adjacency's
    while(!input.eof()) {

        // Get the first territory in the line and its pointer
        // (This is the one to add adjacency's to)
        input.getline(str, 255);
        char *token = strtok(str, " ");
        if(token){
            sscanf(token, "%d", &id);
            Territory* cur = map->map[id-1];

            // While there is an adjacency to add
            token = strtok(NULL, " ");
            while(token){

                // Add the adjacency
                sscanf(token, "%d", &id);
                cur->adjacentTerritories.push_back(map->map[id-1]);

                // Prepare the next one (if exists)
                token = strtok(NULL, " ");
            }
        }
    }

    // Close the file
    input.close();

    // Validate the map before adding
    if(map->Validate())
        maps.push_back(map);
}

// Destructor for the mapLoader class
MapLoader::~MapLoader() = default;

// Constructor for the continent class
Continent::Continent(std::string name, int territorialReward) {
    this->name = name;
    this->territorialReward = territorialReward;
}

// Stream insertion operator for the continent class
// Ignores color in case it becomes important
std::istream &operator>>(std::istream &in, Continent &continent) {
    in >> continent.name;
    in >> continent.territorialReward;

    std::string color;
    in >> color;

    return in;
}

// Stream output operator for the continent class
// Outputs a styled version of the data
std::ostream &operator<<(std::ostream &out, const Continent &continent) {
    out << "{ Name: " << continent.name << ", Reward: " << continent.territorialReward << " }" << std::endl;

    return out;
}

// Destructor for the continent class
Continent::~Continent() = default;

// Constructor for the territory class
Territory::Territory(int id, std::string name, int continent) {
    this->id = id;
    this->name = name;
    this->continent = continent;
    this->unitsGarrisoned = 0;
    this->visited = false;
}

// Stream insertion operator for the territory class
// Ignores miscData1 and 2 in case it becomes important
std::istream &operator>>(std::istream &in, Territory &territory) {
    in >> territory.id;
    in >> territory.name;
    in >> territory.continent;
    territory.visited = false;

    int miscData1, miscData2;
    in >> miscData1 >> miscData2;

    return in;
}

// Stream output operator for the territory class
// Outputs a styled version of the data
std::ostream &operator<<(std::ostream &out, const Territory &territory) {
    out << "{ Id: " << territory.id << ", Name: " << territory.name;
    out << ", Continent: " << territory.continent << " }" << std::endl;

    return out;
}

// Destructor for the territory class
Territory::~Territory() = default;
