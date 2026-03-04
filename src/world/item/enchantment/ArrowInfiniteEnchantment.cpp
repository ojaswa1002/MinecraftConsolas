#include "ArrowInfiniteEnchantment.h"

#include "win/strings.h"

#include "EnchantmentCategory.h"

ArrowInfiniteEnchantment::ArrowInfiniteEnchantment(int id, int frequency)
: Enchantment(id, frequency, EnchantmentCategory::bow) {
    setDescriptionId(IDS_ENCHANTMENT_ARROW_INFINITE);
}

int ArrowInfiniteEnchantment::getMinCost(int level) { return 20; }

int ArrowInfiniteEnchantment::getMaxCost(int level) { return 50; }

int ArrowInfiniteEnchantment::getMaxLevel() { return 1; }
