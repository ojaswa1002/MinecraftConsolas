#include "LookAtPlayerGoal.h"

#include <cstddef>

#include "util/java/Random.h"
#include "world/entity/Entity.h"
#include "world/entity/Mob.h"
#include "world/entity/ai/control/Control.h"
#include "world/entity/ai/control/LookControl.h"
#include "world/entity/player/Player.h"
#include "world/level/Level.h"
#include "world/phys/AABB.h"

LookAtPlayerGoal::LookAtPlayerGoal(
    Mob*             mob,
    const type_info& lookAtType,
    float            lookDistance
)
: lookAtType(lookAtType) {
    this->mob          = mob;
    this->lookDistance = lookDistance;
    this->probability  = 0.02f;
    setRequiredControlFlags(Control::LookControlFlag);

    lookTime = 0;
}

LookAtPlayerGoal::LookAtPlayerGoal(
    Mob*             mob,
    const type_info& lookAtType,
    float            lookDistance,
    float            probability
)
: lookAtType(lookAtType) {
    this->mob          = mob;
    this->lookDistance = lookDistance;
    this->probability  = probability;
    setRequiredControlFlags(Control::LookControlFlag);

    lookTime = 0;
}

bool LookAtPlayerGoal::canUse() {
    if (mob->getRandom()->nextFloat() >= probability) return false;
    if (lookAtType == typeid(Player))
        lookAt =
            mob->level->getNearestPlayer(mob->shared_from_this(), lookDistance);
    else
        lookAt = std::weak_ptr<Entity>(mob->level->getClosestEntityOfClass(
            lookAtType,
            mob->bb->grow(lookDistance, 3, lookDistance),
            mob->shared_from_this()
        ));
    return lookAt.lock() != NULL;
}

bool LookAtPlayerGoal::canContinueToUse() {
    if (lookAt.lock() == NULL || !lookAt.lock()->isAlive()) return false;
    if (mob->distanceToSqr(lookAt.lock()) > lookDistance * lookDistance)
        return false;
    return lookTime > 0;
}

void LookAtPlayerGoal::start() {
    lookTime = 40 + mob->getRandom()->nextInt(40);
}

void LookAtPlayerGoal::stop() { lookAt = std::weak_ptr<Entity>(); }

void LookAtPlayerGoal::tick() {
    mob->getLookControl()->setLookAt(
        lookAt.lock()->x,
        lookAt.lock()->y + lookAt.lock()->getHeadHeight(),
        lookAt.lock()->z,
        10,
        mob->getMaxHeadXRot()
    );
    --lookTime;
}
