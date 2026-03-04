#include "TutorialMode.h"

#include <memory>

#include "client/Minecraft.h"
#include "client/multiplayer/MultiPlayerGameMode.h"
#include "client/multiplayer/MultiPlayerLevel.h"
#include "client/multiplayer/MultiPlayerLocalPlayer.h"
#include "world/entity/player/Inventory.h"
#include "world/item/ItemInstance.h"
#include "world/level/tile/Tile.h"

#include "Tutorial.h"
#include "TutorialMode.h"

class ClientConnection;

TutorialMode::TutorialMode(
    int               iPad,
    Minecraft*        minecraft,
    ClientConnection* connection
)
: MultiPlayerGameMode(minecraft, connection),
  m_iPad(iPad) {}

TutorialMode::~TutorialMode() {
    if (tutorial != NULL) delete tutorial;
}

void TutorialMode::startDestroyBlock(int x, int y, int z, int face) {
    if (!tutorial->m_allTutorialsComplete) {
        int t = minecraft->level->getTile(x, y, z);
        tutorial->startDestroyBlock(
            minecraft->player->inventory->getSelected(),
            Tile::tiles[t]
        );
    }
    MultiPlayerGameMode::startDestroyBlock(x, y, z, face);
}

bool TutorialMode::destroyBlock(int x, int y, int z, int face) {
    if (!tutorial->m_allTutorialsComplete) {
        int t = minecraft->level->getTile(x, y, z);
        tutorial->destroyBlock(Tile::tiles[t]);
    }
    std::shared_ptr<ItemInstance> item = minecraft->player->getSelectedItem();
    int                           damageBefore;
    if (item != NULL) {
        damageBefore = item->getDamageValue();
    }
    bool changed = MultiPlayerGameMode::destroyBlock(x, y, z, face);

    if (!tutorial->m_allTutorialsComplete) {
        if (item != NULL && item->isDamageableItem()) {
            int max       = item->getMaxDamage();
            int damageNow = item->getDamageValue();

            if (damageNow > damageBefore && damageNow > (max / 2)) {
                tutorial->itemDamaged(item);
            }
        }
    }

    return changed;
}

void TutorialMode::tick() {
    MultiPlayerGameMode::tick();

    if (!tutorial->m_allTutorialsComplete) tutorial->tick();

    /*
    if( tutorial.m_allTutorialsComplete && (tutorial.lastMessageTime +
    m_iTutorialDisplayMessageTime) < GetTickCount() )
    {
        // Exit tutorial
        minecraft->gameMode = new SurvivalMode( this );
        delete this;
    }
    */
}

bool TutorialMode::useItemOn(
    std::shared_ptr<Player>       player,
    Level*                        level,
    std::shared_ptr<ItemInstance> item,
    int                           x,
    int                           y,
    int                           z,
    int                           face,
    Vec3*                         hit,
    bool                          bTestUseOnly,
    bool*                         pbUsedItem
) {
    bool haveItem  = false;
    int  itemCount = 0;
    if (!tutorial->m_allTutorialsComplete) {
        tutorial->useItemOn(level, item, x, y, z, bTestUseOnly);

        if (!bTestUseOnly) {
            if (item != NULL) {
                haveItem  = true;
                itemCount = item->count;
            }
        }
    }
    bool result = MultiPlayerGameMode::useItemOn(
        player,
        level,
        item,
        x,
        y,
        z,
        face,
        hit,
        bTestUseOnly,
        pbUsedItem
    );

    if (!bTestUseOnly) {
        if (!tutorial->m_allTutorialsComplete) {
            if (result && haveItem && itemCount > item->count) {
                tutorial->useItemOn(item);
            }
        }
    }
    return result;
}

void TutorialMode::attack(
    std::shared_ptr<Player> player,
    std::shared_ptr<Entity> entity
) {
    if (!tutorial->m_allTutorialsComplete) tutorial->attack(player, entity);

    MultiPlayerGameMode::attack(player, entity);
}

bool TutorialMode::isInputAllowed(int mapping) {
    return tutorial->m_allTutorialsComplete
        || tutorial->isInputAllowed(mapping);
}
