#include "Command.h"

#include <cstddef>

#include "server/MinecraftServer.h"
#include "server/PlayerList.h"

#include "AdminLogCommand.h"
#include "CommandSender.h"

AdminLogCommand* Command::logger;

bool Command::canExecute(std::shared_ptr<CommandSender> source) {
    return source->hasPermission(getId());
}

void Command::logAdminAction(
    std::shared_ptr<CommandSender> source,
    ChatPacket::EChatPacketMessage messageType,
    const std::wstring&            message,
    int                            customData,
    const std::wstring&            additionalMessage
) {
    logAdminAction(
        source,
        0,
        messageType,
        message,
        customData,
        additionalMessage
    );
}

void Command::logAdminAction(
    std::shared_ptr<CommandSender> source,
    int                            type,
    ChatPacket::EChatPacketMessage messageType,
    const std::wstring&            message,
    int                            customData,
    const std::wstring&            additionalMessage
) {
    if (logger != NULL) {
        logger->logAdminCommand(
            source,
            type,
            messageType,
            message,
            customData,
            additionalMessage
        );
    }
}

void Command::setLogger(AdminLogCommand* logger) { Command::logger = logger; }

std::shared_ptr<ServerPlayer> Command::getPlayer(PlayerUID playerId) {
    std::shared_ptr<ServerPlayer> player =
        MinecraftServer::getInstance()->getPlayers()->getPlayer(playerId);

    if (player == NULL) {
        return nullptr;
    } else {
        return player;
    }
}
