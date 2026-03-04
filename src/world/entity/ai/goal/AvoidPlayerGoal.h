#pragma once

#include <memory>

#include "Goal.h"

class Entity;
class Path;
class PathNavigation;
class PathfinderMob;
class type_info;

class AvoidPlayerGoal : public Goal {
private:
    PathfinderMob*        mob; // Owner of this goal
    float                 walkSpeed, sprintSpeed;
    std::weak_ptr<Entity> toAvoid;
    float                 maxDist;
    Path*                 path;
    PathNavigation*       pathNav;
    const type_info&      avoidType;

public:
    AvoidPlayerGoal(
        PathfinderMob*   mob,
        const type_info& avoidType,
        float            maxDist,
        float            walkSpeed,
        float            sprintSpeed
    );
    ~AvoidPlayerGoal();

    virtual bool canUse();
    virtual bool canContinueToUse();
    virtual void start();
    virtual void stop();
    virtual void tick();
};
