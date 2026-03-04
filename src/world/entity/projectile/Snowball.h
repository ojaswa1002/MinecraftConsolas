#pragma once

#include <memory>

#include "util/java/Class.h"

#include "Throwable.h"

class Entity;
class Level;
class Mob;

class Snowball : public Throwable {
public:
    eINSTANCEOF    GetType() { return eTYPE_SNOWBALL; }
    static Entity* create(Level* level) { return new Snowball(level); }

private:
    void _init();

public:
    Snowball(Level* level);
    Snowball(Level* level, std::shared_ptr<Mob> mob);
    Snowball(Level* level, double x, double y, double z);

protected:
    virtual void onHit(HitResult* res);
};
