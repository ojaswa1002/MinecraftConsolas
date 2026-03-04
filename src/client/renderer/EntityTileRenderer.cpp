#include "EntityTileRenderer.h"

#include "client/renderer/tileentity/TileEntityRenderDispatcher.h"
#include "world/level/tile/Tile.h"
#include "world/level/tile/entity/ChestTileEntity.h"
#include "world/level/tile/entity/EnderChestTileEntity.h"

EntityTileRenderer* EntityTileRenderer::instance = new EntityTileRenderer;

EntityTileRenderer::EntityTileRenderer() {
    chest = std::shared_ptr<ChestTileEntity>(new ChestTileEntity());
    enderChest =
        std::shared_ptr<EnderChestTileEntity>(new EnderChestTileEntity());
}

void EntityTileRenderer::render(
    Tile* tile,
    int   data,
    float brightness,
    float alpha,
    bool  setColor,
    bool  useCompiled
) {
    if (tile->id == Tile::enderChest_Id) {
        TileEntityRenderDispatcher::instance
            ->render(enderChest, 0, 0, 0, 0, setColor, alpha, useCompiled);
    } else {
        TileEntityRenderDispatcher::instance
            ->render(chest, 0, 0, 0, 0, setColor, alpha, useCompiled);
    }
}
