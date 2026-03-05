#include "PlayGoal.h"

#include <cstddef>
#include <vector>

#include "util/java/BasicTypeContainers.h"
#include "util/java/Random.h"
#include "world/entity/Entity.h"
#include "world/entity/Mob.h"
#include "world/entity/PathfinderMob.h"
#include "world/entity/ai/control/Control.h"
#include "world/entity/ai/navigation/PathNavigation.h"
#include "world/entity/ai/util/RandomPos.h"
#include "world/entity/npc/Villager.h"
#include "world/level/Level.h"
#include "world/phys/AABB.h"
#include "world/phys/Vec3.h"

PlayGoal::PlayGoal(Villager* mob, float speed) {
    followFriend = std::weak_ptr<Mob>();
    wantedX = wantedY = wantedZ = 0.0;
    playTime                    = 0;

    this->mob   = mob;
    this->speed = speed;
    setRequiredControlFlags(Control::MoveControlFlag);
}

bool PlayGoal::canUse() {
    if (mob->getAge() >= 0) return false;
    if (mob->getRandom()->nextInt(400) != 0) return false;

    std::vector<std::shared_ptr<Entity>>* children =
        mob->level->getEntitiesOfClass(
            typeid(Villager),
            mob->bb->grow(6, 3, 6)
        );
    double closestDistSqr = Double::MAX_VALUE;
    // for (Entity c : children)
    for (auto it = children->begin(); it != children->end(); ++it) {
        std::shared_ptr<Entity> c = *it;
        if (c.get() == mob) continue;
        std::shared_ptr<Villager> friendV =
            std::dynamic_pointer_cast<Villager>(c);
        if (friendV->isChasing()) continue;
        if (friendV->getAge() >= 0) continue;
        double distSqr = friendV->distanceToSqr(mob->shared_from_this());
        if (distSqr > closestDistSqr) continue;
        closestDistSqr = distSqr;
        followFriend   = std::weak_ptr<Mob>(friendV);
    }
    delete children;

    if (followFriend.lock() == NULL) {
        Vec3* pos = RandomPos::getPos(
            std::dynamic_pointer_cast<PathfinderMob>(mob->shared_from_this()),
            16,
            3
        );
        if (pos == NULL) return false;
    }
    return true;
}

bool PlayGoal::canContinueToUse() {
    return playTime > 0 && followFriend.lock() != NULL;
}

void PlayGoal::start() {
    if (followFriend.lock() != NULL) mob->setChasing(true);
    playTime = 1000;
}

void PlayGoal::stop() {
    mob->setChasing(false);
    followFriend = std::weak_ptr<Mob>();
}

void PlayGoal::tick() {
    --playTime;
    if (followFriend.lock() != NULL) {
        if (mob->distanceToSqr(followFriend.lock()) > 2 * 2)
            mob->getNavigation()->moveTo(followFriend.lock(), speed);
    } else {
        if (mob->getNavigation()->isDone()) {
            Vec3* pos = RandomPos::getPos(
                std::dynamic_pointer_cast<PathfinderMob>(
                    mob->shared_from_this()
                ),
                16,
                3
            );
            if (pos == NULL) return;
            mob->getNavigation()->moveTo(pos->x, pos->y, pos->z, speed);
        }
    }
}
