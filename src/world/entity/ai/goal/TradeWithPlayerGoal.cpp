#include "TradeWithPlayerGoal.h"

#include <cstddef>
#include <memory>

#include "world/entity/ai/control/Control.h"
#include "world/entity/ai/navigation/PathNavigation.h"
#include "world/entity/npc/Villager.h"
#include "world/entity/player/Player.h"

TradeWithPlayerGoal::TradeWithPlayerGoal(Villager* mob) {
    this->mob = mob;
    setRequiredControlFlags(
        Control::JumpControlFlag | Control::MoveControlFlag
    );
}

bool TradeWithPlayerGoal::canUse() {
    if (!mob->isAlive()) return false;
    if (mob->isInWater()) return false;
    if (!mob->onGround) return false;
    if (mob->hurtMarked) return false;

    std::shared_ptr<Player> trader = mob->getTradingPlayer();
    if (trader == NULL) {
        // no interaction
        return false;
    }

    if (mob->distanceToSqr(trader) > (4 * 4)) {
        // too far away
        return false;
    }

    if (!(trader->containerMenu == trader->inventoryMenu)) {
        // closed container
        return false;
    }

    return true;
}

void TradeWithPlayerGoal::start() { mob->getNavigation()->stop(); }

void TradeWithPlayerGoal::stop() { mob->setTradingPlayer(nullptr); }
