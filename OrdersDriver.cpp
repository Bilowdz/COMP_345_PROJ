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

    Bomb bomb1;
    Bomb *pBomb1 = &bomb1;

    Blockade blockade1;
    Blockade *pBlockade1 = &blockade1;

    Airlift airlift1;
    Airlift *pAirlift1 = &airlift1;

    Negotiate negotiate1;
    Negotiate *pNegotiate1 = &negotiate1;

    OrdersList ordersListObj;

    ordersListObj.addDeploy(pDeploy1);
    ordersListObj.addAdvance(pAdvance1);
    ordersListObj.addDeploy(pDeploy2);
    ordersListObj.addAdvance(pAdvance2);
    ordersListObj.addBomb(pBomb1);
    ordersListObj.addBlockade(pBlockade1);
    ordersListObj.addAirlift(pAirlift1);
    ordersListObj.addNegotiate(pNegotiate1);

    cout << "\nprinting original vector list in the OrdersList object\n\n";

    for (int i = 0; i < ordersListObj.getList().size(); i++) {
        ordersListObj.getList().at(i)->identify();
    }

    cout << "\nexample of getter method with index 4\n\n";

    ordersListObj.getListMember(4);

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

    cout << "\nexample validate/execute on a deploy object at index 2\n\n";

    ordersListObj.getList().at(2)->validate();

    cout << "\nexample validate/execute on an advance object at index 1\n\n";

    ordersListObj.getList().at(1)->validate();

    cout << "\nexample validate/execute on a bomb object at index 3\n\n";

    ordersListObj.getList().at(3)->validate();

    cout << "\nexample validate/execute on an blockade object at index 4\n\n";

    ordersListObj.getList().at(4)->validate();

    cout << "\nexample validate/execute on an airlift object at index 5\n\n";

    ordersListObj.getList().at(5)->validate();

    cout << "\nexample validate/execute on an negotiate object at index 6\n\n";

    ordersListObj.getList().at(6)->validate();
}