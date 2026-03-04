#pragma once

#include "util/console/ArrayWithLength.h"

#include "Layer.h"

class IslandLayer : public Layer {
public:
    IslandLayer(std::int64_t seedMixup);

    intArray getArea(int xo, int yo, int w, int h);
};
