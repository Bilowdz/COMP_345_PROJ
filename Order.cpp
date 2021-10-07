//
// Created by Ryan on 2021-09-25.
//

#include <iostream>
#include <utility>
#include "Order.h"

Order::Order() {
}
Order::Order(std::string passedInOrder) {
    myOrder = std::move(passedInOrder);
}

std::string Order::getOrder() {
    return myOrder;
}

void Order::setOrder(std::string order) {
    myOrder = std::move(order);
}


