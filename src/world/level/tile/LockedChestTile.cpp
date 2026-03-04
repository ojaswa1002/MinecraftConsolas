#include "LockedChestTile.h"

#include "world/level/Level.h"
#include "world/level/material/Material.h"

LockedChestTile::LockedChestTile(int id) : Tile(id, Material::wood) {}

bool LockedChestTile::mayPlace(Level* level, int x, int y, int z) {
    return true;
}

void LockedChestTile::tick(Level* level, int x, int y, int z, Random* random) {
    level->setTile(x, y, z, 0);
}

void LockedChestTile::registerIcons(IconRegister* iconRegister) {
    // None
}
