#pragma once

#include "world/entity/Creature.h"

class Enemy : public Creature {
public:
    static const int XP_REWARD_NONE;
    static const int XP_REWARD_SMALL;
    static const int XP_REWARD_MEDIUM;
    static const int XP_REWARD_LARGE;
    static const int XP_REWARD_HUGE;
};
