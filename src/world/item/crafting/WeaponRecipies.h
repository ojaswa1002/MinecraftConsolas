// package net.minecraft.world.item.crafting;

// import net.minecraft.world.item.*;
// import net.minecraft.world.level.tile.Tile;

#pragma once

#include <string>
#include <vector>

#define MAX_WEAPON_RECIPES 2

class Object;
class Recipes;

class WeaponRecipies {
public:
    // 4J - added for common ctor code
    void _init();
    WeaponRecipies() { _init(); }

private:
    static std::wstring   shapes[][4];
    std::vector<Object*>* map;

public:
    void addRecipes(Recipes* r);
};
