#include "PanicGoal.h"

#include <cstddef>
#include <memory>

#include "world/entity/PathfinderMob.h"
#include "world/entity/ai/control/Control.h"
#include "world/entity/ai/navigation/PathNavigation.h"
#include "world/entity/ai/util/RandomPos.h"
#include "world/phys/Vec3.h"

PanicGoal::PanicGoal(PathfinderMob* mob, float speed) {
    this->mob   = mob;
    this->speed = speed;
    setRequiredControlFlags(Control::MoveControlFlag);
}

bool PanicGoal::canUse() {
    if (mob->getLastHurtByMob() == NULL) return false;
    Vec3* pos = RandomPos::getPos(
        dynamic_pointer_cast<PathfinderMob>(mob->shared_from_this()),
        5,
        4
    );
    if (pos == NULL) return false;
    posX = pos->x;
    posY = pos->y;
    posZ = pos->z;
    return true;
}

void PanicGoal::start() {
    mob->getNavigation()->moveTo(posX, posY, posZ, speed);
}

bool PanicGoal::canContinueToUse() { return !mob->getNavigation()->isDone(); }
