#pragma once

#include <vector>

#include <mss.h>

#include "platform/gamerules/ConsoleGameRulesConstants.h"
#include "platform/gamerules/levelrules/ruledefinitions/GameRuleDefinition.h"
#include "world/level/levelgen/structure/StructurePiece.h"

class BoundingBox;
class ConsoleGenerateStructureAction;
class Level;
class XboxStructureActionPlaceContainer;

class ConsoleGenerateStructure : public GameRuleDefinition,
                                 public StructurePiece {
private:
    int                                          m_x, m_y, m_z;
    std::vector<ConsoleGenerateStructureAction*> m_actions;
    int                                          m_dimension;

public:
    ConsoleGenerateStructure();

    virtual ConsoleGameRules::EGameRuleType getActionType() {
        return ConsoleGameRules::eGameRuleType_GenerateStructure;
    }

    virtual void getChildren(std::vector<GameRuleDefinition*>* children);
    virtual GameRuleDefinition*
    addChild(ConsoleGameRules::EGameRuleType ruleType);

    virtual void writeAttributes(DataOutputStream* dos, UINT numAttrs);
    virtual void addAttribute(
        const std::wstring& attributeName,
        const std::wstring& attributeValue
    );

    // StructurePiece
    virtual BoundingBox* getBoundingBox();
    virtual bool
    postProcess(Level* level, Random* random, BoundingBox* chunkBB);

    void createContainer(
        XboxStructureActionPlaceContainer* action,
        Level*                             level,
        BoundingBox*                       chunkBB
    );

    bool checkIntersects(int x0, int y0, int z0, int x1, int y1, int z1);

    virtual int getMinY();
};
