#pragma once

#include "client/model/geom/Model.h"

class ModelPart;

class ChestModel : public Model {
public:
    using Model::render;

    ModelPart* lid;
    ModelPart* bottom;
    ModelPart* lock;

    ChestModel();
    void render(bool usecompiled);
};
