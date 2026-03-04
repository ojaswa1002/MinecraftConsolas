#include "OwnerHurtByTargetGoal.h"

#include <cstddef>

#include "world/entity/Mob.h"
#include "world/entity/animal/TamableAnimal.h"

OwnerHurtByTargetGoal::OwnerHurtByTargetGoal(TamableAnimal* tameAnimal)
: TargetGoal(tameAnimal, 32, false) {
    this->tameAnimal = tameAnimal;
    setRequiredControlFlags(TargetGoal::TargetFlag);
}

bool OwnerHurtByTargetGoal::canUse() {
    if (!tameAnimal->isTame()) return false;
    std::shared_ptr<Mob> owner = tameAnimal->getOwner();
    if (owner == NULL) return false;
    ownerLastHurtBy = std::weak_ptr<Mob>(owner->getLastHurtByMob());
    return canAttack(ownerLastHurtBy.lock(), false);
}

void OwnerHurtByTargetGoal::start() {
    mob->setTarget(ownerLastHurtBy.lock());
    TargetGoal::start();
}
