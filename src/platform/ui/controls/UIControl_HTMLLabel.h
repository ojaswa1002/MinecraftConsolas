#pragma once

#include <iggy.h>
#include <rrcore.h>

#include "UIControl_Base.h"
#include "UIControl_Label.h"

class UIControl_HTMLLabel : public UIControl_Label {
private:
    IggyName m_funcStartAutoScroll, m_funcTouchScroll, m_funcGetRealWidth,
        m_funcGetRealHeight;

public:
    UIControl_HTMLLabel();

    virtual bool setupControl(
        UIScene*           scene,
        IggyValuePath*     parent,
        const std::string& controlName
    );

    void         startAutoScroll();
    virtual void ReInit();

    using UIControl_Base::setLabel;
    void setLabel(const std::string& label);

    virtual void SetupTouch();

    virtual void TouchScroll(S32 iY, bool bActive);

    S32 GetRealWidth();
    S32 GetRealHeight();
};
