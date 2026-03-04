#pragma once

#include <vector>

#include "StructureFeature.h"
#include "StructureStart.h"

class Biome;
class Level;
class Random;

class RandomScatteredLargeFeature : public StructureFeature {
public:
    static void                staticCtor();
    static std::vector<Biome*> allowedBiomes;
    RandomScatteredLargeFeature();

protected:
    virtual bool    isFeatureChunk(int x, int z, bool bIsSuperflat = false);
    StructureStart* createStructureStart(int x, int z);

    class ScatteredFeatureStart : public StructureStart {
    public:
        ScatteredFeatureStart(
            Level*  level,
            Random* random,
            int     chunkX,
            int     chunkZ
        );
    };
};
