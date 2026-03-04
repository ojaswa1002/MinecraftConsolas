#include "OwnerHurtTargetGoal.h"

#include <cstddef>

#include "world/entity/Mob.h"
#include "world/entity/animal/TamableAnimal.h"

OwnerHurtTargetGoal::OwnerHurtTargetGoal(TamableAnimal* tameAnimal)
: TargetGoal(tameAnimal, 32, false) {
    this->tameAnimal = tameAnimal;
    setRequiredControlFlags(TargetGoal::TargetFlag);
}

bool OwnerHurtTargetGoal::canUse() {
    if (!tameAnimal->isTame()) return false;
    std::shared_ptr<Mob> owner = tameAnimal->getOwner();
    if (owner == NULL) return false;
    ownerLastHurt = std::weak_ptr<Mob>(owner->getLastHurtMob());
    return canAttack(ownerLastHurt.lock(), false);
}

void OwnerHurtTargetGoal::start() {
    mob->setTarget(ownerLastHurt.lock());
    TargetGoal::start();
}
