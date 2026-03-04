#pragma once

#include <type_traits>
#include <utility>

#include <rrcore.h>

#include "platform/ui/UIScene.h"
#include "platform/ui/all_platforms/UIEnums.h"
#include "platform/ui/controls/UIControl_Button.h"
#include "platform/ui/controls/UIControl_Label.h"

class UILayer;

class UIScene_DeathMenu : public UIScene {
private:
    enum EControls { eControl_Respawn, eControl_ExitGame };

    bool m_bIgnoreInput;

    UIControl_Button m_buttonRespawn, m_buttonExitGame;
    UIControl_Label  m_labelTitle;
    UI_BEGIN_MAP_ELEMENTS_AND_NAMES(UIScene)
    UI_MAP_ELEMENT(m_buttonRespawn, "Respawn")
    UI_MAP_ELEMENT(m_buttonExitGame, "ExitGame")
    UI_MAP_ELEMENT(m_labelTitle, "Title")
    UI_END_MAP_ELEMENTS_AND_NAMES()
public:
    UIScene_DeathMenu(int iPad, void* initData, UILayer* parentLayer);
    virtual ~UIScene_DeathMenu();

    virtual EUIScene getSceneType() { return eUIScene_DeathMenu; }
    virtual void     updateTooltips();

protected:
    // TODO: This should be pure virtual in this class
    virtual std::wstring getMoviePath();

public:
    // INPUT
    virtual void handleInput(
        int   iPad,
        int   key,
        bool  repeat,
        bool  pressed,
        bool  released,
        bool& handled
    );

protected:
    void handlePress(F64 controlId, F64 childId);

#ifdef _DURANGO
    virtual long long getDefaultGtcButtons() { return 0; }
#endif
};
