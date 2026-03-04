#pragma once

#include "Feature.h"

class ClayFeature : public Feature {
private:
    int tile;
    int radius;

public:
    ClayFeature(int radius);

    virtual bool place(Level* level, Random* random, int x, int y, int z);
};
