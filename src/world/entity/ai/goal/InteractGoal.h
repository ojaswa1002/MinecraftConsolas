#pragma once

#include "LookAtPlayerGoal.h"

class Mob;
class type_info;

class InteractGoal : public LookAtPlayerGoal {
public:
    InteractGoal(Mob* mob, const type_info& lookAtType, float lookDistance);
    InteractGoal(
        Mob*             mob,
        const type_info& lookAtType,
        float            lookDistance,
        float            probability
    );
};
