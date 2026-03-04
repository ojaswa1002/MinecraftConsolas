#include "MineShaftStart.h"

#include <list>

#include "MineShaftPieces.h"

class Level;
class Random;

MineShaftStart::MineShaftStart(
    Level*  level,
    Random* random,
    int     chunkX,
    int     chunkZ
) {
    MineShaftPieces::MineShaftRoom* mineShaftRoom =
        new MineShaftPieces::MineShaftRoom(
            0,
            random,
            (chunkX << 4) + 2,
            (chunkZ << 4) + 2
        );
    pieces.push_back(mineShaftRoom);
    mineShaftRoom->addChildren(mineShaftRoom, &pieces, random);

    calculateBoundingBox();
    moveBelowSeaLevel(level, random, 10);
}
