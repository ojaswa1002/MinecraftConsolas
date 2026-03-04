#pragma once

#include <memory>

#include "util/console/ArrayWithLength.h"

#include "Layer.h"

class FuzzyZoomLayer : public Layer {
public:
    FuzzyZoomLayer(std::int64_t seedMixup, std::shared_ptr<Layer> parent);
    intArray getArea(int xo, int yo, int w, int h);

protected:
    int random(int a, int b);
    int random(int a, int b, int c, int d);

public:
    static std::shared_ptr<Layer>
    zoom(std::int64_t seed, std::shared_ptr<Layer> sup, int count);
};
