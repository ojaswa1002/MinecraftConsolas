#pragma once

#include <memory>

#include "commands/Command.h"
#include "commands/CommandsEnum.h"
#include "util/console/ArrayWithLength.h"

class CommandSender;
class GameCommandPacket;

class TimeCommand : public Command {
public:
    virtual EGameCommand getId();
    virtual void
    execute(std::shared_ptr<CommandSender> source, byteArray commandData);

protected:
    void doSetTime(std::shared_ptr<CommandSender> source, int value);
    void doAddTime(std::shared_ptr<CommandSender> source, int value);

public:
    static std::shared_ptr<GameCommandPacket> preparePacket(bool night);
};
