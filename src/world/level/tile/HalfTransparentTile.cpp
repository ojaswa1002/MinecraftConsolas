#include "HalfTransparentTile.h"

#include <type_traits>
#include <utility>

#include "world/IconRegister.h"
#include "world/level/LevelSource.h"

class Material;

HalfTransparentTile::HalfTransparentTile(
    int                 id,
    const std::wstring& tex,
    Material*           material,
    bool                allowSame
)
: Tile(id, material, isSolidRender()) {
    this->allowSame = allowSame;
    this->texture   = tex;
}

bool HalfTransparentTile::isSolidRender(bool isServerLevel) { return false; }

bool HalfTransparentTile::shouldRenderFace(
    LevelSource* level,
    int          x,
    int          y,
    int          z,
    int          face
) {
    int id = level->getTile(x, y, z);
    if (!allowSame && id == this->id) return false;
    return Tile::shouldRenderFace(level, x, y, z, face);
}

bool HalfTransparentTile::blocksLight() { return false; }

void HalfTransparentTile::registerIcons(IconRegister* iconRegister) {
    icon = iconRegister->registerIcon(texture);
}
