#pragma once

#include "util/java/Class.h"
#include "world/entity/Entity.h"

class Level;

class NetherSphere : public Entity {
public:
    eINSTANCEOF GetType() { return eTYPE_NETHER_SPHERE; };

public:
    NetherSphere(Level* level);

protected:
    virtual void defineSynchedData();
    virtual void readAdditionalSaveData(CompoundTag* tag);
    virtual void addAdditonalSaveData(CompoundTag* tag);
};
