#include "AnimatePacket.h"

#include "util/java/InputOutputStream/DataInputStream.h"
#include "util/java/InputOutputStream/DataOutputStream.h"
#include "world/entity/Entity.h"

#include "PacketListener.h"

AnimatePacket::AnimatePacket() {
    id     = -1;
    action = 0;
}

AnimatePacket::AnimatePacket(std::shared_ptr<Entity> e, int action) {
    id           = e->entityId;
    this->action = action;
}

void AnimatePacket::read(DataInputStream* dis) // throws IOException
{
    id     = dis->readInt();
    action = dis->readByte();
}

void AnimatePacket::write(DataOutputStream* dos) // throws IOException
{
    dos->writeInt(id);
    dos->writeByte(action);
}

void AnimatePacket::handle(PacketListener* listener) {
    listener->handleAnimate(shared_from_this());
}

int AnimatePacket::getEstimatedSize() { return 5; }
