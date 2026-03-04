#pragma once

#include "StructureStart.h"

class Level;
class Random;

class MineShaftStart : public StructureStart {
public:
    MineShaftStart(Level* level, Random* random, int chunkX, int chunkZ);
};
