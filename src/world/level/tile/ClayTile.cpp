#include "ClayTile.h"

#include "world/item/Item.h"
#include "world/level/material/Material.h"

ClayTile::ClayTile(int id) : Tile(id, Material::clay) {}

int ClayTile::getResource(int data, Random* random, int playerBonusLevel) {
    return Item::clay->id;
}

int ClayTile::getResourceCount(Random* random) { return 4; }
