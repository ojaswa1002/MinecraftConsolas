#pragma once

#include "util/java/Class.h"

#include "Spider.h"

class Entity;
class Level;

class CaveSpider : public Spider {
public:
    eINSTANCEOF    GetType() { return eTYPE_CAVESPIDER; }
    static Entity* create(Level* level) { return new CaveSpider(level); }

public:
    CaveSpider(Level* level);

    virtual int   getMaxHealth();
    virtual float getModelScale();
    virtual bool  doHurtTarget(std::shared_ptr<Entity> target);
    void          finalizeMobSpawn();
};
