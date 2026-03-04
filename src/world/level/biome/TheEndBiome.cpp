#include "TheEndBiome.h"

#include <vector>

#include "util/java/Class.h"
#include "win/extraX64.h"
#include "world/level/tile/Tile.h"

#include "TheEndBiomeDecorator.h"

TheEndBiome::TheEndBiome(int id) : Biome(id) {
    enemies.clear();
    friendlies.clear();
    friendlies_chicken.clear(); // 4J added
    friendlies_wolf.clear();    // 4J added
    waterFriendlies.clear();

    enemies.push_back(new MobSpawnerData(eTYPE_ENDERMAN, 10, 4, 4));
    topMaterial    = (byte)Tile::dirt_Id;
    this->material = (byte)Tile::dirt_Id;

    decorator = new TheEndBiomeDecorator(this);
}

// 4J Stu - Don't need override
// int TheEndBiome::getSkyColor(float temp)
//{
//	return 0x000000;
//}
