#pragma once

#include "world/entity/Creature.h"
#include "world/entity/PathfinderMob.h"

class Level;

class Golem : public PathfinderMob, public Creature {
public:
    Golem(Level* level);

protected:
    virtual void causeFallDamage(float distance);
    virtual int  getAmbientSound();
    virtual int  getHurtSound();
    virtual int  getDeathSound();

public:
    virtual int getAmbientSoundInterval();

protected:
    virtual bool removeWhenFarAway();
};
