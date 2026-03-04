#pragma once

#include <memory>

#include "commands/Command.h"
#include "commands/CommandsEnum.h"
#include "util/console/ArrayWithLength.h"
#include "win/extraX64.h"
#include "world/item/ItemInstance.h"

class ExperienceCommand : public Command {
public:
    virtual EGameCommand getId();
    virtual void
    execute(std::shared_ptr<CommandSender> source, byteArray commandData);

protected:
    std::shared_ptr<Player> getPlayer(PlayerUID playerId);
};
