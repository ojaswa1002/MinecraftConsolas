#pragma once

#include "MobRenderer.h"

class Model;

class GiantMobRenderer : public MobRenderer {
private:
    float _scale;

public:
    GiantMobRenderer(Model* model, float shadow, float scale);

protected:
    virtual void scale(std::shared_ptr<Mob> mob, float a);
};
