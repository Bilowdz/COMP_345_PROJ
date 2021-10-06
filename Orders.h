//
// Created by 14388 on 2021-10-01.
//

#ifndef COMP_345_PROJ_ORDERS_H
#define COMP_345_PROJ_ORDERS_H

#include <vector>
#include <ostream>

class Orders {
private:
    // each order is implemented as a subclass of this class
    // each of these subclasses must implement validate() to make sure the order can be done
    // also implement execute() which first uses validate() then executes the order for each subclass
public:
    virtual void identify();
    virtual void validate();
};

//------------------------------------------------------------------
// Subclasses of Orders:
//------------------------------------------------------------------

class Deploy : public Orders {
//    // place some armies on one of the current player's territories
private:
    int armies{};
public:
    void setArmies(int sArmies);
    int getArmies() const;
    void validate() override;
    static void execute();
    void identify() override;
};
class Advance : public Orders {
    // move some armies from one of the current player's territories to an adjacent territory
private:
    int armies{};
public:
    void setArmies(int sArmies);
    int getArmies() const;
    void validate() override;
    static void execute();
    void identify() override;
};
class Bomb : public Orders {
    // destroy half of the armies located on an opponent's territory that is adjacent to one of the current player's territories
private:

public:
    void validate() override;
    static void execute();
    void identify() override;
};
class Blockade : public Orders {
    // triple the number of armies on one of the current player's territories and make it a neutral territory
private:

public:
    void validate() override;
    static void execute();
    void identify() override;
};
class Airlift : public Orders {
    // advance some armies from one of the current player's territories to any other territory
private:

public:
    void validate() override;
    static void execute();
    void identify() override;
};
class Negotiate : public Orders {
    // prevent attacks between the current player and another player until the end of the turn
private:

public:
    void validate() override;
    static void execute();
    void identify() override;
};

//--------------------------------------------------------------------------
// OrdersList class which takes in objects of each subclass of Order class:
//--------------------------------------------------------------------------

class OrdersList {
    // contains a list of Orders objects
private:
    std::vector<Orders*> ordersList;
public:
    OrdersList();
    void getListMember(int index);
    std::vector<Orders*> getList();

    void addDeploy(Deploy * deploy);
    void addAdvance(Advance * advance);
    void addBomb(Bomb * bomb);
    void addBlockade(Blockade * blockade);
    void addAirlift(Airlift * airlift);
    void addNegotiate(Negotiate * negotiate);

    void move(int indexFrom, int indexTo);
    void remove(int index);
};

#endif //COMP_345_PROJ_ORDERS_H
