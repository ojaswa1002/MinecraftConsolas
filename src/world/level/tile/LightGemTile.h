#pragma once

#include "Tile.h"

class Material;

class LightGemTile : public Tile {
public:
    LightGemTile(int id, Material* material);
    virtual int getResourceCountForLootBonus(int bonusLevel, Random* random);
    virtual int getResourceCount(Random* random);
    virtual int getResource(int data, Random* random, int playerBonusLevel);
};
