#include "GiantMobRenderer.h"

#include <memory>

#include "client/renderer/Stubs.h"

class Model;

GiantMobRenderer::GiantMobRenderer(Model* model, float shadow, float _scale)
: MobRenderer(model, shadow * _scale) {
    this->_scale = _scale;
}

void GiantMobRenderer::scale(std::shared_ptr<Mob> mob, float a) {
    glScalef(_scale, _scale, _scale);
}
