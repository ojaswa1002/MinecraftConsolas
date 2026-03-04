#pragma once

#include "platform/gamerules/levelgeneration/LevelGenerationOptions.h"

#include "DLCFile.h"

class DLCGameRules : public DLCFile {
public:
    DLCGameRules(DLCManager::EDLCType type, const std::wstring& path)
    : DLCFile(type, path) {}
};
