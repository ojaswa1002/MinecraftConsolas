#pragma once

#include <memory>

#include "TargetGoal.h"

class Mob;
class TamableAnimal;

class OwnerHurtTargetGoal : public TargetGoal {
private:
    TamableAnimal*     tameAnimal; // Owner of this goal
    std::weak_ptr<Mob> ownerLastHurt;

public:
    OwnerHurtTargetGoal(TamableAnimal* tameAnimal);

    bool canUse();
    void start();
};
