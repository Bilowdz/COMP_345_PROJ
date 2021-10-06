//
// Created by Ryan on 2021-09-25.
//

#ifndef COMP_345_PROJ_TERRITORY_H
#define COMP_345_PROJ_TERRITORY_H


class Territory {
public:
    Territory();
    Territory(int *numOfTerritories);
    void setNumTerritories(int *numOfTerritories);
    int& getNumTerritories();
private:
    int numOfTerritories;

};


#endif //COMP_345_PROJ_TERRITORY_H
