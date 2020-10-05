#include <stdio.h>
#include <assert.h>
#include "../Chunks/chunk.h"
#include "../Chunks/tile.h"
#include "../Chunks/pathfinding.h"
#include "test_pathfinding.h"

static void testPathfindGetPath(void);

void
testPathfinding(void)
{
    testPathfindGetPath();
}

static void
testPathfindGetPath(void)
{
    Path path;
    int nbChunks = 4;
    int tilesX = 64;
    int tilesY = 64;
    Chunk chunk[nbChunks];

    for (int i = 0; i < nbChunks; i++) {
        chunk[i] = chunkCreateChunk();
    }

    chunk[0].chunkX = 0;
    chunk[0].chunkY = 0;
    chunk[1].chunkX = -1;
    chunk[1].chunkY = 0;
    chunk[2].chunkX = 0;
    chunk[2].chunkY = -1;
    chunk[3].chunkX = -1;
    chunk[3].chunkY = -1;

    chunk[0].tile[1][0].id = 1;

    /* Test when the starting tile is a tile with collision. */
    tileSetCollision(chunk, 0, true);
    path = pathfindGetPath(chunk, tilesX, tilesY, tilesX + 1, tilesY);
    assert(path.nbSteps == -1);
    assert(!path.doesPathExist);
    pathfindDestroyPath(&path);

    /* Test when ending tile is a tile with collision. */
    path = pathfindGetPath(chunk, tilesX + 1, tilesY, tilesX, tilesY);
    assert(path.nbSteps == -1);
    assert(!path.doesPathExist);
    pathfindDestroyPath(&path);

    /* Test when destination goes out of scope negatively. */
    tileSetCollision(chunk, 0, false);
    path = pathfindGetPath(chunk, tilesX, tilesY, -100, -200);
    assert(path.nbSteps == -1);
    assert(!path.doesPathExist);
    pathfindDestroyPath(&path);

    /* Test when destination goes out of scope positively. */
    tileSetCollision(chunk, 0, false);
    path = pathfindGetPath(chunk, tilesX, tilesY,
                           tilesX * (NBCHUNKS + 1), tilesY * (NBCHUNKS + 1));
    assert(path.nbSteps == -1);
    assert(!path.doesPathExist);
    pathfindDestroyPath(&path);

    /* Test destination unreachable. */
    tileSetCollision(chunk, 0, true);
    chunk[0].tile[0][0].collision = false;
    chunk[1].tile[tilesX - 2][0].collision = false;
    path = pathfindGetPath(chunk, tilesX, tilesY, tilesX - 2, tilesY);
    assert(path.nbSteps == -1);
    assert(!path.doesPathExist);
    pathfindDestroyPath(&path);

    /* Test starting point = ending point. */
    chunk[3].tile[0][0].collision = false;
    path = pathfindGetPath(chunk, 0, 0, 0, 0);
    assert(path.nbSteps == 0);
    assert(path.doesPathExist);
    pathfindDestroyPath(&path);

#if TILESX == 64 && TILESY == 64
    /*
     * Test path is found.
     * Note: This is hard to test if TILESX is different than tilesX or
     *       TILESY is different than tilesY
     */
    chunk[0].tile[0][0].collision = false;
    chunk[1].tile[tilesX - 1][0].collision = false;
    chunk[1].tile[tilesX - 2][0].collision = false;
    chunk[1].tile[tilesX - 2][1].collision = false;
    chunk[1].tile[tilesX - 2][2].collision = false;
    path = pathfindGetPath(chunk, tilesX, tilesY, tilesX - 2, tilesY + 2);
    assert(path.nbSteps == 4);
    assert(path.doesPathExist);
    pathfindDestroyPath(&path);
#endif

    for (int i = 0; i < nbChunks; i++) {
        chunkDestroy(&chunk[i]);
    }
}
