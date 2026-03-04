#include "DownfallLayer.h"

#include <memory>

#include "util/console/ArrayWithLength.h"
#include "world/level/biome/Biome.h"

#include "IntCache.h"
#include "Layer.h"

DownfallLayer::DownfallLayer(std::shared_ptr<Layer> parent) : Layer(0) {
    this->parent = parent;
}

intArray DownfallLayer::getArea(int xo, int yo, int w, int h) {
    intArray b = parent->getArea(xo, yo, w, h);

    intArray result = IntCache::allocate(w * h);
    for (int i = 0; i < w * h; i++) {
        result[i] = Biome::biomes[b[i]]->getDownfallInt();
    }

    return result;
}
