#pragma once

#include <memory>

#include "util/console/ArrayWithLength.h"

#include "Layer.h"

class ShoreLayer : public Layer {
public:
    ShoreLayer(std::int64_t seed, std::shared_ptr<Layer> parent);
    virtual intArray getArea(int xo, int yo, int w, int h);
};
