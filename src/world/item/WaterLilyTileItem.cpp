#include "WaterLilyTileItem.h"

#include <cstddef>
#include <memory>

#include "world/entity/player/Abilities.h"
#include "world/entity/player/Player.h"
#include "world/level/Level.h"
#include "world/level/material/Material.h"
#include "world/level/tile/Tile.h"
#include "world/phys/HitResult.h"

#include "ItemInstance.h"

WaterLilyTileItem::WaterLilyTileItem(int id) : ColoredTileItem(id, false) {}

bool WaterLilyTileItem::TestUse(Level* level, std::shared_ptr<Player> player) {
    HitResult* hr = getPlayerPOVHitResult(level, player, true);
    if (hr == NULL) return false;

    if (hr->type == HitResult::TILE) {
        int xt = hr->x;
        int yt = hr->y;
        int zt = hr->z;
        delete hr;
        if (!level->mayInteract(player, xt, yt, zt, 0)) {
            return false;
        }
        if (!player->mayBuild(xt, yt, zt)) return false;

        if (level->getMaterial(xt, yt, zt) == Material::water
            && level->getData(xt, yt, zt) == 0
            && level->isEmptyTile(xt, yt + 1, zt)) {
            return true;
        }
    } else {
        delete hr;
    }
    return false;
}

std::shared_ptr<ItemInstance> WaterLilyTileItem::use(
    std::shared_ptr<ItemInstance> itemInstance,
    Level*                        level,
    std::shared_ptr<Player>       player
) {
    HitResult* hr = getPlayerPOVHitResult(level, player, true);
    if (hr == NULL) return itemInstance;

    if (hr->type == HitResult::TILE) {
        int xt = hr->x;
        int yt = hr->y;
        int zt = hr->z;
        delete hr;
        if (!level->mayInteract(player, xt, yt, zt, 0)) {
            return itemInstance;
        }
        if (!player->mayBuild(xt, yt, zt)) return itemInstance;

        if (level->getMaterial(xt, yt, zt) == Material::water
            && level->getData(xt, yt, zt) == 0
            && level->isEmptyTile(xt, yt + 1, zt)) {
            level->setTile(xt, yt + 1, zt, Tile::waterLily->id);
            if (!player->abilities.instabuild) {
                itemInstance->count--;
            }
        }
    } else {
        delete hr;
    }
    return itemInstance;
}

int WaterLilyTileItem::getColor(int data, int spriteLayer) {
    return Tile::waterLily->getColor(data);
}
