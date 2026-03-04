#pragma once

#include "Tile.h"

class AirTile : public Tile {
    friend class Tile;

protected:
    AirTile(int id);
};
