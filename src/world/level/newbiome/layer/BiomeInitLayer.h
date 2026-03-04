#pragma once

#include <memory>

#include "util/console/ArrayWithLength.h"

#include "Layer.h"

class LevelType;

class BiomeInitLayer : public Layer {
private:
    BiomeArray startBiomes;

public:
    BiomeInitLayer(
        std::int64_t           seed,
        std::shared_ptr<Layer> parent,
        LevelType*             levelType
    );
    virtual ~BiomeInitLayer();
    intArray getArea(int xo, int yo, int w, int h);
};
