#include "XuiCraftingTask.h"

#include "platform/tutorial/Tutorial.h"
#include "platform/ui/scenes/ingame_menu_screens/UIScene_CraftingMenu.h"

bool XuiCraftingTask::isCompleted() {
#ifndef __PSVITA__
    // This doesn't seem to work
    // IUIScene_CraftingMenu *craftScene =
    // reinterpret_cast<IUIScene_CraftingMenu *>(tutorial->getScene());
#ifdef _XBOX
    CXuiSceneCraftingPanel* craftScene =
        (CXuiSceneCraftingPanel*)(tutorial->getScene());
#else
    UIScene_CraftingMenu* craftScene =
        reinterpret_cast<UIScene_CraftingMenu*>(tutorial->getScene());
#endif

    bool completed = false;

    switch (m_type) {
    case e_Crafting_SelectGroup:
        if (craftScene != NULL && craftScene->getCurrentGroup() == m_group) {
            completed = true;
        }
        break;
    case e_Crafting_SelectItem:
        if (craftScene != NULL && craftScene->isItemSelected(m_item)) {
            completed = true;
        }
        break;
    }

    return completed;
#else
    return true;
#endif
}
