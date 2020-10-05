#include <assert.h>
#include <string.h>
#include "../Chunks/chunk.h"
#include "test_chunk.h"

static void testChunkInit(void);
static void testChunkRotateChunk(void);
static void testChunkGetFileName(void);

void
testChunk(void)
{
    testChunkInit();
    testChunkRotateChunk();
    testChunkGetFileName();
}

static void
testChunkInit(void)
{
    Chunk chunk[NBCHUNKS];
    for (int i = 0; i < NBCHUNKS; i++) {
        chunk[i] = chunkCreateChunk();
    }

    /* Testing chunkInit (simple assignment). */
    chunkSetMainChunk(chunk, -5, 5);
    assert(chunk[0].chunkX == -5);
    assert(chunk[0].chunkY == 5);

    for (int i = 0; i < NBCHUNKS; i++) {
        chunkDestroy(&chunk[i]);
    }
}

static void
testChunkRotateChunk(void)
{
    Chunk chunk[NBCHUNKS];
    for (int i = 0; i < NBCHUNKS; i++) {
        chunk[i] = chunkCreateChunk();
    }

    /*
     * Testing chunkRotateChunks (4 scenarios).
     * Case: (3, 2) on chunk 0, 0
     *       (1, 0)
     */
    chunkRotateChunks(chunk, 0, 0, 0, 0);
    assert(chunk[0].chunkX == 0);
    assert(chunk[0].chunkY == 0);
    assert(chunk[1].chunkX == -1);
    assert(chunk[1].chunkY == 0);
    assert(chunk[2].chunkX == 0);
    assert(chunk[2].chunkY == -1);
    assert(chunk[3].chunkX == -1);
    assert(chunk[3].chunkY == -1);

    /*
     * Case: (2, 3) in close negatives
     *       (0, 1)
     */
    chunkRotateChunks(chunk, -1, 0, -1, 0);
    assert(chunk[0].chunkX == -1);
    assert(chunk[0].chunkY == 0);
    assert(chunk[1].chunkX == 0);
    assert(chunk[1].chunkY == 0);
    assert(chunk[2].chunkX == -1);
    assert(chunk[2].chunkY == -1);
    assert(chunk[3].chunkX == 0);
    assert(chunk[3].chunkY == -1);

    /*
     * Case: (0, 1) in far negatives
     *       (2, 3)
     */
    chunkRotateChunks(chunk, -1 -10 * TILESIZE * TILESX,
                      -1 -10 * TILESIZE * TILESY,
                      -10, -10);
    assert(chunk[0].chunkX == -10);
    assert(chunk[0].chunkY == -10);
    assert(chunk[1].chunkX == -9);
    assert(chunk[1].chunkY == -10);
    assert(chunk[2].chunkX == -10);
    assert(chunk[2].chunkY == -9);
    assert(chunk[3].chunkX == -9);
    assert(chunk[3].chunkY == -9);

    /*
     * Case: (1, 0) in far positives
     *       (3, 2)
     */
    chunkRotateChunks(chunk, 4 * TILESIZE * TILESX,
                      TILESIZE * TILESY / 2 + 5 * TILESIZE * TILESY, 4, 5);
    assert(chunk[0].chunkX == 4);
    assert(chunk[0].chunkY == 5);
    assert(chunk[1].chunkX == 3);
    assert(chunk[1].chunkY == 5);
    assert(chunk[2].chunkX == 4);
    assert(chunk[2].chunkY == 6);
    assert(chunk[3].chunkX == 3);
    assert(chunk[3].chunkY == 6);

    for (int i = 0; i < NBCHUNKS; i++) {
        chunkDestroy(&chunk[i]);
    }
}

static void
testChunkGetFileName(void)
{
    assert(strcmp(chunkGetFileName(-5, 4), "Demo/chunks/-5,4.txt") == 0);
    assert(strcmp(chunkGetFileName(0, 1934), "Demo/chunks/0,1934.txt") == 0);
}
