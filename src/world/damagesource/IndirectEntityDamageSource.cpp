// IndirectEntityDamageSource::IndirectEntityDamageSource(const std::wstring
// &msgId, std::shared_ptr<Entity> entity, std::shared_ptr<Entity> owner) :
// EntityDamageSource(msgId, entity)
#include "IndirectEntityDamageSource.h"

#include <cstddef>
#include <memory>
#include <type_traits>
#include <utility>

#include "network/packet/ChatPacket.h"
#include "util/java/Class.h"
#include "world/entity/Entity.h"
#include "world/entity/player/Player.h"

#include "EntityDamageSource.h"

IndirectEntityDamageSource::IndirectEntityDamageSource(
    ChatPacket::EChatPacketMessage msgId,
    std::shared_ptr<Entity>        entity,
    std::shared_ptr<Entity>        owner
)
: EntityDamageSource(msgId, entity) {
    this->owner = owner;
}

// 4J Stu - Brought forward from 1.2.3 to fix #46422
std::shared_ptr<Entity> IndirectEntityDamageSource::getDirectEntity() {
    return entity;
}

std::shared_ptr<Entity> IndirectEntityDamageSource::getEntity() {
    return owner;
}

// std::wstring
// IndirectEntityDamageSource::getLocalizedDeathMessage(std::shared_ptr<Player>
// player)
//{
//	return L"death." + msgId + player->name + owner->getAName();
//	//return I18n.get("death." + msgId, player.name, owner.getAName());
// }

std::shared_ptr<ChatPacket> IndirectEntityDamageSource::getDeathMessagePacket(
    std::shared_ptr<Player> player
) {
    std::wstring additional = L"";
    int          type;
    if (owner != NULL) {
        type = owner->GetType();
        if (type == eTYPE_SERVERPLAYER) {
            std::shared_ptr<Player> sourcePlayer =
                std::dynamic_pointer_cast<Player>(owner);
            if (sourcePlayer != NULL) additional = sourcePlayer->name;
        }
    } else {
        type = entity->GetType();
    }
    return std::shared_ptr<ChatPacket>(
        new ChatPacket(player->name, m_msgId, type, additional)
    );
}
