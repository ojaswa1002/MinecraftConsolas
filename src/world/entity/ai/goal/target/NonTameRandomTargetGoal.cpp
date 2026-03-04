#include "NonTameRandomTargetGoal.h"

#include "world/entity/animal/TamableAnimal.h"

class type_info;

NonTameRandomTargetGoal::NonTameRandomTargetGoal(
    TamableAnimal*   mob,
    const type_info& targetType,
    float            within,
    int              randomInterval,
    bool             mustSee
)
: NearestAttackableTargetGoal(
      mob,
      targetType,
      within,
      randomInterval,
      mustSee
  ) {
    this->tamableMob = mob;
}

bool NonTameRandomTargetGoal::canUse() {
    if (tamableMob->isTame()) return false;
    return NearestAttackableTargetGoal::canUse();
}
