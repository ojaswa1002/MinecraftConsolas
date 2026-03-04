#include "StoneTile.h"

#include "world/level/material/Material.h"

StoneTile::StoneTile(int id) : Tile(id, Material::stone) {}

int StoneTile::getResource(int data, Random* random, int playerBonusLevel) {
    return Tile::stoneBrick_Id;
}
