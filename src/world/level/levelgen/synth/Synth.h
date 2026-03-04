#pragma once

#include "util/console/ArrayWithLength.h"

class Synth {
public:
    virtual double getValue(double x, double y) = 0;

    doubleArray create(int width, int height);
};

