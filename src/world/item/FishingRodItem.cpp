#include "FishingRodItem.h"

#include <cstddef>
#include <memory>
#include <type_traits>
#include <utility>

#include "util/java/Random.h"
#include "world/IconRegister.h"
#include "world/SoundTypes.h"
#include "world/entity/player/Player.h"
#include "world/entity/projectile/FishingHook.h"
#include "world/level/Level.h"

#include "ItemInstance.h"

class Icon;

const std::wstring FishingRodItem::TEXTURE_EMPTY = L"fishingRod_empty";

FishingRodItem::FishingRodItem(int id) : Item(id) {
    setMaxDamage(64);
    setMaxStackSize(1);
    emptyIcon = NULL;
}

bool FishingRodItem::isHandEquipped() { return true; }

bool FishingRodItem::isMirroredArt() { return true; }

std::shared_ptr<ItemInstance> FishingRodItem::use(
    std::shared_ptr<ItemInstance> instance,
    Level*                        level,
    std::shared_ptr<Player>       player
) {
    if (player->fishing != NULL) {
        int dmg = player->fishing->retrieve();
        instance->hurt(dmg, player);
        player->swing();
    } else {
        level->playSound(
            player,
            eSoundType_RANDOM_BOW,
            0.5f,
            0.4f / (random->nextFloat() * 0.4f + 0.8f)
        );
        if (!level->isClientSide) {
            // 4J Stu - Move the player->fishing out of the ctor as we cannot
            // reference 'this'
            std::shared_ptr<FishingHook> hook =
                std::shared_ptr<FishingHook>(new FishingHook(level, player));
            player->fishing = hook;
            level->addEntity(std::shared_ptr<FishingHook>(hook));
        }
        player->swing();
    }
    return instance;
}

void FishingRodItem::registerIcons(IconRegister* iconRegister) {
    Item::registerIcons(iconRegister);
    emptyIcon = iconRegister->registerIcon(TEXTURE_EMPTY);
}

Icon* FishingRodItem::getEmptyIcon() { return emptyIcon; }
