#include "RepairResultSlot.h"

#include <cstddef>

#include "util/java/Random.h"
#include "world/Container.h"
#include "world/entity/player/Abilities.h"
#include "world/entity/player/Player.h"
#include "world/item/ItemInstance.h"
#include "world/level/Level.h"
#include "world/level/tile/LevelEvent.h"
#include "world/level/tile/Tile.h"

#include "RepairMenu.h"

RepairResultSlot::RepairResultSlot(
    RepairMenu*                menu,
    int                        xt,
    int                        yt,
    int                        zt,
    std::shared_ptr<Container> container,
    int                        slot,
    int                        x,
    int                        y
)
: Slot(container, slot, x, y) {
    m_menu   = menu;
    this->xt = xt;
    this->yt = yt;
    this->zt = zt;
}

bool RepairResultSlot::mayPlace(std::shared_ptr<ItemInstance> item) {
    return false;
}

bool RepairResultSlot::mayPickup(std::shared_ptr<Player> player) {
    return (player->abilities.instabuild
            || player->experienceLevel >= m_menu->cost)
        && (m_menu->cost > 0 && hasItem());
}

void RepairResultSlot::onTake(
    std::shared_ptr<Player>       player,
    std::shared_ptr<ItemInstance> carried
) {
    if (!player->abilities.instabuild)
        player->withdrawExperienceLevels(m_menu->cost);
    m_menu->repairSlots->setItem(RepairMenu::INPUT_SLOT, nullptr);
    if (m_menu->repairItemCountCost > 0) {
        std::shared_ptr<ItemInstance> addition =
            m_menu->repairSlots->getItem(RepairMenu::ADDITIONAL_SLOT);
        if (addition != NULL && addition->count > m_menu->repairItemCountCost) {
            addition->count -= m_menu->repairItemCountCost;
            m_menu->repairSlots->setItem(RepairMenu::ADDITIONAL_SLOT, addition);
        } else {
            m_menu->repairSlots->setItem(RepairMenu::ADDITIONAL_SLOT, nullptr);
        }
    } else {
        m_menu->repairSlots->setItem(RepairMenu::ADDITIONAL_SLOT, nullptr);
    }
    m_menu->cost = 0;

    if (!player->abilities.instabuild && !m_menu->level->isClientSide
        && m_menu->level->getTile(xt, yt, zt) == Tile::anvil->id
        && player->getRandom()->nextFloat() < 0.12f) {
        int data = m_menu->level->getData(xt, yt, zt);
        int dir  = data & 0x3;
        int dmg  = data >> 2;

        if (++dmg > 2) {
            m_menu->level->setTile(xt, yt, zt, 0);
            m_menu->level
                ->levelEvent(LevelEvent::SOUND_ANVIL_BROKEN, xt, yt, zt, 0);
        } else {
            m_menu->level->setData(xt, yt, zt, dir | (dmg << 2));
            m_menu->level
                ->levelEvent(LevelEvent::SOUND_ANVIL_USED, xt, yt, zt, 0);
        }
    } else if (!m_menu->level->isClientSide) {
        m_menu->level->levelEvent(LevelEvent::SOUND_ANVIL_USED, xt, yt, zt, 0);
    }
}

bool RepairResultSlot::mayCombine(std::shared_ptr<ItemInstance> second) {
    return false;
}
