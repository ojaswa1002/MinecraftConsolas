#pragma once

#include <memory>

#include "util/console/ArrayWithLength.h"

#include "Layer.h"

class DownfallLayer : public Layer {
public:
    DownfallLayer(std::shared_ptr<Layer> parent);
    intArray getArea(int xo, int yo, int w, int h);
};
