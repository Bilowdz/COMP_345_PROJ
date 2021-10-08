#include <iostream>
#include "Map.h"
int main() {
    auto* loader(new MapLoader());

    Map *copyMap = new Map(*loader->maps.front());

    std::cout << *loader;

    std::cout << loader->maps.size() << std::endl;
}
