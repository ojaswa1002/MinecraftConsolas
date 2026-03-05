#include "SaddleItem.h"

#include <memory>

#include "world/entity/Mob.h"
#include "world/entity/animal/Pig.h"

#include "ItemInstance.h"

SaddleItem::SaddleItem(int id) : Item(id) { maxStackSize = 1; }

bool SaddleItem::interactEnemy(
    std::shared_ptr<ItemInstance> itemInstance,
    std::shared_ptr<Mob>          mob
) {
    if (std::dynamic_pointer_cast<Pig>(mob)) {
        std::shared_ptr<Pig> pig = std::dynamic_pointer_cast<Pig>(mob);
        if (!pig->hasSaddle() && !pig->isBaby()) {
            pig->setSaddle(true);
            itemInstance->count--;
        }
        return true;
    }
    return false;
}

bool SaddleItem::hurtEnemy(
    std::shared_ptr<ItemInstance> itemInstance,
    std::shared_ptr<Mob>          mob,
    std::shared_ptr<Mob>          attacker
) {
    interactEnemy(itemInstance, mob);
    return true;
}
