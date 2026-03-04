#pragma once

#include "client/model/geom/Model.h"

class ModelPart;

class SignModel : public Model {
public:
    using Model::render;
    ModelPart* cube;
    ModelPart* cube2;

    SignModel();
    void render(bool usecompiled);
};
