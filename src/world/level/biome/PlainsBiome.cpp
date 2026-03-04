#include "PlainsBiome.h"

#include "Biome.h"
#include "BiomeDecorator.h"

PlainsBiome::PlainsBiome(int id) : Biome(id) {
    decorator->treeCount   = -999;
    decorator->flowerCount = 4;
    decorator->grassCount  = 10;
}
