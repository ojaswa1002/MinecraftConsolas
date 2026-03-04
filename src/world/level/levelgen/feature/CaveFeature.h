#pragma once

#include "Feature.h"

class CaveFeature : public Feature {
    virtual bool place(Level* level, Random* random, int x, int y, int z);
};
