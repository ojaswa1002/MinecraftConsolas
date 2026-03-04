#pragma once

#include <memory>

#include "util/java/Class.h"

#include "Throwable.h"

class Entity;
class Level;
class Mob;

class ThrownExpBottle : public Throwable {
public:
    eINSTANCEOF    GetType() { return eTYPE_THROWNEXPBOTTLE; }
    static Entity* create(Level* level) { return new ThrownExpBottle(level); }

public:
    ThrownExpBottle(Level* level);
    ThrownExpBottle(Level* level, std::shared_ptr<Mob> mob);
    ThrownExpBottle(Level* level, double x, double y, double z);

protected:
    virtual float getGravity();
    virtual float getThrowPower();
    virtual float getThrowUpAngleOffset();
    virtual void  onHit(HitResult* res);
};
