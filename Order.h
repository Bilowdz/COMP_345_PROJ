//
// Created by Ryan on 2021-09-25.
//

#ifndef COMP_345_PROJ_ORDER_H
#define COMP_345_PROJ_ORDER_H


class Order {
public:
    Order();
    std::string getOrder();
    void setOrder(std::string order);
private:
    std::string myOrder = "This is my order";
};


#endif //COMP_345_PROJ_ORDER_H
