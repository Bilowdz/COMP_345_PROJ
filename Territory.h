//
// Created by Ryan on 2021-09-25.
//

#ifndef COMP_345_PROJ_TERRITORY_H
#define COMP_345_PROJ_TERRITORY_H

#include <vector>

class Territory {
public:
    Territory();
    //Territory(int *numOfTerritories);
    Territory(int id, std::string name);
    ~Territory();
    int id;
    std::string name;
    int unitsGarrisoned;
    std::vector<Territory*> adjacentTerritories;
    void setNumTerritories(int *numOfTerritories);
    int getNumTerritories() const;
    void identify();
    void setSize(int);
    int getSize() const;
    std::string getName() const;
    int getId() const;
private:
    int numOfTerritories; //number of territories player owns
    int size;
};


#endif //COMP_345_PROJ_TERRITORY_H
