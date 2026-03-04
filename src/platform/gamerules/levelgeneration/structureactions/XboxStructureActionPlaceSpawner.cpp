#include "XboxStructureActionPlaceSpawner.h"

#include <cstddef>
#include <memory>
#include <type_traits>
#include <utility>

#include "util/java/InputOutputStream/DataOutputStream.h"
#include "world/level/Level.h"
#include "world/level/levelgen/structure/BoundingBox.h"
#include "world/level/levelgen/structure/StructurePiece.h"
#include "world/level/tile/Tile.h"
#include "world/level/tile/entity/MobSpawnerTileEntity.h"

#include "XboxStructureActionPlaceBlock.h"

XboxStructureActionPlaceSpawner::XboxStructureActionPlaceSpawner() {
    m_tile     = Tile::mobSpawner_Id;
    m_entityId = L"Pig";
}

XboxStructureActionPlaceSpawner::~XboxStructureActionPlaceSpawner() {}

void XboxStructureActionPlaceSpawner::writeAttributes(
    DataOutputStream* dos,
    UINT              numAttrs
) {
    XboxStructureActionPlaceBlock::writeAttributes(dos, numAttrs + 1);

    ConsoleGameRules::write(dos, ConsoleGameRules::eGameRuleAttr_entity);
    dos->writeUTF(m_entityId);
}

void XboxStructureActionPlaceSpawner::addAttribute(
    const std::wstring& attributeName,
    const std::wstring& attributeValue
) {
    if (attributeName.compare(L"entity") == 0) {
        m_entityId = attributeValue;
#ifndef _CONTENT_PACKAGE
        wprintf(
            L"XboxStructureActionPlaceSpawner: Adding parameter entity=%ls\n",
            m_entityId.c_str()
        );
#endif
    } else {
        XboxStructureActionPlaceBlock::addAttribute(
            attributeName,
            attributeValue
        );
    }
}

bool XboxStructureActionPlaceSpawner::placeSpawnerInLevel(
    StructurePiece* structure,
    Level*          level,
    BoundingBox*    chunkBB
) {
    int worldX = structure->getWorldX(m_x, m_z);
    int worldY = structure->getWorldY(m_y);
    int worldZ = structure->getWorldZ(m_x, m_z);

    if (chunkBB->isInside(worldX, worldY, worldZ)) {
        if (level->getTileEntity(worldX, worldY, worldZ) != NULL) {
            // Remove the current tile entity
            level->removeTileEntity(worldX, worldY, worldZ);
            level->setTile(worldX, worldY, worldZ, 0);
        }

        level->setTile(worldX, worldY, worldZ, m_tile);
        std::shared_ptr<MobSpawnerTileEntity> entity =
            dynamic_pointer_cast<MobSpawnerTileEntity>(
                level->getTileEntity(worldX, worldY, worldZ)
            );

#ifndef _CONTENT_PACKAGE
        wprintf(
            L"XboxStructureActionPlaceSpawner - placing a %ls spawner at "
            L"(%d,%d,%d)\n",
            m_entityId.c_str(),
            worldX,
            worldY,
            worldZ
        );
#endif
        if (entity != NULL) {
            entity->setEntityId(m_entityId);
        }
        return true;
    }
    return false;
}
