#pragma once

#include "Tile.h"

class StoneTile : public Tile {
public:
    StoneTile(int id);
    virtual int getResource(int data, Random* random, int playerBonusLevel);
};
