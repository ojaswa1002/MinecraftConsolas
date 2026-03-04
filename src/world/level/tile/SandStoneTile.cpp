#include "SandStoneTile.h"

#include <cstddef>
#include <type_traits>
#include <utility>

#include "win/strings.h"
#include "world/Facing.h"
#include "world/IconRegister.h"
#include "world/level/material/Material.h"

class Icon;

const std::wstring SandStoneTile::TEXTURE_TOP    = L"sandstone_top";
const std::wstring SandStoneTile::TEXTURE_BOTTOM = L"sandstone_bottom";
const std::wstring SandStoneTile::TEXTURE_NAMES[] =
    {L"sandstone_side", L"sandstone_carved", L"sandstone_smooth"};

int SandStoneTile::SANDSTONE_NAMES[SANDSTONE_BLOCK_NAMES] = {
    IDS_TILE_SANDSTONE,
    IDS_TILE_SANDSTONE_CHISELED,
    IDS_TILE_SANDSTONE_SMOOTH
};

SandStoneTile::SandStoneTile(int id) : Tile(id, Material::stone) {
    icons      = NULL;
    iconTop    = NULL;
    iconBottom = NULL;
}

Icon* SandStoneTile::getTexture(int face, int data) {
    if (face == Facing::UP
        || (face == Facing::DOWN
            && (data == TYPE_HEIROGLYPHS || data == TYPE_SMOOTHSIDE))) {
        return iconTop;
    }
    if (face == Facing::DOWN) {
        return iconBottom;
    }
    if (data < 0 || data >= SANDSTONE_TILE_TEXTURE_COUNT) data = 0;
    return icons[data];
}

int SandStoneTile::getSpawnResourcesAuxValue(int data) { return data; }

void SandStoneTile::registerIcons(IconRegister* iconRegister) {
    icons = new Icon*[SANDSTONE_TILE_TEXTURE_COUNT];

    for (int i = 0; i < SANDSTONE_TILE_TEXTURE_COUNT; i++) {
        icons[i] = iconRegister->registerIcon(TEXTURE_NAMES[i]);
    }

    iconTop    = iconRegister->registerIcon(TEXTURE_TOP);
    iconBottom = iconRegister->registerIcon(TEXTURE_BOTTOM);
}
