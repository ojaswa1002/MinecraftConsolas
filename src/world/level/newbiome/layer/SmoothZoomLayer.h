#pragma once

#include <memory>

#include "util/console/ArrayWithLength.h"

#include "Layer.h"

class SmoothZoomLayer : public Layer {
public:
    SmoothZoomLayer(std::int64_t seedMixup, std::shared_ptr<Layer> parent);

    virtual intArray getArea(int xo, int yo, int w, int h);
    static std::shared_ptr<Layer>
    zoom(std::int64_t seed, std::shared_ptr<Layer> sup, int count);
};
