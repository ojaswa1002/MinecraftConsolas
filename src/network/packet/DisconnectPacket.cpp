#include "DisconnectPacket.h"

#include "util/java/InputOutputStream/DataInputStream.h"
#include "util/java/InputOutputStream/DataOutputStream.h"

#include "PacketListener.h"

DisconnectPacket::DisconnectPacket() { reason = eDisconnect_None; }

DisconnectPacket::DisconnectPacket(eDisconnectReason reason) {
    this->reason = reason;
}

void DisconnectPacket::read(DataInputStream* dis) // throws IOException
{
    reason = (eDisconnectReason)dis->readInt();
}

void DisconnectPacket::write(DataOutputStream* dos) // throws IOException
{
    dos->writeInt((int)reason);
}

void DisconnectPacket::handle(PacketListener* listener) {
    listener->handleDisconnect(shared_from_this());
}

int DisconnectPacket::getEstimatedSize() { return sizeof(eDisconnectReason); }

bool DisconnectPacket::canBeInvalidated() { return true; }

bool DisconnectPacket::isInvalidatedBy(std::shared_ptr<Packet> packet) {
    return true;
}
