#pragma once

#include <vector>

#include "world/level/biome/Biome.h"

#include "StructureFeature.h"
#include "StructureStart.h"

class ChunkPos;
class Level;
class Random;

class NetherBridgeFeature : public StructureFeature {
private:
    std::vector<Biome::MobSpawnerData*> bridgeEnemies;
    bool                                isSpotSelected;
    ChunkPos*                           netherFortressPos;

public:
    NetherBridgeFeature();
    ~NetherBridgeFeature();
    std::vector<Biome::MobSpawnerData*>* getBridgeEnemies();

protected:
    virtual bool            isFeatureChunk(int x, int z, bool bIsSuperflat);
    virtual StructureStart* createStructureStart(int x, int z);

public:
    void clearCachedBuildings();

private:
    class NetherBridgeStart : public StructureStart {
    public:
        NetherBridgeStart(Level* level, Random* random, int chunkX, int chunkZ);
    };
};
