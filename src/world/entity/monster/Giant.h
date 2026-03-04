#pragma once

#include "util/java/Class.h"

#include "Monster.h"

class Entity;
class Level;

class Giant : public Monster {
public:
    eINSTANCEOF    GetType() { return eTYPE_GIANT; }
    static Entity* create(Level* level) { return new Giant(level); }

    Giant(Level* level);

    int           getMaxHealth();
    virtual float getWalkTargetValue(int x, int y, int z);
};
