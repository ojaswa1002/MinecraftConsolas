#pragma once

#include "util/console/ArrayWithLength.h"

#include "Layer.h"

class BiomeOverrideLayer : public Layer {
private:
    static const unsigned int width  = 216;
    static const unsigned int height = 216;

    byteArray m_biomeOverride;

public:
    BiomeOverrideLayer(int seedMixup);
    intArray getArea(int xo, int yo, int w, int h);
};
