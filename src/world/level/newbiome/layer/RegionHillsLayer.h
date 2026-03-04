#pragma once

#include <memory>

#include "util/console/ArrayWithLength.h"

#include "Layer.h"

class RegionHillsLayer : public Layer {
public:
    RegionHillsLayer(std::int64_t seed, std::shared_ptr<Layer> parent);

    intArray getArea(int xo, int yo, int w, int h);
};
