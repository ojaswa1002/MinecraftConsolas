#include "TheEndPortalTileEntity.h"

#include <memory>

// 4J Added
std::shared_ptr<TileEntity> TheEndPortalTileEntity::clone() {
    std::shared_ptr<TheEndPortalTileEntity> result =
        std::shared_ptr<TheEndPortalTileEntity>(new TheEndPortalTileEntity());
    TileEntity::clone(result);
    return result;
}
