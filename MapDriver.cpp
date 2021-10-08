#include <iostream>
#include "Map.h"

int main() {
    MapLoader* loader(new MapLoader);
    Map *map = loader->Load("A:\\Programming Stuff\\GitHub\\COMP_345_PROJ\\Maps\\canada.map", false);
    // map->Print();
    std::cout << map->Validate();
}
