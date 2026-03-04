#pragma once

#include <memory>

#include "Goal.h"

class Mob;
class Villager;

class PlayGoal : public Goal {
private:
    Villager*          mob;
    std::weak_ptr<Mob> followFriend;
    float              speed;
    double             wantedX, wantedY, wantedZ;
    int                playTime;

public:
    PlayGoal(Villager* mob, float speed);

    virtual bool canUse();
    virtual bool canContinueToUse();
    virtual void start();
    virtual void stop();
    virtual void tick();
};
