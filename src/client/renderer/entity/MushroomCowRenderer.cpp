#include "MushroomCowRenderer.h"

#include <memory>

#include <4J_Render.h>

#include "client/model/QuadrupedModel.h"
#include "client/model/geom/ModelPart.h"
#include "client/renderer/Stubs.h"
#include "client/renderer/Textures.h"
#include "client/renderer/TileRenderer.h"
#include "world/entity/Mob.h"
#include "world/entity/animal/MushroomCow.h"
#include "world/level/tile/Bush.h"
#include "world/level/tile/Tile.h"

class Model;

MushroomCowRenderer::MushroomCowRenderer(Model* model, float shadow)
: MobRenderer(model, shadow) {}

void MushroomCowRenderer::render(
    std::shared_ptr<Entity> _mob,
    double                  x,
    double                  y,
    double                  z,
    float                   rot,
    float                   a
) {
    // 4J - original version used generics and thus had an input parameter of
    // type MushroomCow rather than std::shared_ptr<Entity>  we have here - do
    // some casting around instead std::shared_ptr<MushroomCow> mob =
    // std::dynamic_pointer_cast<MushroomCow>(_mob);

    // 4J Stu - No need to do the cast, just pass through as-is
    MobRenderer::render(_mob, x, y, z, rot, a);
}

void MushroomCowRenderer::additionalRendering(
    std::shared_ptr<Mob> _mob,
    float                a
) {
    // 4J - original version used generics and thus had an input parameter of
    // type MushroomCow rather than std::shared_ptr<Mob>  we have here - do some
    // casting around instead
    std::shared_ptr<MushroomCow> mob =
        std::dynamic_pointer_cast<MushroomCow>(_mob);
    MobRenderer::additionalRendering(mob, a);
    if (mob->isBaby()) return;
    bindTexture(TN_TERRAIN); // 4J was "/terrain.png"
    glEnable(GL_CULL_FACE);
    glPushMatrix();
    glScalef(1, -1, 1);
    glTranslatef(0.2f, 0.4f, 0.5f);
    glRotatef(42, 0, 1, 0);
    tileRenderer->renderTile(Tile::mushroom2, 0, 1);
    glTranslatef(0.1f, 0, -0.6f);
    glRotatef(42, 0, 1, 0);
    tileRenderer->renderTile(Tile::mushroom2, 0, 1);
    glPopMatrix();

    glPushMatrix();
    ((QuadrupedModel*)model)->head->translateTo(1 / 16.0f);
    glScalef(1, -1, 1);
    glTranslatef(0, 0.75f, -0.2f);
    glRotatef(12, 0, 1, 0);
    tileRenderer->renderTile(Tile::mushroom2, 0, 1);
    glPopMatrix();

    glDisable(GL_CULL_FACE);
}
