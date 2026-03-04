#include "AirTile.h"

#include "world/level/material/Material.h"

AirTile::AirTile(int id) : Tile(id, Material::air) {}
