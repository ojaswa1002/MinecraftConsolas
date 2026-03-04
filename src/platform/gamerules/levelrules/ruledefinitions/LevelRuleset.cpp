#include "LevelRuleset.h"

#include <cstddef>

#include "platform/localisation/StringTable.h"

#include "CompoundGameRuleDefinition.h"
#include "NamedAreaRuleDefinition.h"

class AABB;

LevelRuleset::LevelRuleset() { m_stringTable = NULL; }

LevelRuleset::~LevelRuleset() {
    for (auto it = m_areas.begin(); it != m_areas.end(); ++it) {
        delete *it;
    }
}

void LevelRuleset::getChildren(std::vector<GameRuleDefinition*>* children) {
    CompoundGameRuleDefinition::getChildren(children);
    for (auto it = m_areas.begin(); it != m_areas.end(); it++)
        children->push_back(*it);
}

GameRuleDefinition*
LevelRuleset::addChild(ConsoleGameRules::EGameRuleType ruleType) {
    GameRuleDefinition* rule = NULL;
    if (ruleType == ConsoleGameRules::eGameRuleType_NamedArea) {
        rule = new NamedAreaRuleDefinition();
        m_areas.push_back((NamedAreaRuleDefinition*)rule);
    } else {
        rule = CompoundGameRuleDefinition::addChild(ruleType);
    }
    return rule;
}

void LevelRuleset::loadStringTable(StringTable* table) {
    m_stringTable = table;
}

LPCWSTR LevelRuleset::getString(const std::wstring& key) {
    if (m_stringTable == NULL) {
        return L"";
    } else {
        return m_stringTable->getString(key);
    }
}

AABB* LevelRuleset::getNamedArea(const std::wstring& areaName) {
    AABB* area = NULL;
    for (auto it = m_areas.begin(); it != m_areas.end(); ++it) {
        if ((*it)->getName().compare(areaName) == 0) {
            area = (*it)->getArea();
            break;
        }
    }
    return area;
}
