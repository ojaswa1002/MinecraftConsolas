#pragma once

#include <memory>

#include "TargetGoal.h"

class Mob;

class HurtByTargetGoal : public TargetGoal {
private:
    bool                 alertSameType;
    std::shared_ptr<Mob> oldHurtByMob;

public:
    HurtByTargetGoal(Mob* mob, bool alertSameType);

    bool canUse();
    void start();
    void tick();
};
