#include "ToggleDownfallCommand.h"

#include <type_traits>
#include <utility>

#include "network/packet/ChatPacket.h"
#include "network/packet/GameCommandPacket.h"
#include "server/MinecraftServer.h"
#include "server/level/ServerLevel.h"
#include "world/level/storage/LevelData.h"

EGameCommand ToggleDownfallCommand::getId() {
    return eGameCommand_ToggleDownfall;
}

void ToggleDownfallCommand::execute(
    std::shared_ptr<CommandSender> source,
    byteArray                      commandData
) {
    doToggleDownfall();
    logAdminAction(
        source,
        ChatPacket::e_ChatCustom,
        L"commands.downfall.success"
    );
}

void ToggleDownfallCommand::doToggleDownfall() {
    MinecraftServer::getInstance()->levels[0]->toggleDownfall();
    MinecraftServer::getInstance()->levels[0]->getLevelData()->setThundering(
        true
    );
}

std::shared_ptr<GameCommandPacket> ToggleDownfallCommand::preparePacket() {
    return std::shared_ptr<GameCommandPacket>(
        new GameCommandPacket(eGameCommand_ToggleDownfall, byteArray())
    );
}
