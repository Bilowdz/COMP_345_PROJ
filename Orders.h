//
// Created by 14388 on 2021-10-01.
//

#ifndef COMP_345_PROJ_ORDERS_H
#define COMP_345_PROJ_ORDERS_H

class Orders {
private:
    // each order is implemented as a subclass of this class
    // each of these subclasses must implement validate() to make sure the order can be done
    // also implement execute() which first uses validate() then executes the order for each subclass
public:
};

//------------------------------------------------------------------
// Subclasses of Orders:
//------------------------------------------------------------------

class Deploy : public Orders {
    // place some armies on one of the current player's territories
private:
    int armies;
public:
    void deployArmies(int armies);
    void validate(int armies);
    void execute();
};
class Advance : public Orders {
    // move some armies from one of the current player's territories to an adjacent territory
private:
    void advanceArmies(int armies);
public:
    void validate();
    void execute();
};
class Bomb : public Orders {
    // destroy half of the armies located on an opponent's territory that is adjacent to one of the current player's territories
private:

public:
    void validate();
    void execute();
};
class Blockade : public Orders {
    // triple the number of armies on one of the current player's territories and make it a neutral territory
private:

public:
    void validate();
    void execute();
};
class Airlift : public Orders {
    // advance some armies from one of the current player's territories to any other territory
private:

public:
    void validate();
    void execute();
};
class Negotiate : public Orders {
    // prevent attacks between the current player and another player until the end of the turn
private:

public:
    void validate();
    void execute();
};

//--------------------------------------------------------------------------
// OrdersList class which takes in objects of each subclass of Order class:
//--------------------------------------------------------------------------

class OrdersList {
    // contains a list of Orders objects
private:
    //Orders arrayOfOrders[];
public:
    void addDeploy(Deploy addDeploy);
    void move();
    void remove();
};

#endif //COMP_345_PROJ_ORDERS_H
