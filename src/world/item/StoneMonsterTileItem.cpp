#include "StoneMonsterTileItem.h"

#include <memory>

#include "world/level/tile/StoneMonsterTile.h"
#include "world/level/tile/Tile.h"

#include "ItemInstance.h"

StoneMonsterTileItem::StoneMonsterTileItem(int id) : TileItem(id) {
    setMaxDamage(0);
    setStackedByData(true);
}

int StoneMonsterTileItem::getLevelDataForAuxValue(int auxValue) {
    return auxValue;
}

Icon* StoneMonsterTileItem::getIcon(int itemAuxValue) {
    return Tile::monsterStoneEgg->getTexture(0, itemAuxValue);
}

unsigned int
StoneMonsterTileItem::getDescriptionId(std::shared_ptr<ItemInstance> instance) {
    int auxValue = instance->getAuxValue();
    if (auxValue < 0
        || auxValue >= StoneMonsterTile::STONE_MONSTER_NAMES_LENGTH) {
        auxValue = 0;
    }
    return StoneMonsterTile::STONE_MONSTER_NAMES[auxValue];
}
