#include "IceTile.h"

#include <cstddef>
#include <memory>
#include <type_traits>
#include <utility>

#include "stats/GenericStats.h"
#include "world/entity/player/Player.h"
#include "world/food/FoodConstants.h"
#include "world/item/enchantment/EnchantmentHelper.h"
#include "world/level/Level.h"
#include "world/level/LightLayer.h"
#include "world/level/dimension/Dimension.h"
#include "world/level/material/Material.h"

#include "Tile.h"

class ItemInstance;

IceTile::IceTile(int id)
: HalfTransparentTile(id, L"ice", Material::ice, false) {
    friction = 0.98f;
    setTicking(true);
}

int IceTile::getRenderLayer() { return 1; }

bool IceTile::shouldRenderFace(
    LevelSource* level,
    int          x,
    int          y,
    int          z,
    int          face
) {
    return HalfTransparentTile::shouldRenderFace(level, x, y, z, 1 - face);
}

void IceTile::playerDestroy(
    Level*                  level,
    std::shared_ptr<Player> player,
    int                     x,
    int                     y,
    int                     z,
    int                     data
) {
    player->awardStat(
        GenericStats::blocksMined(id),
        GenericStats::param_blocksMined(id, data, 1)
    );
    player->causeFoodExhaustion(FoodConstants::EXHAUSTION_MINE);

    if (isSilkTouchable()
        && EnchantmentHelper::hasSilkTouch(player->inventory)) {
        std::shared_ptr<ItemInstance> item = getSilkTouchItemInstance(data);
        if (item != NULL) {
            popResource(level, x, y, z, item);
        }
    } else {
        if (level->dimension->ultraWarm) {
            level->setTile(x, y, z, 0);
            return;
        }

        int playerBonusLevel =
            EnchantmentHelper::getDiggingLootBonus(player->inventory);
        spawnResources(level, x, y, z, data, playerBonusLevel);
        Material* below = level->getMaterial(x, y - 1, z);
        if (below->blocksMotion() || below->isLiquid()) {
            level->setTile(x, y, z, Tile::water_Id);
        }
    }
}

int IceTile::getResourceCount(Random* random) { return 0; }

void IceTile::tick(Level* level, int x, int y, int z, Random* random) {
    if (level->getBrightness(LightLayer::Block, x, y, z)
        > 11 - Tile::lightBlock[id]) {
        if (level->dimension->ultraWarm) {
            level->setTile(x, y, z, 0);
            return;
        }
        this->spawnResources(level, x, y, z, level->getData(x, y, z), 0);
        level->setTile(x, y, z, Tile::calmWater_Id);
    }
}

bool IceTile::shouldTileTick(Level* level, int x, int y, int z) {
    return level->getBrightness(LightLayer::Block, x, y, z)
         > 11 - Tile::lightBlock[id];
}

int IceTile::getPistonPushReaction() { return Material::PUSH_NORMAL; }
