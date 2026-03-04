#pragma once

#include <memory>

#include "util/console/ArrayWithLength.h"

#include "Layer.h"

class VoronoiZoom : public Layer {
public:
    VoronoiZoom(std::int64_t seedMixup, std::shared_ptr<Layer> parent);

    virtual intArray getArea(int xo, int yo, int w, int h);

protected:
    int random(int a, int b);
    int random(int a, int b, int c, int d);
};
