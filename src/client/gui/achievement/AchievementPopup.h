#pragma once

#include "client/gui/GuiComponent.h"

class Achievement;
class ItemRenderer;
class Minecraft;

class AchievementPopup : public GuiComponent {
private:
    Minecraft* mc;
    int        width, height;

    std::wstring  title;
    std::wstring  desc;
    Achievement*  ach;
    std::int64_t  startTime;
    ItemRenderer* ir;
    bool          isHelper;

public:
    AchievementPopup(Minecraft* mc);
    void popup(Achievement* ach);
    void permanent(Achievement* ach);

private:
    void prepareWindow();

public:
    void render();
};
