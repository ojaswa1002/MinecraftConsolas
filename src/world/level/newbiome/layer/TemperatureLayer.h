#pragma once

#include <memory>

#include "util/console/ArrayWithLength.h"

#include "Layer.h"

class TemperatureLayer : public Layer {
public:
    TemperatureLayer(std::shared_ptr<Layer> parent);

    virtual intArray getArea(int xo, int yo, int w, int h);
};
