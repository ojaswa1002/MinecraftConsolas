#pragma once

#include <memory>

#include "Goal.h"

class DoorInfo;
class PathfinderMob;

class MoveIndoorsGoal : public Goal {
private:
    PathfinderMob*          mob;
    std::weak_ptr<DoorInfo> doorInfo;
    int                     insideX, insideZ;

public:
    MoveIndoorsGoal(PathfinderMob* mob);

    bool canUse();
    bool canContinueToUse();
    void start();
    void stop();
};
