#include <iostream>
#include "Map.h"

int main() {
    MapLoader* loader(new MapLoader);
    loader->Load("A:\\Programming Stuff\\GitHub\\COMP_345_PROJ\\Maps\\canada.map");
}
