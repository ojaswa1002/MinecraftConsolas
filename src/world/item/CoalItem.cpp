#include "CoalItem.h"

#include <memory>

#include "win/strings.h"

#include "ItemInstance.h"

CoalItem::CoalItem(int id) : Item(id) {
    setStackedByData(true);
    setMaxDamage(0);
}

unsigned int
CoalItem::getDescriptionId(std::shared_ptr<ItemInstance> instance) {
    if (instance->getAuxValue() == CHAR_COAL) {
        return IDS_ITEM_CHARCOAL;
    }
    return IDS_ITEM_COAL;
}
