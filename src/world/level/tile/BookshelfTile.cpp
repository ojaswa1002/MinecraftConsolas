#include "BookshelfTile.h"

#include "world/Facing.h"
#include "world/item/Item.h"
#include "world/level/material/Material.h"

BookshelfTile::BookshelfTile(int id) : Tile(id, Material::wood) {}

Icon* BookshelfTile::getTexture(int face, int data) {
    if (face == Facing::UP || face == Facing::DOWN)
        return Tile::wood->getTexture(face);
    return Tile::getTexture(face, data);
}

int BookshelfTile::getResourceCount(Random* random) { return 3; }

int BookshelfTile::getResource(int data, Random* random, int playerBonusLevel) {
    return Item::book_Id;
}
