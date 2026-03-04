#include "FireChargeItem.h"

#include <cstddef>
#include <memory>
#include <type_traits>
#include <utility>

#include "util/java/Random.h"
#include "world/IconRegister.h"
#include "world/SoundTypes.h"
#include "world/entity/player/Abilities.h"
#include "world/entity/player/Player.h"
#include "world/level/Level.h"
#include "world/level/tile/Tile.h"

#include "ItemInstance.h"

FireChargeItem::FireChargeItem(int id) : Item(id) {
    m_dragonFireballIcon = NULL;
}

bool FireChargeItem::useOn(
    std::shared_ptr<ItemInstance> itemInstance,
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
    if (level->isClientSide) {
        return true;
    }

    if (face == 0) y--;
    if (face == 1) y++;
    if (face == 2) z--;
    if (face == 3) z++;
    if (face == 4) x--;
    if (face == 5) x++;

    if (!player->mayBuild(x, y, z)) {
        return false;
    }

    // 4J-PB - Adding a test only version to allow tooltips to be displayed
    if (bTestUseOnOnly) {
        return true;
    }

    int targetType = level->getTile(x, y, z);

    if (targetType == 0) {
        level->playSound(
            x + 0.5,
            y + 0.5,
            z + 0.5,
            eSoundType_FIRE_IGNITE,
            1,
            random->nextFloat() * 0.4f + 0.8f
        );
        level->setTile(x, y, z, Tile::fire_Id);
    }

    if (!player->abilities.instabuild) {
        itemInstance->count--;
    }
    return true;
}

Icon* FireChargeItem::getIcon(int itemAuxValue) {
    if (itemAuxValue > 0) return m_dragonFireballIcon;
    return Item::getIcon(itemAuxValue);
}

void FireChargeItem::registerIcons(IconRegister* iconRegister) {
    Item::registerIcons(iconRegister);
    m_dragonFireballIcon = iconRegister->registerIcon(L"dragonFireball");
}

