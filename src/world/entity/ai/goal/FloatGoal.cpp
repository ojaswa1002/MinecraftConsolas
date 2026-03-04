#include "FloatGoal.h"

#include "util/java/Random.h"
#include "world/entity/Mob.h"
#include "world/entity/ai/control/Control.h"
#include "world/entity/ai/control/JumpControl.h"
#include "world/entity/ai/navigation/PathNavigation.h"

FloatGoal::FloatGoal(Mob* mob) {
    this->mob = mob;
    setRequiredControlFlags(Control::JumpControlFlag);
    mob->getNavigation()->setCanFloat(true);
}

bool FloatGoal::canUse() { return (mob->isInWater() || mob->isInLava()); }

void FloatGoal::tick() {
    if (mob->getRandom()->nextFloat() < 0.8f) mob->getJumpControl()->jump();
}
