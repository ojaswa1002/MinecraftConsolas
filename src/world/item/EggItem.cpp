#include "EggItem.h"

#include <memory>

#include "util/java/Random.h"
#include "world/SoundTypes.h"
#include "world/entity/player/Abilities.h"
#include "world/entity/player/Player.h"
#include "world/entity/projectile/ThrownEgg.h"
#include "world/level/Level.h"

#include "ItemInstance.h"

class Entity;
class Mob;

EggItem::EggItem(int id) : Item(id) { this->maxStackSize = 16; }

std::shared_ptr<ItemInstance> EggItem::use(
    std::shared_ptr<ItemInstance> instance,
    Level*                        level,
    std::shared_ptr<Player>       player
) {
    if (!player->abilities.instabuild) {
        instance->count--;
    }
    level->playSound(
        dynamic_pointer_cast<Entity>(player),
        eSoundType_RANDOM_BOW,
        0.5f,
        0.4f / (random->nextFloat() * 0.4f + 0.8f)
    );
    if (!level->isClientSide)
        level->addEntity(
            std::shared_ptr<ThrownEgg>(
                new ThrownEgg(level, dynamic_pointer_cast<Mob>(player))
            )
        );
    return instance;
}
