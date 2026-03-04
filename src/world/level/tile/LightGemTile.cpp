#include "LightGemTile.h"

#include "util/Mth.h"
#include "util/java/Random.h"
#include "world/item/Item.h"

class Material;

LightGemTile::LightGemTile(int id, Material* material) : Tile(id, material) {}

int LightGemTile::getResourceCountForLootBonus(int bonusLevel, Random* random) {
    return Mth::clamp(
        getResourceCount(random) + random->nextInt(bonusLevel + 1),
        1,
        4
    );
}

int LightGemTile::getResourceCount(Random* random) {
    return 2 + random->nextInt(3);
}

int LightGemTile::getResource(int data, Random* random, int playerBonusLevel) {
    return Item::yellowDust->id;
}
