#include "InteractGoal.h"

#include "world/entity/ai/control/Control.h"

class Mob;
class type_info;

InteractGoal::InteractGoal(
    Mob*             mob,
    const type_info& lookAtType,
    float            lookDistance
)
: LookAtPlayerGoal(mob, lookAtType, lookDistance) {
    setRequiredControlFlags(
        Control::LookControlFlag | Control::MoveControlFlag
    );
}

InteractGoal::InteractGoal(
    Mob*             mob,
    const type_info& lookAtType,
    float            lookDistance,
    float            probability
)
: LookAtPlayerGoal(mob, lookAtType, lookDistance, probability) {
    setRequiredControlFlags(
        Control::LookControlFlag | Control::MoveControlFlag
    );
}
