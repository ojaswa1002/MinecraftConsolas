#pragma once

#include <memory>

#include "commands/Command.h"
#include "commands/CommandsEnum.h"
#include "util/console/ArrayWithLength.h"

class GameCommandPacket;
class Player;

class EnchantItemCommand : public Command {
public:
    virtual EGameCommand getId();
    int                  getPermissionLevel();
    virtual void
    execute(std::shared_ptr<CommandSender> source, byteArray commandData);

    static std::shared_ptr<GameCommandPacket> preparePacket(
        std::shared_ptr<Player> player,
        int                     enchantmentId,
        int                     enchantmentLevel = 1
    );
};
