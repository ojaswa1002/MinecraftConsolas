#pragma once

#include "HeavyTile.h"

class GravelTile : public HeavyTile {
public:
    GravelTile(int type);
    virtual int getResource(int data, Random* random, int playerBonusLevel);
};
