//
// Created by 14388 on 2021-10-01.
//

#ifndef COMP_345_PROJ_ORDERS_H
#define COMP_345_PROJ_ORDERS_H

#include <vector>
#include <ostream>

class Orders {
private:

public:
    Orders();
    Orders(const Orders &o1);
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
    Deploy();
    ~Deploy();
    Deploy(const Deploy &d1);
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
    Advance();
    ~Advance();
    Advance(const Advance &a1);
    void validate() override;
    static void execute();
    void identify() override;
};
class Bomb : public Orders {
    // destroy half of the armies located on an opponent's territory that is adjacent to one of the current player's territories
private:

public:
    Bomb();
    ~Bomb();
    Bomb(const Bomb &b1);
    void validate() override;
    static void execute();
    void identify() override;
};
class Blockade : public Orders {
    // triple the number of armies on one of the current player's territories and make it a neutral territory
private:

public:
    Blockade();
    ~Blockade();
    Blockade(const Blockade &b1);
    void validate() override;
    static void execute();
    void identify() override;
};
class Airlift : public Orders {
    // advance some armies from one of the current player's territories to any other territory
private:

public:
    Airlift();
    ~Airlift();
    Airlift(const Airlift &a1);
    void validate() override;
    static void execute();
    void identify() override;
};
class Negotiate : public Orders {
    // prevent attacks between the current player and another player until the end of the turn
private:

public:
    Negotiate();
    ~Negotiate();
    Negotiate(const Negotiate &n1);
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
