//
// Created by 14388 on 2021-10-01.
//

#include "Orders.h"
#include <stdio.h>
using namespace std;

// Driver that creates an order of every kind, places them in an OrdersList object, and demonstrates that the above features are available.
int main(){

    vector<Orders> orders(0);
    Deploy deploy(5);
    orders.push_back(deploy);

    //OrdersList(orders);

    for (int i = 0; i < orders.size(); i++) {
        orders.at(i).toString();
    }

    printf("\nOrdersDriver.cpp terminating.\n");

}