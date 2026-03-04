#pragma once

#include "util/WeighedRandom.h"

class Enchantment;

class EnchantmentInstance : public WeighedRandomItem {
public:
    const Enchantment* enchantment;
    const int          level;

    EnchantmentInstance(Enchantment* enchantment, int level);
    EnchantmentInstance(int id, int level);

    // 4J Added
    EnchantmentInstance* copy();
};
