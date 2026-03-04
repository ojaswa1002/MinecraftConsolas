#include "UIControl_Cursor.h"

#include "UIControl.h"
#include "UIControl_Base.h"

UIControl_Cursor::UIControl_Cursor() {}

bool UIControl_Cursor::setupControl(
    UIScene*           scene,
    IggyValuePath*     parent,
    const std::string& controlName
) {
    UIControl::setControlType(UIControl::eCursor);
    bool success = UIControl_Base::setupControl(scene, parent, controlName);

    // Label specific initialisers

    return success;
}
