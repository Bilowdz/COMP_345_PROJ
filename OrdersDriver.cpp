//
// Created by 14388 on 2021-10-01.
//

#include "Orders.h"
#include <stdio.h>
#include <iostream>
using namespace std;

// Driver that creates an order of every kind, places them in an OrdersList object, and demonstrates that the above features are available.
int main(){

    Deploy deploy1;
    deploy1.setArmies(11);
    Deploy *pDeploy1 = &deploy1;

    Advance advance1;
    advance1.setArmies(7);
    Advance *pAdvance1 = &advance1;

    Deploy deploy2;
    deploy2.setArmies(23);
    Deploy *pDeploy2 = &deploy2;

    Advance advance2;
    advance2.setArmies(2);
    Advance *pAdvance2 = &advance2;

    OrdersList ordersListObj;

    ordersListObj.addDeploy(pDeploy1);
    ordersListObj.addAdvance(pAdvance1);
    ordersListObj.addDeploy(pDeploy2);
    ordersListObj.addAdvance(pAdvance2);

    cout << "\nprinting original vector list in the OrdersList object\n\n";

    for (int i = 0; i < ordersListObj.getList().size(); i++) {
        ordersListObj.getList().at(i)->identify();
    }
    cout << "\nmoving index 3 to index 0\n\n";

    ordersListObj.move(3,0);

    for (int i = 0; i < ordersListObj.getList().size(); i++) {
        ordersListObj.getList().at(i)->identify();
    }
    cout << "\nremoving index 1\n\n";

    ordersListObj.remove(1);

    for (int i = 0; i < ordersListObj.getList().size(); i++) {
        ordersListObj.getList().at(i)->identify();
    }

}