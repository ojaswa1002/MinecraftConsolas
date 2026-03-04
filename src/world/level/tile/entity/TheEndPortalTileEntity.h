#pragma once

#include "util/java/Class.h"

#include "TileEntity.h"

class TheEndPortalTileEntity : public TileEntity {
public:
    eINSTANCEOF        GetType() { return eTYPE_THEENDPORTALTILEENTITY; }
    static TileEntity* create() { return new TheEndPortalTileEntity(); }

    // 4J Added
    std::shared_ptr<TileEntity> clone();
};
