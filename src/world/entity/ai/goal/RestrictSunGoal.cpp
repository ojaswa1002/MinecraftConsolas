#include "RestrictSunGoal.h"

#include "world/entity/PathfinderMob.h"
#include "world/entity/ai/navigation/PathNavigation.h"
#include "world/level/Level.h"

RestrictSunGoal::RestrictSunGoal(PathfinderMob* mob) { this->mob = mob; }

bool RestrictSunGoal::canUse() { return mob->level->isDay(); }

void RestrictSunGoal::start() { mob->getNavigation()->setAvoidSun(true); }

void RestrictSunGoal::stop() { mob->getNavigation()->setAvoidSun(false); }
