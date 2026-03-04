#pragma once

#include <memory>

#include "util/java/Class.h"

#include "TileEntity.h"

class Player;

class EnderChestTileEntity : public TileEntity {
public:
    eINSTANCEOF        GetType() { return eTYPE_ENDERCHESTTILEENTITY; }
    static TileEntity* create() { return new EnderChestTileEntity(); }

public:
    float openness, oOpenness;
    int   openCount;

private:
    int tickInterval;

public:
    EnderChestTileEntity();

    void tick();
    void triggerEvent(int b0, int b1);
    void setRemoved();
    void startOpen();
    void stopOpen();
    bool stillValid(std::shared_ptr<Player> player);

    // 4J Added
    virtual std::shared_ptr<TileEntity> clone();
};
