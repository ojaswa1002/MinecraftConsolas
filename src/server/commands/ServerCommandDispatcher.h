#pragma once

#include <type_traits>
#include <utility>

#include "commands/AdminLogCommand.h"
#include "commands/CommandDispatcher.h"
#include "network/packet/ChatPacket.h"

class ServerCommandDispatcher : public CommandDispatcher,
                                public AdminLogCommand {
public:
    ServerCommandDispatcher();
    void logAdminCommand(
        std::shared_ptr<CommandSender> source,
        int                            type,
        ChatPacket::EChatPacketMessage messageType,
        const std::wstring&            message           = L"",
        int                            customData        = -1,
        const std::wstring&            additionalMessage = L""
    );
};
