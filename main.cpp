#include <iostream>
#include "GameEngineDriver.h"
#include "Map.h"
#include "Orders.h"
using namespace std;

void OrdersDriver(){

    // Creating objects of Orders subclasses
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

    // Creating OrdersList object
    OrdersList ordersListObj;

    cout << "\nostream operator example for each subclass of order: \n\n";

    cout << deploy1;
    cout << advance1;
    cout << bomb1;
    cout << blockade1;
    cout << airlift1;
    cout << negotiate1 << "\n";

    // Adding all the Orders subclass objects to OrdersList object
    ordersListObj.addDeploy(pDeploy1);
    ordersListObj.addAdvance(pAdvance1);
    ordersListObj.addDeploy(pDeploy2);
    ordersListObj.addAdvance(pAdvance2);
    ordersListObj.addBomb(pBomb1);
    ordersListObj.addBlockade(pBlockade1);
    ordersListObj.addAirlift(pAirlift1);
    ordersListObj.addNegotiate(pNegotiate1);

    // Printing original list
    cout << "\nprinting original vector list in the OrdersList object\n\n";

    for (int i = 0; i < ordersListObj.getList().size(); i++) {
        ordersListObj.getList().at(i)->identify();
    }

    // Testing GetListMember method
    cout << "\nexample of getter method with index 4\n\n";

    ordersListObj.getListMember(4);

    // Testing move method
    cout << "\nmoving index 3 to index 0\n\n";

    ordersListObj.move(3,0);

    for (int i = 0; i < ordersListObj.getList().size(); i++) {
        ordersListObj.getList().at(i)->identify();
    }

    // Testing remove method
    cout << "\nremoving index 1\n\n";

    ordersListObj.remove(1);

    for (int i = 0; i < ordersListObj.getList().size(); i++) {
        ordersListObj.getList().at(i)->identify();
    }

    // Testing move method differently
    cout << "\nmoving index 2 to index 5\n\n";

    ordersListObj.move(2,5);

    for (int i = 0; i < ordersListObj.getList().size(); i++) {
        ordersListObj.getList().at(i)->identify();
    }

    // Testing final case for move method
    cout << "\nmoving index 4 to index 4\n\n";

    ordersListObj.move(4,4);

    for (int i = 0; i < ordersListObj.getList().size(); i++) {
        ordersListObj.getList().at(i)->identify();
    }

    // Testing validate/execute of Deploy class
    cout << "\nexample validate/execute on a deploy object at index 4\n\n";

    ordersListObj.getList().at(4)->validate();

    // Testing validate/execute of Advance class
    cout << "\nexample validate/execute on an advance object at index 1\n\n";

    ordersListObj.getList().at(1)->validate();

    // Testing validate/execute of Bomb class
    cout << "\nexample validate/execute on a bomb object at index 2\n\n";

    ordersListObj.getList().at(2)->validate();

    // Testing validate/execute of Blockade class
    cout << "\nexample validate/execute on an blockade object at index 3\n\n";

    ordersListObj.getList().at(3)->validate();

    // Testing validate/execute of Airlift class
    cout << "\nexample validate/execute on an airlift object at index 5\n\n";

    ordersListObj.getList().at(5)->validate();

    // Testing validate/execute of Negotiate class
    cout << "\nexample validate/execute on an negotiate object at index 6\n\n";

    ordersListObj.getList().at(6)->validate();

}

void runGameEngine(){
    GameEngineDriver driver;

    // loop until game is done
    while(!driver.isGameDone()) {

        // accept user input
        cin >> driver;

        cout << driver << endl;
    }
}

void driveMap() {
    auto* loader(new MapLoader());

    std::cout << *loader;

    std::cout << loader->maps.size() << std::endl;

    delete loader;
}

int main() {
    OrdersDriver();

    return 0;
}
