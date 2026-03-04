#include "ForestBiome.h"

#include <vector>

#include "util/java/Class.h"
#include "util/java/Random.h"
#include "world/level/levelgen/feature/BasicTree.h"
#include "world/level/levelgen/feature/BirchFeature.h"
#include "world/level/levelgen/feature/TreeFeature.h"

#include "BiomeDecorator.h"

ForestBiome::ForestBiome(int id) : Biome(id) {
    friendlies_wolf.push_back(
        new MobSpawnerData(eTYPE_WOLF, 5, 4, 4)
    ); // 4J - moved to their own category
    decorator->treeCount  = 10;
    decorator->grassCount = 2;
}

Feature* ForestBiome::getTreeFeature(Random* random) {
    if (random->nextInt(5) == 0) {
        return new BirchFeature(
            false
        ); // 4J used to return member birchTree, now returning newly created
           // object so that caller can be consistently resposible for cleanup
    }
    if (random->nextInt(10) == 0) {
        return new BasicTree(
            false
        ); // 4J used to return member fancyTree, now returning newly created
           // object so that caller can be consistently resposible for cleanup
    }
    return new TreeFeature(
        false
    ); // 4J used to return member normalTree, now returning newly created
       // object so that caller can be consistently resposible for cleanup
}
