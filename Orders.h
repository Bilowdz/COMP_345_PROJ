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
#include "Map.h"
#include "Card.h"

using namespace std;

class Player;

//------------------------------------------------------------------
// Orders class, the parent class to each order:
//------------------------------------------------------------------

/**
 * Orders class definitions
 */
class Orders {
private:
    Player * playerLink;
public:
    Orders();
    virtual ~Orders();
    Orders(const Orders &o1);
    virtual void identify();
    virtual void validate(Player *);
    virtual void execute(Player *) = 0;
    virtual Player * getPlayerLink();
    virtual void setPlayerLink(Player & player);
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
    Territory territory;
public:
    void setArmies(int sArmies);
    [[nodiscard]] int getArmies() const;
    Deploy();
    ~Deploy() override;
    Deploy(int sArmies, Territory&);
    Deploy(const Deploy &d1);
    Deploy &operator=(const Deploy &p);
    void validate(Player *) override;
    void execute(Player *) override;
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
    Territory * source;
    Territory * target;
public:
    void setArmies(int sArmies);
    [[nodiscard]] int getArmies() const;
    Advance();
    ~Advance() override;
    Advance(int sArmies, Territory& source, Territory& target);
    Advance(const Advance &a1);
    Advance &operator=(const Advance &p);
    void validate(Player *) override;
    void execute(Player *, Deck *) override;
    void identify() override;
    friend ostream &operator << (ostream &, const Advance &advance);
};

/**
 * Bomb class definitions
 */
class Bomb : public Orders {
    // destroy half of the armies located on an opponent's territory that is adjacent to one of the current player's territories
private:
    Territory * target;
public:
    Bomb();
    ~Bomb() override;
    Bomb(Territory& target);
    Bomb(const Bomb &b1);
    Bomb &operator=(const Bomb &p);
    void validate(Player *) override;
    void execute(Player *) override;
    void identify() override;
    friend ostream &operator << (ostream &, const Bomb &bomb);
};

/**
 * Blockade class definitions
 */
class Blockade : public Orders {
    // triple the number of armies on one of the current player's territories and make it a neutral territory
private:
    Territory * target;
public:
    Blockade();
    ~Blockade() override;
    Blockade(Territory& target);
    Blockade(const Blockade &b1);
    Blockade &operator=(const Blockade &p);
    void validate(Player *) override;
    void execute(Player *) override;
    void identify() override;
    friend ostream &operator << (ostream &, const Blockade &blockade);
};

/**
 * Airlift class definitions
 */
class Airlift : public Orders {
    // advance some armies from one of the current player's territories to any other territory
private:
    int armies{};
    Territory * source;
    Territory * target;
public:
    Airlift();
    ~Airlift() override;
    Airlift(int sArmies, Territory& source, Territory& target);
    Airlift(const Airlift &a1);
    Airlift &operator=(const Airlift &p);
    void validate(Player *) override;
    void execute(Player *) override;
    void identify() override;
    friend ostream &operator << (ostream &, const Airlift &airlift);
};

/**
 * Negotiate class definitions
 */
class Negotiate : public Orders {
    // prevent attacks between the current player and another player until the end of the turn
private:
    Player * targetPlayer;
public:
    Negotiate();
    ~Negotiate() override;
    Negotiate(Player * targetPlayer);
    Negotiate(const Negotiate &n1);
    Negotiate &operator=(const Negotiate &p);
    void validate(Player *) override;
    void execute(Player *) override;
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
    OrdersList &operator=(const OrdersList &p);
    Orders* getListMember(int index);
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
