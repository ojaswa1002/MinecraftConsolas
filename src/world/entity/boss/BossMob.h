#pragma once

#include <memory>

#include "world/entity/Mob.h"

class BossMobPart;
class DamageSource;
class Level;

class BossMob : public Mob {
protected:
    int maxHealth;

public:
    BossMob(Level* level);

    virtual int  getMaxHealth();
    virtual bool hurt(
        std::shared_ptr<BossMobPart> bossMobPart,
        DamageSource*                source,
        int                          damage
    );
    virtual bool hurt(DamageSource* source, int damage);

protected:
    virtual bool reallyHurt(DamageSource* source, int damage);
};
