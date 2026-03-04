#include "MoveTowardsRestrictionGoal.h"

#include <cstddef>
#include <memory>

#include "world/Pos.h"
#include "world/entity/PathfinderMob.h"
#include "world/entity/ai/control/Control.h"
#include "world/entity/ai/navigation/PathNavigation.h"
#include "world/entity/ai/util/RandomPos.h"
#include "world/phys/Vec3.h"

MoveTowardsRestrictionGoal::MoveTowardsRestrictionGoal(
    PathfinderMob* mob,
    float          speed
) {
    wantedX = wantedY = wantedZ = 0.0;

    this->mob   = mob;
    this->speed = speed;
    setRequiredControlFlags(Control::MoveControlFlag);
}

bool MoveTowardsRestrictionGoal::canUse() {
    if (mob->isWithinRestriction()) return false;
    Pos*  towards = mob->getRestrictCenter();
    Vec3* pos     = RandomPos::getPosTowards(
        dynamic_pointer_cast<PathfinderMob>(mob->shared_from_this()),
        16,
        7,
        Vec3::newTemp(towards->x, towards->y, towards->z)
    );
    if (pos == NULL) return false;
    wantedX = pos->x;
    wantedY = pos->y;
    wantedZ = pos->z;
    return true;
}

bool MoveTowardsRestrictionGoal::canContinueToUse() {
    return !mob->getNavigation()->isDone();
}

void MoveTowardsRestrictionGoal::start() {
    mob->getNavigation()->moveTo(wantedX, wantedY, wantedZ, speed);
}
