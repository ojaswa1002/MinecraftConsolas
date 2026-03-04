#include "GiveItemCommand.h"

#include <cstddef>

#include "network/packet/ChatPacket.h"
#include "network/packet/GameCommandPacket.h"
#include "server/level/ServerPlayer.h"
#include "util/java/InputOutputStream/ByteArrayInputStream.h"
#include "util/java/InputOutputStream/ByteArrayOutputStream.h"
#include "util/java/InputOutputStream/DataInputStream.h"
#include "util/java/InputOutputStream/DataOutputStream.h"
#include "win/extraX64.h"
#include "world/entity/player/Player.h"
#include "world/item/Item.h"
#include "world/item/ItemInstance.h"

EGameCommand GiveItemCommand::getId() { return eGameCommand_Give; }

void GiveItemCommand::execute(
    std::shared_ptr<CommandSender> source,
    byteArray                      commandData
) {
    ByteArrayInputStream bais(commandData);
    DataInputStream      dis(&bais);

    PlayerUID    uid    = dis.readPlayerUID();
    int          item   = dis.readInt();
    int          amount = dis.readInt();
    int          aux    = dis.readInt();
    std::wstring tag    = dis.readUTF();

    bais.reset();

    std::shared_ptr<ServerPlayer> player = getPlayer(uid);
    if (player != NULL && item > 0 && Item::items[item] != NULL) {
        std::shared_ptr<ItemInstance> itemInstance =
            std::shared_ptr<ItemInstance>(new ItemInstance(item, amount, aux));
        player->drop(itemInstance);
        // logAdminAction(source, L"commands.give.success",
        // ChatPacket::e_ChatCustom, Item::items[item]->getName(itemInstance),
        // item, amount, player->getAName());
        logAdminAction(
            source,
            ChatPacket::e_ChatCustom,
            L"commands.give.success",
            item,
            player->getAName()
        );
    }
}

std::shared_ptr<GameCommandPacket> GiveItemCommand::preparePacket(
    std::shared_ptr<Player> player,
    int                     item,
    int                     amount,
    int                     aux,
    const std::wstring&     tag
) {
    if (player == NULL) return nullptr;

    ByteArrayOutputStream baos;
    DataOutputStream      dos(&baos);

    dos.writePlayerUID(player->getXuid());
    dos.writeInt(item);
    dos.writeInt(amount);
    dos.writeInt(aux);
    dos.writeUTF(tag);

    return std::shared_ptr<GameCommandPacket>(
        new GameCommandPacket(eGameCommand_Give, baos.toByteArray())
    );
}
