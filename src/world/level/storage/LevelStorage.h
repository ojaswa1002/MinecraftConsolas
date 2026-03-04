#pragma once

#include <cstddef>
#include <memory>
#include <vector>

#include "util/console/fileio/ConsoleSavePath.h"
#include "win/extraX64.h"

class ChunkStorage;
class ConsoleSaveFile;
class Dimension;
class LevelData;
class Player;
class PlayerIO;

class LevelStorage {
public:
    static const std::wstring NETHER_FOLDER;
    static const std::wstring ENDER_FOLDER;

    virtual LevelData*    prepareLevel()                           = 0;
    virtual void          checkSession()                           = 0;
    virtual ChunkStorage* createChunkStorage(Dimension* dimension) = 0;
    virtual void          saveLevelData(
                 LevelData*                            levelData,
                 std::vector<std::shared_ptr<Player>>* players
             )                                                  = 0;
    virtual void            saveLevelData(LevelData* levelData) = 0;
    virtual PlayerIO*       getPlayerIO()                       = 0;
    virtual void            closeAll()                          = 0;
    virtual ConsoleSavePath getDataFile(const std::wstring& id) = 0;
    virtual std::wstring    getLevelId()                        = 0;

public:
    virtual ConsoleSaveFile* getSaveFile() { return NULL; }
    virtual void             flushSaveFile(bool autosave) {}

    // 4J Added
    virtual int getAuxValueForMap(
        PlayerUID xuid,
        int       dimension,
        int       centreXC,
        int       centreZC,
        int       scale
    ) {
        return 0;
    }
};
