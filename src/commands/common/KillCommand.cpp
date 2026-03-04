#include "KillCommand.h"

#include <memory>
#include <type_traits>
#include <utility>

#include "commands/CommandSender.h"
#include "world/damagesource/DamageSource.h"
#include "world/entity/player/Player.h"

EGameCommand KillCommand::getId() { return eGameCommand_Kill; }

void KillCommand::execute(
    std::shared_ptr<CommandSender> source,
    byteArray                      commandData
) {
    std::shared_ptr<Player> player = dynamic_pointer_cast<Player>(source);

    player->hurt(DamageSource::outOfWorld, 1000);

    source->sendMessage(L"Ouch. That look like it hurt.");
}
