#include "HurtByTargetGoal.h"

#include <cstddef>
#include <vector>

#include "world/entity/Mob.h"
#include "world/level/Level.h"
#include "world/phys/AABB.h"

class Entity;

HurtByTargetGoal::HurtByTargetGoal(Mob* mob, bool alertSameType)
: TargetGoal(mob, 16, false) {
    this->alertSameType = alertSameType;
    setRequiredControlFlags(TargetGoal::TargetFlag);
}

bool HurtByTargetGoal::canUse() {
    return canAttack(mob->getLastHurtByMob(), false);
}

void HurtByTargetGoal::start() {
    mob->setTarget(mob->getLastHurtByMob());
    oldHurtByMob = mob->getLastHurtByMob();

    if (alertSameType) {
        std::vector<std::shared_ptr<Entity>>* nearby =
            mob->level->getEntitiesOfClass(
                typeid(*mob),
                AABB::newTemp(
                    mob->x,
                    mob->y,
                    mob->z,
                    mob->x + 1,
                    mob->y + 1,
                    mob->z + 1
                )
                    ->grow(within, 4, within)
            );
        for (auto it = nearby->begin(); it != nearby->end(); ++it) {
            std::shared_ptr<Mob> other = dynamic_pointer_cast<Mob>(*it);
            if (this->mob->shared_from_this() == other) continue;
            if (other->getTarget() != NULL) continue;
            other->setTarget(mob->getLastHurtByMob());
        }
        delete nearby;
    }

    TargetGoal::start();
}

void HurtByTargetGoal::tick() {
    if (mob->getLastHurtByMob() != NULL
        && mob->getLastHurtByMob() != oldHurtByMob) {
        this->start();
    }
}
