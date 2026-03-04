#include "DemoLevel.h"

#include "world/level/storage/LevelData.h"

class Dimension;
class LevelStorage;

DemoLevel::DemoLevel(
    std::shared_ptr<LevelStorage> levelStorage,
    const std::wstring&           levelName
)
: Level(levelStorage, levelName, DEMO_LEVEL_SEED) {}

DemoLevel::DemoLevel(Level* level, Dimension* dimension)
: Level(level, dimension) {}

void DemoLevel::setInitialSpawn() {
    levelData->setSpawn(DEMO_SPAWN_X, DEMO_SPAWN_Y, DEMO_SPAWN_Z);
}
