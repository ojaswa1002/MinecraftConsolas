#pragma once

#include <memory>
#include <vector>

#include "Goal.h"

class DoorInfo;
class Path;
class PathfinderMob;
class Village;

class MoveThroughVillageGoal : public Goal {
private:
    PathfinderMob*                       mob;
    float                                speed;
    Path*                                path;
    std::weak_ptr<DoorInfo>              doorInfo;
    bool                                 onlyAtNight;
    std::vector<std::weak_ptr<DoorInfo>> visited;

public:
    MoveThroughVillageGoal(PathfinderMob* mob, float speed, bool onlyAtNight);
    ~MoveThroughVillageGoal();

    virtual bool canUse();
    virtual bool canContinueToUse();
    virtual void start();
    virtual void stop();

private:
    std::shared_ptr<DoorInfo> getNextDoorInfo(std::shared_ptr<Village> village);
    bool                      hasVisited(std::shared_ptr<DoorInfo> di);
    void                      updateVisited();
};
