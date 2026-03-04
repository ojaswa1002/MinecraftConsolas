#include "Sponge.h"

#include "world/level/material/Material.h"

const int RANGE = 2;


Sponge::Sponge(int id) : Tile(id, Material::sponge) {}
