#include "ContainerButtonClickPacket.h"

#include "util/java/InputOutputStream/DataInputStream.h"
#include "util/java/InputOutputStream/DataOutputStream.h"

#include "PacketListener.h"

ContainerButtonClickPacket::ContainerButtonClickPacket() {}

ContainerButtonClickPacket::ContainerButtonClickPacket(
    int containerId,
    int buttonId
) {
    this->containerId = containerId;
    this->buttonId    = buttonId;
}

void ContainerButtonClickPacket::handle(PacketListener* listener) {
    listener->handleContainerButtonClick(shared_from_this());
}

void ContainerButtonClickPacket::read(DataInputStream* dis) {
    containerId = dis->readByte();
    buttonId    = dis->readByte();
}

void ContainerButtonClickPacket::write(DataOutputStream* dos) {
    dos->writeByte(containerId);
    dos->writeByte(buttonId);
}

int ContainerButtonClickPacket::getEstimatedSize() { return 2; }
