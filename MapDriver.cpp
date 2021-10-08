#include <iostream>
#include "Map.h"
int main() {
    auto* loader(new MapLoader());
    std::cout << loader->maps.size() << std::endl;
}
