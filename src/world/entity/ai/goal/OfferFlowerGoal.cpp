#include "OfferFlowerGoal.h"

#include <cstddef>

#include "util/java/Random.h"
#include "world/entity/ai/control/Control.h"
#include "world/entity/ai/control/LookControl.h"
#include "world/entity/animal/VillagerGolem.h"
#include "world/entity/npc/Villager.h"
#include "world/level/Level.h"
#include "world/phys/AABB.h"

OfferFlowerGoal::OfferFlowerGoal(VillagerGolem* golem) {
    this->golem = golem;
    setRequiredControlFlags(
        Control::MoveControlFlag | Control::LookControlFlag
    );
}

bool OfferFlowerGoal::canUse() {
    if (!golem->level->isDay()) return false;
    if (golem->getRandom()->nextInt(8000) != 0) return false;
    villager = std::weak_ptr<Villager>(
        dynamic_pointer_cast<Villager>(golem->level->getClosestEntityOfClass(
            typeid(Villager),
            golem->bb->grow(6, 2, 6),
            golem->shared_from_this()
        ))
    );
    return villager.lock() != NULL;
}

bool OfferFlowerGoal::canContinueToUse() {
    return _tick > 0 && villager.lock() != NULL;
}

void OfferFlowerGoal::start() {
    _tick = OFFER_TICKS;
    golem->offerFlower(true);
}

void OfferFlowerGoal::stop() {
    golem->offerFlower(false);
    villager = std::weak_ptr<Villager>();
}

void OfferFlowerGoal::tick() {
    golem->getLookControl()->setLookAt(villager.lock(), 30, 30);
    --_tick;
}
