#pragma once

#include <memory>

#include "commands/Command.h"
#include "commands/CommandsEnum.h"
#include "util/console/ArrayWithLength.h"

class GameCommandPacket;

class ToggleDownfallCommand : public Command {
public:
    virtual EGameCommand getId();
    virtual void
    execute(std::shared_ptr<CommandSender> source, byteArray commandData);

protected:
    void doToggleDownfall();

public:
    static std::shared_ptr<GameCommandPacket> preparePacket();
};
