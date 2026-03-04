#include "RemoveMobEffectPacket.h"

#include "util/java/InputOutputStream/DataInputStream.h"
#include "util/java/InputOutputStream/DataOutputStream.h"
#include "win/extraX64.h"
#include "world/effect/MobEffectInstance.h"

#include "PacketListener.h"

RemoveMobEffectPacket::RemoveMobEffectPacket() {}

RemoveMobEffectPacket::RemoveMobEffectPacket(
    int                entityId,
    MobEffectInstance* effect
) {
    this->entityId = entityId;
    this->effectId = (byte)(effect->getId() & 0xff);
}

void RemoveMobEffectPacket::read(DataInputStream* dis) {
    entityId = dis->readInt();
    effectId = dis->readByte();
}

void RemoveMobEffectPacket::write(DataOutputStream* dos) {
    dos->writeInt(entityId);
    dos->writeByte(effectId);
}

void RemoveMobEffectPacket::handle(PacketListener* listener) {
    listener->handleRemoveMobEffect(shared_from_this());
}

int RemoveMobEffectPacket::getEstimatedSize() { return 5; }
