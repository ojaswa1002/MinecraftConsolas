#include "LookAtTradingPlayerGoal.h"

#include <memory>

#include "world/entity/npc/Villager.h"
#include "world/entity/player/Player.h"

class Entity;
class Mob;

LookAtTradingPlayerGoal::LookAtTradingPlayerGoal(Villager* villager)
: LookAtPlayerGoal((Mob*)villager, typeid(Player), 8) {
    this->villager = villager;
}

bool LookAtTradingPlayerGoal::canUse() {
    if (villager->isTrading()) {
        lookAt = std::weak_ptr<Entity>(
            dynamic_pointer_cast<Entity>(villager->getTradingPlayer())
        );
        return true;
    }
    return false;
}
