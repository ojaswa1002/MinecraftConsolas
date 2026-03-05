#include "AvoidPlayerGoal.h"

#include <cstddef>
#include <vector>

#include "world/entity/Entity.h"
#include "world/entity/PathfinderMob.h"
#include "world/entity/ai/control/Control.h"
#include "world/entity/ai/navigation/PathNavigation.h"
#include "world/entity/ai/sensing/Sensing.h"
#include "world/entity/ai/util/RandomPos.h"
#include "world/entity/animal/TamableAnimal.h"
#include "world/entity/player/Player.h"
#include "world/level/Level.h"
#include "world/level/pathfinder/Path.h"
#include "world/phys/AABB.h"
#include "world/phys/Vec3.h"

AvoidPlayerGoal::AvoidPlayerGoal(
    PathfinderMob*   mob,
    const type_info& avoidType,
    float            maxDist,
    float            walkSpeed,
    float            sprintSpeed
)
: avoidType(avoidType) {
    this->mob = mob;
    // this->avoidType = avoidType;
    this->maxDist     = maxDist;
    this->walkSpeed   = walkSpeed;
    this->sprintSpeed = sprintSpeed;
    this->pathNav     = mob->getNavigation();
    setRequiredControlFlags(Control::MoveControlFlag);

    toAvoid = std::weak_ptr<Entity>();
    path    = NULL;
}

AvoidPlayerGoal::~AvoidPlayerGoal() {
    if (path != NULL) delete path;
}

bool AvoidPlayerGoal::canUse() {
    if (avoidType == typeid(Player)) {
        std::shared_ptr<TamableAnimal> tamableAnimal =
            std::dynamic_pointer_cast<TamableAnimal>(mob->shared_from_this());
        if (tamableAnimal != NULL && tamableAnimal->isTame()) return false;
        toAvoid = std::weak_ptr<Entity>(
            mob->level->getNearestPlayer(mob->shared_from_this(), maxDist)
        );
        if (toAvoid.lock() == NULL) return false;
    } else {
        std::vector<std::shared_ptr<Entity>>* entities =
            mob->level->getEntitiesOfClass(
                avoidType,
                mob->bb->grow(maxDist, 3, maxDist)
            );
        if (entities->empty()) {
            delete entities;
            return false;
        }
        toAvoid = std::weak_ptr<Entity>(entities->at(0));
        delete entities;
    }

    if (!mob->getSensing()->canSee(toAvoid.lock())) return false;

    Vec3* pos = RandomPos::getPosAvoid(
        std::dynamic_pointer_cast<PathfinderMob>(mob->shared_from_this()),
        16,
        7,
        Vec3::newTemp(toAvoid.lock()->x, toAvoid.lock()->y, toAvoid.lock()->z)
    );
    if (pos == NULL) return false;
    if (toAvoid.lock()->distanceToSqr(pos->x, pos->y, pos->z)
        < toAvoid.lock()->distanceToSqr(mob->shared_from_this()))
        return false;
    delete path;
    path = pathNav->createPath(pos->x, pos->y, pos->z);
    if (path == NULL) return false;
    if (!path->endsInXZ(pos)) return false;
    return true;
}

bool AvoidPlayerGoal::canContinueToUse() {
    return toAvoid.lock() != NULL && !pathNav->isDone();
}

void AvoidPlayerGoal::start() {
    pathNav->moveTo(path, walkSpeed);
    path = NULL;
}

void AvoidPlayerGoal::stop() { toAvoid = std::weak_ptr<Entity>(); }

void AvoidPlayerGoal::tick() {
    if (mob->distanceToSqr(toAvoid.lock()) < 7 * 7)
        mob->getNavigation()->setSpeed(sprintSpeed);
    else mob->getNavigation()->setSpeed(walkSpeed);
}
