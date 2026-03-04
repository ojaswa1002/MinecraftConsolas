#include "UIControl_BitmapIcon.h"

#include <type_traits>
#include <utility>

#include "platform/ui/UIScene.h"

#include "UIControl.h"

bool UIControl_BitmapIcon::setupControl(
    UIScene*           scene,
    IggyValuePath*     parent,
    const std::string& controlName
) {
    UIControl::setControlType(UIControl::eBitmapIcon);
    bool success = UIControl::setupControl(scene, parent, controlName);

    // SlotList specific initialisers
    m_funcSetTextureName = registerFastName(L"SetTextureName");

    return success;
}

void UIControl_BitmapIcon::setTextureName(const std::wstring& iconName) {
    IggyDataValue result;
    IggyDataValue value[1];

    IggyStringUTF16 stringVal;
    stringVal.string  = (IggyUTF16*)iconName.c_str();
    stringVal.length  = iconName.length();
    value[0].type     = IGGY_DATATYPE_string_UTF16;
    value[0].string16 = stringVal;
    IggyResult out    = IggyPlayerCallMethodRS(
        m_parentScene->getMovie(),
        &result,
        getIggyValuePath(),
        m_funcSetTextureName,
        1,
        value
    );
}
