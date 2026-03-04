#include "MockedLevelStorage.h"

#include <type_traits>
#include <utility>

#include "util/console/fileio/ConsoleSavePath.h"

LevelData* MockedLevelStorage::prepareLevel() { return NULL; }

void MockedLevelStorage::checkSession() {}

ChunkStorage* MockedLevelStorage::createChunkStorage(Dimension* dimension) {
    return NULL;
}

void MockedLevelStorage::saveLevelData(
    LevelData*                            levelData,
    std::vector<std::shared_ptr<Player>>* players
) {}

void MockedLevelStorage::saveLevelData(LevelData* levelData) {}

PlayerIO* MockedLevelStorage::getPlayerIO() { return NULL; }

void MockedLevelStorage::closeAll() {}

ConsoleSavePath MockedLevelStorage::getDataFile(const std::wstring& id) {
    return ConsoleSavePath(std::wstring(L""));
}

std::wstring MockedLevelStorage::getLevelId() { return L"none"; }
