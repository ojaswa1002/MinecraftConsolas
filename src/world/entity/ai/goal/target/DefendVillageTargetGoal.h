#pragma once

#include <memory>

#include "TargetGoal.h"

class Mob;
class VillagerGolem;

class DefendVillageTargetGoal : public TargetGoal {
private:
    VillagerGolem*     golem; // Owner of this goal
    std::weak_ptr<Mob> potentialTarget;

public:
    DefendVillageTargetGoal(VillagerGolem* golem);

    bool canUse();
    void start();
};
