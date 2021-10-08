#include <iostream>
#include "Map.h"
int main() {
    auto* loader(new MapLoader());

    for(Map *m : loader->maps){
        m->FancyPrint();
    }

    std::cout << loader->maps.size() << std::endl;
}
