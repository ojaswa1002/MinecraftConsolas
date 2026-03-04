#include "InstantenousMobEffect.h"

#include "platform/App_enums.h"

#include "MobEffect.h"

InstantenousMobEffect::InstantenousMobEffect(
    int              id,
    bool             isHarmful,
    eMinecraftColour color
)
: MobEffect(id, isHarmful, color) {}

bool InstantenousMobEffect::isInstantenous() { return true; }

bool InstantenousMobEffect::isDurationEffectTick(
    int remainingDuration,
    int amplification
) {
    return remainingDuration >= 1;
}
