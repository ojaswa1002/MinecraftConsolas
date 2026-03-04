#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

#include "win/extraX64.h"
#include "world/level/saveddata/SavedData.h"

class LevelStorage;
class type_info;

class SavedDataStorage {
private:
    LevelStorage* levelStorage;

    typedef std::unordered_map<std::wstring, std::shared_ptr<SavedData>>
                 cacheMapType;
    cacheMapType cache;

    std::vector<std::shared_ptr<SavedData>> savedDatas;

    typedef std::unordered_map<std::wstring, short> uaiMapType;
    uaiMapType                                      usedAuxIds;

public:
    SavedDataStorage(LevelStorage*);
    std::shared_ptr<SavedData>
         get(const type_info& clazz, const std::wstring& id);
    void set(const std::wstring& id, std::shared_ptr<SavedData> data);
    void save();

private:
    void save(std::shared_ptr<SavedData> data);
    void loadAuxValues();

public:
    int getFreeAuxValueFor(const std::wstring& id);

    // 4J Added
    int getAuxValueForMap(
        PlayerUID xuid,
        int       dimension,
        int       centreXC,
        int       centreZC,
        int       scale
    );
};
