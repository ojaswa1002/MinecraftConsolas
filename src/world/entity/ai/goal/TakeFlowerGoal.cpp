#include "TakeFlowerGoal.h"

#include <cstddef>
#include <vector>

#include "util/java/Random.h"
#include "world/entity/ai/control/Control.h"
#include "world/entity/ai/control/LookControl.h"
#include "world/entity/ai/navigation/PathNavigation.h"
#include "world/entity/animal/VillagerGolem.h"
#include "world/entity/npc/Villager.h"
#include "world/level/Level.h"
#include "world/phys/AABB.h"

#include "OfferFlowerGoal.h"

class Entity;

TakeFlowerGoal::TakeFlowerGoal(Villager* villager) {
    takeFlower = false;
    pickupTick = 0;
    golem      = std::weak_ptr<VillagerGolem>();

    this->villager = villager;
    setRequiredControlFlags(
        Control::MoveControlFlag | Control::LookControlFlag
    );
}

bool TakeFlowerGoal::canUse() {
    if (villager->getAge() >= 0) return false;
    if (!villager->level->isDay()) return false;

    std::vector<std::shared_ptr<Entity>>* golems =
        villager->level->getEntitiesOfClass(
            typeid(VillagerGolem),
            villager->bb->grow(6, 2, 6)
        );
    if (golems->size() == 0) {
        delete golems;
        return false;
    }

    // for (Entity e : golems)
    for (auto it = golems->begin(); it != golems->end(); ++it) {
        std::shared_ptr<VillagerGolem> vg =
            dynamic_pointer_cast<VillagerGolem>(*it);
        if (vg->getOfferFlowerTick() > 0) {
            golem = std::weak_ptr<VillagerGolem>(vg);
            break;
        }
    }
    delete golems;
    return golem.lock() != NULL;
}

bool TakeFlowerGoal::canContinueToUse() {
    return golem.lock() != NULL && golem.lock()->getOfferFlowerTick() > 0;
}

void TakeFlowerGoal::start() {
    pickupTick = villager->getRandom()->nextInt(
        (int)(OfferFlowerGoal::OFFER_TICKS * 0.8)
    );
    takeFlower = false;
    golem.lock()->getNavigation()->stop();
}

void TakeFlowerGoal::stop() {
    golem = std::weak_ptr<VillagerGolem>();
    villager->getNavigation()->stop();
}

void TakeFlowerGoal::tick() {
    villager->getLookControl()->setLookAt(golem.lock(), 30, 30);
    if (golem.lock()->getOfferFlowerTick() == pickupTick) {
        villager->getNavigation()->moveTo(golem.lock(), 0.15f);
        takeFlower = true;
    }

    if (takeFlower) {
        if (villager->distanceToSqr(golem.lock()) < 2 * 2) {
            golem.lock()->offerFlower(false);
            villager->getNavigation()->stop();
        }
    }
}
