#include "RainforestBiome.h"

#include "util/java/Random.h"
#include "world/level/levelgen/feature/BasicTree.h"
#include "world/level/levelgen/feature/TreeFeature.h"

RainforestBiome::RainforestBiome(int id) : Biome(id) {}

Feature* RainforestBiome::getTreeFeature(Random* random) {
    if (random->nextInt(3) == 0) {
        return new BasicTree(false);
    }
    return new TreeFeature(false);
}
