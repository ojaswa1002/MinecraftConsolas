#include "SeedFoodItem.h"

#include <memory>

#include "world/Facing.h"
#include "world/entity/player/Player.h"
#include "world/level/Level.h"

#include "ItemInstance.h"

SeedFoodItem::SeedFoodItem(
    int   id,
    int   nutrition,
    float saturationMod,
    int   resultId,
    int   targetLand
)
: FoodItem(id, nutrition, saturationMod, false) {
    this->resultId   = resultId;
    this->targetLand = targetLand;
}

bool SeedFoodItem::useOn(
    std::shared_ptr<ItemInstance> instance,
    std::shared_ptr<Player>       player,
    Level*                        level,
    int                           x,
    int                           y,
    int                           z,
    int                           face,
    float                         clickX,
    float                         clickY,
    float                         clickZ,
    bool                          bTestUseOnOnly
) {
    if (face != Facing::UP) return false;

    if (!player->mayBuild(x, y, z) || !player->mayBuild(x, y + 1, z))
        return false;
    int targetType = level->getTile(x, y, z);

    if (targetType == targetLand && level->isEmptyTile(x, y + 1, z)) {
        if (!bTestUseOnOnly) {
            level->setTile(x, y + 1, z, resultId);
            instance->count--;
        }
        return true;
    }
    return false;
}
