#pragma once

#include <string>

#include <windows.h>

#include <mss.h>

class LevelRuleset;

class LevelRules {
public:
    LevelRules();

    void
    addLevelRule(const std::wstring& displayName, PBYTE pbData, DWORD dwLen);
    void addLevelRule(const std::wstring& displayName, LevelRuleset* rootRule);

    void removeLevelRule(LevelRuleset* removing);
};
