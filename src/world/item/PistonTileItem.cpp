#include "PistonTileItem.h"

#include "world/level/tile/piston/PistonBaseTile.h"

PistonTileItem::PistonTileItem(int id) : TileItem(id) {}

int PistonTileItem::getLevelDataForAuxValue(int auxValue) {
    // return an undefined facing until the setPlacedBy method is called
    return PistonBaseTile::UNDEFINED_FACING;
}
