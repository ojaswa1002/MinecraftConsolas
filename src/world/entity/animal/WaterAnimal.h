#pragma once

#include "world/entity/Creature.h"
#include "world/entity/PathfinderMob.h"

class Level;

class WaterAnimal : public PathfinderMob, public Creature {
public:
    WaterAnimal(Level* level);
    virtual bool isWaterMob();
    virtual bool canSpawn();
    virtual int  getAmbientSoundInterval();

protected:
    virtual bool removeWhenFarAway();
    virtual int  getExperienceReward(std::shared_ptr<Player> killedBy);
};
