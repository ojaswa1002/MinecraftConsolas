#include "EnchantItemCommand.h"

#include <cstddef>
#include <type_traits>
#include <utility>

#include "nbt/CompoundTag.h"
#include "nbt/ListTag.h"
#include "network/packet/ChatPacket.h"
#include "network/packet/GameCommandPacket.h"
#include "server/level/ServerPlayer.h"
#include "util/java/InputOutputStream/ByteArrayInputStream.h"
#include "util/java/InputOutputStream/ByteArrayOutputStream.h"
#include "util/java/InputOutputStream/DataInputStream.h"
#include "util/java/InputOutputStream/DataOutputStream.h"
#include "win/extraX64.h"
#include "world/entity/player/Player.h"
#include "world/item/ItemInstance.h"
#include "world/item/enchantment/Enchantment.h"

EGameCommand EnchantItemCommand::getId() { return eGameCommand_EnchantItem; }

int EnchantItemCommand::getPermissionLevel() {
    return 0; // aLEVEL_GAMEMASTERS;
}

void EnchantItemCommand::execute(
    std::shared_ptr<CommandSender> source,
    byteArray                      commandData
) {
    ByteArrayInputStream bais(commandData);
    DataInputStream      dis(&bais);

    PlayerUID uid              = dis.readPlayerUID();
    int       enchantmentId    = dis.readInt();
    int       enchantmentLevel = dis.readInt();

    bais.reset();

    std::shared_ptr<ServerPlayer> player = getPlayer(uid);

    if (player == NULL) return;

    std::shared_ptr<ItemInstance> selectedItem = player->getSelectedItem();

    if (selectedItem == NULL) return;

    Enchantment* e = Enchantment::enchantments[enchantmentId];

    if (e == NULL) return;
    if (!e->canEnchant(selectedItem)) return;

    if (enchantmentLevel < e->getMinLevel())
        enchantmentLevel = e->getMinLevel();
    if (enchantmentLevel > e->getMaxLevel())
        enchantmentLevel = e->getMaxLevel();

    if (selectedItem->hasTag()) {
        ListTag<CompoundTag>* enchantmentTags =
            selectedItem->getEnchantmentTags();
        if (enchantmentTags != NULL) {
            for (int i = 0; i < enchantmentTags->size(); i++) {
                int type = enchantmentTags->get(i)->getShort(
                    (wchar_t*)ItemInstance::TAG_ENCH_ID
                );

                if (Enchantment::enchantments[type] != NULL) {
                    Enchantment* other = Enchantment::enchantments[type];
                    if (!other->isCompatibleWith(e)) {
                        return;
                        // throw new
                        // CommandException("commands.enchant.cantCombine",
                        // e.getFullname(level),
                        // other.getFullname(enchantmentTags.get(i).getShort(ItemInstance.TAG_ENCH_LEVEL)));
                    }
                }
            }
        }
    }

    selectedItem->enchant(e, enchantmentLevel);

    // logAdminAction(source, "commands.enchant.success");
    logAdminAction(
        source,
        ChatPacket::e_ChatCustom,
        L"commands.enchant.success"
    );
}

std::shared_ptr<GameCommandPacket> EnchantItemCommand::preparePacket(
    std::shared_ptr<Player> player,
    int                     enchantmentId,
    int                     enchantmentLevel
) {
    if (player == NULL) return nullptr;

    ByteArrayOutputStream baos;
    DataOutputStream      dos(&baos);

    dos.writePlayerUID(player->getXuid());
    dos.writeInt(enchantmentId);
    dos.writeInt(enchantmentLevel);

    return std::shared_ptr<GameCommandPacket>(
        new GameCommandPacket(eGameCommand_EnchantItem, baos.toByteArray())
    );
}
