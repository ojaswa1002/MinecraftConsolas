#pragma once

#include <type_traits>
#include <utility>

#include <mss.h>

#include "platform/gamerules/ConsoleGameRulesConstants.h"

#include "GameRuleDefinition.h"

class AABB;

class NamedAreaRuleDefinition : public GameRuleDefinition {
private:
    std::wstring m_name;
    AABB*        m_area;

public:
    NamedAreaRuleDefinition();
    ~NamedAreaRuleDefinition();

    virtual void writeAttributes(DataOutputStream* dos, UINT numAttributes);

    virtual ConsoleGameRules::EGameRuleType getActionType() {
        return ConsoleGameRules::eGameRuleType_NamedArea;
    }

    virtual void addAttribute(
        const std::wstring& attributeName,
        const std::wstring& attributeValue
    );

    AABB*        getArea() { return m_area; }
    std::wstring getName() { return m_name; }
};
