#include "SmoothStoneBrickTileItem.h"

#include <memory>

#include "world/level/tile/SmoothStoneBrickTile.h"
#include "world/level/tile/Tile.h"

#include "ItemInstance.h"

SmoothStoneBrickTileItem::SmoothStoneBrickTileItem(int id, Tile* parentTile)
: TileItem(id) {
    this->parentTile = parentTile;

    setMaxDamage(0);
    setStackedByData(true);
}

Icon* SmoothStoneBrickTileItem::getIcon(int itemAuxValue) {
    return parentTile->getTexture(2, itemAuxValue);
}

int SmoothStoneBrickTileItem::getLevelDataForAuxValue(int auxValue) {
    return auxValue;
}

unsigned int SmoothStoneBrickTileItem::getDescriptionId(
    std::shared_ptr<ItemInstance> instance
) {
    int auxValue = instance->getAuxValue();
    if (auxValue < 0
        || auxValue >= SmoothStoneBrickTile::SMOOTH_STONE_BRICK_NAMES_LENGTH) {
        auxValue = 0;
    }
    return SmoothStoneBrickTile::SMOOTH_STONE_BRICK_NAMES[auxValue];
}
