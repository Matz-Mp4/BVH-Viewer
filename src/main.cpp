#include "../third-party/happly/happly.h"
#include "../include/objects/ObjectLoader.hpp"

#include <iostream>

int main () {
    ObjectLoader objloader("../models/horse.ply");
    std::cout << objloader.generate_mesh();
    return 0;
}
