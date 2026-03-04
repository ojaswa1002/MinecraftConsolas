#include "StaticCtors.h"

#include "network/packet/Packet.h"
#include "server/level/ServerLevel.h"
#include "stats/GenericStats.h"
#include "stats/Stats.h"
#include "util/SharedConstants.h"
#include "world/entity/EntityIO.h"
#include "world/entity/MobCategory.h"
#include "world/entity/monster/EnderMan.h"
#include "world/entity/monster/PigZombie.h"
#include "world/entity/monster/Skeleton.h"
#include "world/entity/npc/Villager.h"
#include "world/item/HatchetItem.h"
#include "world/item/Item.h"
#include "world/item/PickaxeItem.h"
#include "world/item/ShovelItem.h"
#include "world/item/alchemy/PotionBrewing.h"
#include "world/item/crafting/FurnaceRecipes.h"
#include "world/item/crafting/Recipes.h"
#include "world/item/enchantment/Enchantment.h"
#include "world/level/LevelSettings.h"
#include "world/level/LevelType.h"
#include "world/level/biome/Biome.h"
#include "world/level/chunk/BlockReplacements.h"
#include "world/level/chunk/CompressedTileStorage.h"
#include "world/level/chunk/LevelChunk.h"
#include "world/level/chunk/SparseDataStorage.h"
#include "world/level/chunk/SparseLightStorage.h"
#include "world/level/chunk/storage/McRegionChunkStorage.h"
#include "world/level/levelgen/structure/MineShaftPieces.h"
#include "world/level/levelgen/structure/RandomScatteredLargeFeature.h"
#include "world/level/levelgen/structure/StrongholdFeature.h"
#include "world/level/levelgen/structure/VillageFeature.h"
#include "world/level/levelgen/structure/VillagePieces.h"
#include "world/level/material/Material.h"
#include "world/level/material/MaterialColor.h"
#include "world/level/tile/Tile.h"
#include "world/level/tile/entity/TileEntity.h"

#ifdef _DURANGO
#include "stats/DurangoStats.h"
#else
#include "stats/CommonStats.h"
#endif

void MinecraftWorld_RunStaticCtors() {
    // The ordering of these static ctors can be important. If they are within
    // statement blocks then DO NOT CHANGE the ordering - 4J Stu

    Packet::staticCtor();

    {
        MaterialColor::staticCtor();
        Material::staticCtor();
        Tile::staticCtor();
        HatchetItem::staticCtor();
        PickaxeItem::staticCtor();
        ShovelItem::staticCtor();
        BlockReplacements::staticCtor();
        Biome::staticCtor();
        Item::staticCtor();
        FurnaceRecipes::staticCtor();
        Recipes::staticCtor();
#ifdef _DURANGO
        GenericStats::setInstance(new DurangoStats());
#else
        GenericStats::setInstance(new CommonStats());
        Stats::staticCtor();
#endif
        // Achievements::staticCtor(); // 4J Stu - This is now called from
        // within the Stats::staticCtor()
        Skeleton::staticCtor();
        PigZombie::staticCtor();
        TileEntity::staticCtor();
        EntityIO::staticCtor();
        MobCategory::staticCtor();

        Item::staticInit();
        LevelChunk::staticCtor();

        LevelType::staticCtor();

        MineShaftPieces::staticCtor();
        StrongholdFeature::staticCtor();
        VillagePieces::Smithy::staticCtor();
        VillageFeature::staticCtor();
        RandomScatteredLargeFeature::staticCtor();
    }
    EnderMan::staticCtor();
    PotionBrewing::staticCtor();
    Enchantment::staticCtor();

    SharedConstants::staticCtor();

    ServerLevel::staticCtor();
    SparseLightStorage::staticCtor();
    CompressedTileStorage::staticCtor();
    SparseDataStorage::staticCtor();
    McRegionChunkStorage::staticCtor();
    Villager::staticCtor();
    GameType::staticCtor();
}
