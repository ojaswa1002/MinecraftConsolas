#pragma once

#include <memory>

#include "world/level/Level.h"

class Dimension;
class LevelStorage;

class DemoLevel : public Level {
private:
    static const std::int64_t DEMO_LEVEL_SEED =
        0; // 4J - TODO - was "Don't Look Back".hashCode();
    static const int DEMO_SPAWN_X = 796;
    static const int DEMO_SPAWN_Y = 72;
    static const int DEMO_SPAWN_Z = -731;

public:
    DemoLevel(
        std::shared_ptr<LevelStorage> levelStorage,
        const std::wstring&           levelName
    );
    DemoLevel(Level* level, Dimension* dimension);

protected:
    virtual void setInitialSpawn();
};
