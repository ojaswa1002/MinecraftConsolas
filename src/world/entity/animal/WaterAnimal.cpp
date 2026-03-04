#include "WaterAnimal.h"

#include <memory>

#include "util/java/Random.h"
#include "world/level/Level.h"

WaterAnimal::WaterAnimal(Level* level) : PathfinderMob(level) {
    // 4J Stu - This function call had to be moved here from the Entity ctor to
    // ensure that the derived version of the function is called

    // This should only be called for the most derive classes
    // this->defineSynchedData();
}

bool WaterAnimal::isWaterMob() {
    return true; // prevent drowning
}

bool WaterAnimal::canSpawn() { return level->isUnobstructed(bb); }

int WaterAnimal::getAmbientSoundInterval() { return 20 * 6; }

bool WaterAnimal::removeWhenFarAway() { return true; }

int WaterAnimal::getExperienceReward(std::shared_ptr<Player> killedBy) {
    return 1 + level->random->nextInt(3);
}
