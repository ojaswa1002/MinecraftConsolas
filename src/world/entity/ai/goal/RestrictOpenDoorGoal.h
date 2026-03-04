#pragma once

#include <memory>

#include "Goal.h"

class DoorInfo;
class PathfinderMob;

class RestrictOpenDoorGoal : public Goal {
private:
    PathfinderMob*          mob;
    std::weak_ptr<DoorInfo> doorInfo;

public:
    RestrictOpenDoorGoal(PathfinderMob* mob);

    virtual bool canUse();
    virtual bool canContinueToUse();
    virtual void start();
    virtual void stop();
    virtual void tick();
};
