#pragma once

#include <memory>

#include "commands/Command.h"
#include "commands/CommandsEnum.h"
#include "util/console/ArrayWithLength.h"
#include "win/extraX64.h"
#include "world/item/ItemInstance.h"

class CommandSender;
class GameType;

class GameModeCommand : public Command {
public:
    virtual EGameCommand getId();
    virtual void
    execute(std::shared_ptr<CommandSender> source, byteArray commandData);

protected:
    GameType* getModeForString(
        std::shared_ptr<CommandSender> source,
        const std::wstring&            name
    );
    std::shared_ptr<Player> getPlayer(PlayerUID playerId);
};
