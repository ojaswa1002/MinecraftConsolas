#pragma once

#include <memory>

#include "commands/Command.h"
#include "commands/CommandsEnum.h"
#include "util/console/ArrayWithLength.h"
#include "win/extraX64.h"

class GameCommandPacket;

class TeleportCommand : public Command {
public:
    virtual EGameCommand getId();
    virtual void
    execute(std::shared_ptr<CommandSender> source, byteArray commandData);

    static std::shared_ptr<GameCommandPacket>
    preparePacket(PlayerUID subject, PlayerUID destination);
};
