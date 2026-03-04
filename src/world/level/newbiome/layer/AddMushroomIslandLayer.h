#pragma once

#include <memory>

#include "util/console/ArrayWithLength.h"

#include "Layer.h"

class AddMushroomIslandLayer : public Layer {
public:
    AddMushroomIslandLayer(
        std::int64_t           seedMixup,
        std::shared_ptr<Layer> parent
    );
    virtual intArray getArea(int xo, int yo, int w, int h);
};
