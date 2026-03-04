#pragma once

#include <memory>

#include "Goal.h"

class Creeper;
class Mob;

class SwellGoal : public Goal {
private:
    Creeper*           creeper;
    std::weak_ptr<Mob> target;

public:
    SwellGoal(Creeper* creeper);

    bool canUse();
    void start();
    void stop();
    void tick();
};
