#pragma once

#include "util/java/Class.h"

#include "Particle.h"

class Level;

class BubbleParticle : public Particle {
public:
    virtual eINSTANCEOF GetType() { return eType_BUBBLEPARTICLE; }
    BubbleParticle(
        Level* level,
        double x,
        double y,
        double z,
        double xa,
        double ya,
        double za
    );
    virtual void tick();
};
