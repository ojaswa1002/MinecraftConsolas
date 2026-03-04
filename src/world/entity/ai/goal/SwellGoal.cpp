#include "SwellGoal.h"

#include <cstddef>

#include "world/entity/Mob.h"
#include "world/entity/ai/control/Control.h"
#include "world/entity/ai/navigation/PathNavigation.h"
#include "world/entity/ai/sensing/Sensing.h"
#include "world/entity/monster/Creeper.h"

SwellGoal::SwellGoal(Creeper* creeper) {
    target = std::weak_ptr<Mob>();

    this->creeper = creeper;
    setRequiredControlFlags(Control::MoveControlFlag);
}

bool SwellGoal::canUse() {
    std::shared_ptr<Mob> target = creeper->getTarget();
    return creeper->getSwellDir() > 0
        || (target != NULL && (creeper->distanceToSqr(target) < 3 * 3));
}

void SwellGoal::start() {
    creeper->getNavigation()->stop();
    target = std::weak_ptr<Mob>(creeper->getTarget());
}

void SwellGoal::stop() { target = std::weak_ptr<Mob>(); }

void SwellGoal::tick() {
    if (target.lock() == NULL) {
        creeper->setSwellDir(-1);
        return;
    }

    if (creeper->distanceToSqr(target.lock()) > 7 * 7) {
        creeper->setSwellDir(-1);
        return;
    }

    if (!creeper->getSensing()->canSee(target.lock())) {
        creeper->setSwellDir(-1);
        return;
    }

    creeper->setSwellDir(1);
}
