#pragma once

#include <memory>

#include "util/console/ArrayWithLength.h"

#include "Layer.h"

class RiverInitLayer : public Layer {
public:
    RiverInitLayer(std::int64_t seed, std::shared_ptr<Layer> parent);

    intArray getArea(int xo, int yo, int w, int h);
};
