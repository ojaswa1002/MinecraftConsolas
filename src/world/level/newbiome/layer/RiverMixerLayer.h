#pragma once

#include <memory>

#include "util/console/ArrayWithLength.h"

#include "Layer.h"

class RiverMixerLayer : public Layer {
private:
    std::shared_ptr<Layer> biomes;
    std::shared_ptr<Layer> rivers;

public:
    RiverMixerLayer(
        std::int64_t           seed,
        std::shared_ptr<Layer> biomes,
        std::shared_ptr<Layer> rivers
    );

    virtual void     init(std::int64_t seed);
    virtual intArray getArea(int xo, int yo, int w, int h);
};
