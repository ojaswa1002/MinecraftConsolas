#include "ServerLevelListener.h"

#include <cstddef>
#include <memory>
#include <vector>

#include "network/packet/LevelEventPacket.h"
#include "network/packet/LevelSoundPacket.h"
#include "network/packet/TileDestructionPacket.h"
#include "server/MinecraftServer.h"
#include "server/PlayerList.h"
#include "server/network/PlayerConnection.h"
#include "util/MemSect.h"
#include "win/Windows64_App.h"
#include "world/entity/Entity.h"
#include "world/entity/player/Player.h"
#include "world/level/dimension/Dimension.h"

#include "EntityTracker.h"
#include "PlayerChunkMap.h"
#include "ServerLevel.h"
#include "ServerPlayer.h"

ServerLevelListener::ServerLevelListener(
    MinecraftServer* server,
    ServerLevel*     level
) {
    this->server = server;
    this->level  = level;
}

// 4J removed -
/*
void ServerLevelListener::addParticle(const std::wstring& name, double x, double
y, double z, double xa, double ya, double za)
{
}
*/

void ServerLevelListener::addParticle(
    ePARTICLE_TYPE name,
    double         x,
    double         y,
    double         z,
    double         xa,
    double         ya,
    double         za
) {}

void ServerLevelListener::allChanged() {}

void ServerLevelListener::entityAdded(std::shared_ptr<Entity> entity) {
    MemSect(10);
    level->getTracker()->addEntity(entity);
    MemSect(0);
}

void ServerLevelListener::entityRemoved(std::shared_ptr<Entity> entity) {
    level->getTracker()->removeEntity(entity);
}

// 4J added
void ServerLevelListener::playerRemoved(std::shared_ptr<Entity> entity) {
    std::shared_ptr<ServerPlayer> player =
        std::dynamic_pointer_cast<ServerPlayer>(entity);
    player->getLevel()->getTracker()->removePlayer(entity);
}

void ServerLevelListener::playSound(
    int    iSound,
    double x,
    double y,
    double z,
    float  volume,
    float  pitch,
    float  fClipSoundDist
) {
    if (iSound < 0) {
        app.DebugPrintf(
            "ServerLevelListener received request for sound less than 0, so "
            "ignoring\n"
        );
    } else {
        // 4J-PB - I don't want to broadcast player sounds to my local machine,
        // since we're already playing these in the LevelRenderer::playSound.
        // The PC version does seem to do this and the result is I can stop
        // walking , and then I'll hear my footstep sound with a delay
        server->getPlayers()->broadcast(
            x,
            y,
            z,
            volume > 1 ? 16 * volume : 16,
            level->dimension->id,
            std::shared_ptr<LevelSoundPacket>(
                new LevelSoundPacket(iSound, x, y, z, volume, pitch)
            )
        );
    }
}

void ServerLevelListener::playSound(
    std::shared_ptr<Entity> entity,
    int                     iSound,
    double                  x,
    double                  y,
    double                  z,
    float                   volume,
    float                   pitch,
    float                   fClipSoundDist
) {
    if (iSound < 0) {
        app.DebugPrintf(
            "ServerLevelListener received request for sound less than 0, so "
            "ignoring\n"
        );
    } else {
        // 4J-PB - I don't want to broadcast player sounds to my local machine,
        // since we're already playing these in the LevelRenderer::playSound.
        // The PC version does seem to do this and the result is I can stop
        // walking , and then I'll hear my footstep sound with a delay
        std::shared_ptr<Player> player =
            std::dynamic_pointer_cast<Player>(entity);
        server->getPlayers()->broadcast(
            player,
            x,
            y,
            z,
            volume > 1 ? 16 * volume : 16,
            level->dimension->id,
            std::shared_ptr<LevelSoundPacket>(
                new LevelSoundPacket(iSound, x, y, z, volume, pitch)
            )
        );
    }
}

void ServerLevelListener::setTilesDirty(
    int    x0,
    int    y0,
    int    z0,
    int    x1,
    int    y1,
    int    z1,
    Level* level
) {}

void ServerLevelListener::skyColorChanged() {}

void ServerLevelListener::tileChanged(int x, int y, int z) {
    level->getChunkMap()->tileChanged(x, y, z);
}

void ServerLevelListener::tileLightChanged(int x, int y, int z) {}

void ServerLevelListener::playStreamingMusic(
    const std::wstring& name,
    int                 x,
    int                 y,
    int                 z
) {}

void ServerLevelListener::levelEvent(
    std::shared_ptr<Player> source,
    int                     type,
    int                     x,
    int                     y,
    int                     z,
    int                     data
) {
    server->getPlayers()->broadcast(
        source,
        x,
        y,
        z,
        64,
        level->dimension->id,
        std::shared_ptr<LevelEventPacket>(
            new LevelEventPacket(type, x, y, z, data)
        )
    );
}

void ServerLevelListener::destroyTileProgress(
    int id,
    int x,
    int y,
    int z,
    int progress
) {
    // for (ServerPlayer p : server->getPlayers()->players)
    for (auto it = server->getPlayers()->players.begin();
         it != server->getPlayers()->players.end();
         ++it) {
        std::shared_ptr<ServerPlayer> p = *it;
        if (p == NULL || p->level != level || p->entityId == id) continue;
        double xd = (double)x - p->x;
        double yd = (double)y - p->y;
        double zd = (double)z - p->z;

        if (xd * xd + yd * yd + zd * zd < 32 * 32) {
            p->connection->send(
                std::shared_ptr<TileDestructionPacket>(
                    new TileDestructionPacket(id, x, y, z, progress)
                )
            );
        }
    }
}
