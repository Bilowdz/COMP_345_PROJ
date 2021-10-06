//
// Created by Ryan on 2021-09-25.
//

#ifndef COMP_345_PROJ_TERRITORY_H
#define COMP_345_PROJ_TERRITORY_H

#include <vector>

class Territory {
public:
    Territory();
    Territory(int *numOfTerritories);

    Territory(int id, std::string name);
    int id;
    std::string name;
    int unitsGarrisoned;
    // Owner
    std::vector<Territory*> adjacentTerritories;

    void setNumTerritories(int *numOfTerritories);
    int& getNumTerritories();
    void identify();
private:
    int numOfTerritories;

};


#endif //COMP_345_PROJ_TERRITORY_H
