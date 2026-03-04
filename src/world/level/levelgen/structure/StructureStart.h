#pragma once

#include <list>

class BoundingBox;
class Level;
class Random;
class StructurePiece;

class StructureStart {
protected:
    std::list<StructurePiece*> pieces;
    BoundingBox*               boundingBox;

    StructureStart();

public:
    ~StructureStart();
    BoundingBox*                getBoundingBox();
    std::list<StructurePiece*>* getPieces();
    void postProcess(Level* level, Random* random, BoundingBox* chunkBB);

protected:
    void calculateBoundingBox();
    void moveBelowSeaLevel(Level* level, Random* random, int offset);
    void moveInsideHeights(
        Level*  level,
        Random* random,
        int     lowestAllowed,
        int     highestAllowed
    );

public:
    bool isValid();
};
