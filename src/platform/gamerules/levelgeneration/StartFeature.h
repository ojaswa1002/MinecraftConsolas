#pragma once

#include <mss.h>

#include "platform/gamerules/ConsoleGameRulesConstants.h"
#include "platform/gamerules/levelrules/ruledefinitions/GameRuleDefinition.h"
#include "world/level/levelgen/structure/StructureFeature.h"

class StartFeature : public GameRuleDefinition {
private:
    int                             m_chunkX, m_chunkZ;
    StructureFeature::EFeatureTypes m_feature;

public:
    StartFeature();

    virtual ConsoleGameRules::EGameRuleType getActionType() {
        return ConsoleGameRules::eGameRuleType_StartFeature;
    }

    virtual void writeAttributes(DataOutputStream* dos, UINT numAttrs);
    virtual void addAttribute(
        const std::wstring& attributeName,
        const std::wstring& attributeValue
    );

    bool isFeatureChunk(
        int                             chunkX,
        int                             chunkZ,
        StructureFeature::EFeatureTypes feature
    );
};
