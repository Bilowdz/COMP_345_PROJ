//
// Created by 14388 on 2021-10-01.
//

#ifndef COMP_345_PROJ_ORDERS_H
#define COMP_345_PROJ_ORDERS_H

class Orders {
    // each order is implemented as a subclass of this class
    // each of these subclasses must implement validate() to make sure the order can be done
    // also implement execute() which first uses validate() then executes the order for each subclass
    class Deploy {
    private:

    public:
        void validate();
        void execute();
    };
    class Advance {
    private:

    public:
        void validate();
        void execute();
    };
    class Bomb {
    private:

    public:
        void validate();
        void execute();
    };
    class Blockade {
    private:

    public:
        void validate();
        void execute();
    };
    class Airlift {
    private:

    public:
        void validate();
        void execute();
    };
    class Negotiate {
    private:

    public:
        void validate();
        void execute();
    };
};

class OrdersList {
    // contains a list of Orders objects
private:

public:
    void move();
    void remove();
};

#endif //COMP_345_PROJ_ORDERS_H
