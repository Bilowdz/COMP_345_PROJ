/**
 * Created by: Simon Bilodeau 40130702
 * Due date: Oct 3rd, 2021
 * Class: COMP 345
 * Professor: Joey Paquet
 *
 * Orders.h description:
 * This file includes the method definitions for the following classes:
 * OrdersList, Orders, and subclasses of Orders: Deploy, Advance, Bomb, Blockade, Airlift, Negotiate.
 * The class OrdersList has a vector of Orders objects as its only member. This vector is composed of
 * objects of the subclasses of Orders. These are orders used by the players to order their armies around
 * the map. Each order has a different function for the player, described in its "identify()" method in Orders.cpp.
 */

#ifndef COMP_345_PROJ_ORDERS_H
#define COMP_345_PROJ_ORDERS_H

#include <vector>
#include <ostream>
using namespace std;

//------------------------------------------------------------------
// Orders class, the parent class to each order:
//------------------------------------------------------------------

/**
 * Orders class definitions
 */
class Orders {
private:

public:
    Orders();
    ~Orders();
    Orders(const Orders &o1);
    virtual void identify();
    virtual void validate();
    friend ostream &operator << (ostream &, const Orders &orders);

};

//------------------------------------------------------------------
// Subclasses of Orders:
//------------------------------------------------------------------

/**
 * Deploy class definitions
 */
class Deploy : public Orders {
    // place some armies on one of the current player's territories
private:
    int armies{};
public:
    void setArmies(int sArmies);
    [[nodiscard]] int getArmies() const;
    Deploy();
    ~Deploy();
    Deploy(const Deploy &d1);
    void validate() override;
    static void execute();
    void identify() override;
    friend ostream &operator << (ostream &, const Deploy &deploy);
};

/**
 * Advance class definitions
 */
class Advance : public Orders {
    // move some armies from one of the current player's territories to an adjacent territory
private:
    int armies{};
public:
    void setArmies(int sArmies);
    [[nodiscard]] int getArmies() const;
    Advance();
    ~Advance();
    Advance(const Advance &a1);
    void validate() override;
    static void execute();
    void identify() override;
    friend ostream &operator << (ostream &, const Advance &advance);
};

/**
 * Bomb class definitions
 */
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
    friend ostream &operator << (ostream &, const Bomb &bomb);
};

/**
 * Blockade class definitions
 */
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
    friend ostream &operator << (ostream &, const Blockade &blockade);
};

/**
 * Airlift class definitions
 */
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
    friend ostream &operator << (ostream &, const Airlift &airlift);
};

/**
 * Negotiate class definitions
 */
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
    friend ostream &operator << (ostream &, const Negotiate &negotiate);
};

//--------------------------------------------------------------------------
// OrdersList class which takes in objects of each subclass of Order class:
//--------------------------------------------------------------------------

/**
 * OrdersList class definitions
 */
class OrdersList {
    // contains a list of Orders objects
private:
    std::vector<Orders*> ordersList;
public:
    OrdersList();
    ~OrdersList();
    OrdersList(const OrdersList &o1);
    void getListMember(int index);
    std::vector<Orders*> getList();
    friend ostream &operator << (ostream &, const OrdersList &ordersList);

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
