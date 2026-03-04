#pragma once

#include <memory>

#include "TargetGoal.h"

class Mob;
class TamableAnimal;

class OwnerHurtByTargetGoal : public TargetGoal {
private:
    TamableAnimal*     tameAnimal; // Owner of this goal
    std::weak_ptr<Mob> ownerLastHurtBy;

public:
    OwnerHurtByTargetGoal(TamableAnimal* tameAnimal);

    bool canUse();
    void start();
};
