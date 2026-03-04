#pragma once

#include <memory>

#include "util/console/ArrayWithLength.h"

#include "Layer.h"

class RiverLayer : public Layer {
public:
    RiverLayer(std::int64_t seedMixup, std::shared_ptr<Layer> parent);
    intArray getArea(int xo, int yo, int w, int h);
};
