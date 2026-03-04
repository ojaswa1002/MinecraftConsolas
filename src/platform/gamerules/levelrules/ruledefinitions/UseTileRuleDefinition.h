#pragma once

#include <mss.h>

#include "platform/gamerules/ConsoleGameRulesConstants.h"
#include "world/Pos.h"

#include "GameRuleDefinition.h"

class UseTileRuleDefinition : public GameRuleDefinition {
private:
    // These values should map directly to the xsd definition for this Rule
    int  m_tileId;
    bool m_useCoords;
    Pos  m_coordinates;

public:
    UseTileRuleDefinition();

    ConsoleGameRules::EGameRuleType getActionType() {
        return ConsoleGameRules::eGameRuleType_UseTileRule;
    }

    virtual void writeAttributes(DataOutputStream* dos, UINT numAttributes);
    virtual void addAttribute(
        const std::wstring& attributeName,
        const std::wstring& attributeValue
    );

    virtual bool onUseTile(GameRule* rule, int tileId, int x, int y, int z);
};
