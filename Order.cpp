//
// Created by Ryan on 2021-09-25.
//

#include <iostream>
#include <utility>
#include "Order.h"

Order::Order() {
}

std::string Order::getOrder() {
    return myOrder;
}

void Order::setOrder(std::string order) {
    myOrder = std::move(order);
}
