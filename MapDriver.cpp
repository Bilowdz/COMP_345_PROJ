#include <iostream>
#include "Map.h"
int main() {

    MapLoader* loader(new MapLoader);
    //Map *map = loader->Load("C:\\Users\\Nicolo pt 2\\Desktop\\School\\University\\6. FALL2021\\COMP345\\Projects\\Project\\Syllabus.COMP345.paquet.2021.2.pdf\\COMP_345_PROJ\\Maps\\canada.map", false);
    Map *map = loader->Load("../Maps/canada.map", false);
    map->Print();
    std::cout << map->Validate();
}
