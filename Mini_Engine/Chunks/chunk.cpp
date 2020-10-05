#include <stdbool.h>
#include <string.h>
#include <SDL.h>
#include "chunk.h"
#include "tile.h"
#include "objects.h"
#include "../File_Utilities/file_utilities.h"

/*---------------------------------------------------------------------------*/
/* Local function prototypes                                                 */
/*---------------------------------------------------------------------------*/

/**
 * @brief Sets the updated state of all chunks to false if they had a change in
 *        chunk id.
 *
 * @param chunk: Array of chunks to update.
 */
static void setChunkUpdateState(Chunk chunk[]);

/*---------------------------------------------------------------------------*/
/* Chunk functions implementation                                            */
/*---------------------------------------------------------------------------*/

/* Sets the main chunk's (chunk[0]) position. */
void
chunkSetMainChunk(Chunk chunk[], int chunkX, int chunkY)
{
    /* Sets a certain starting chunk. */
    if (NBCHUNKS > 0) {
        chunk[0].chunkX = chunkX;
        chunk[0].chunkY = chunkY;
    }
    else {
        printf("Impossible to initiate an empty chunk array.\n");
    }
}

/*
 * Loads data such as tile data and object data to a singular chunk, determined
 * by the chunkIndex.
 */
void
chunkLoadChunk(Chunk *chunk, bool forceLoad)
{
    /* Load tile and object data into one chunk. */
    if (!chunk->updated || forceLoad) {
        tileLoadTiles(chunk);
        objectLoadObjects(chunk);
        chunk->updated = true;
    }
}

/*
 * Loads data such as tile data and object data to all chunks in the array of
 * chunks sent in parameters.
 */
void
chunkLoadChunks(Chunk chunk[], bool forceLoad)
{
    /* Load tile and object data for all chunks. */
    for (int i = 0; i < NBCHUNKS; i++) {
        chunkLoadChunk(&chunk[i], false);
    }
}

/*
 * This function updates the chunkX and chunkY coordinates for every chunk in
 * the chunk array and rotates the chunks based on character coordinates
 * if necessary.
 * chunk[0] is the main chunk and always contains the selected character.
 * chunk[1] is the horizontal chunk.
 * chunk[2] is the vertical chunk.
 * chunk[3] is the diagonal chunk.
 */
void
chunkRotateChunks(Chunk chunk[], int charX, int charY, int charChunkX,
                       int charChunkY)
{
    int chunkPixelLenght = TILESIZE * TILESX; /* Length of chunk in pixels. */
    int chunkPixelHeight = TILESIZE * TILESY; /* Height of chunk in pixels. */

    /* Save chunk data to oldChunk. */
    for (int i = 0; i < NBCHUNKS; i++) {
        chunk[i].oldChunkX = chunk[i].chunkX;
        chunk[i].oldChunkY = chunk[i].chunkY;
    }

    /* Update main chunk to be the one the character is in. */
    if (NBCHUNKS > 0) {
        chunk[0].chunkX = charChunkX;
        chunk[0].chunkY = charChunkY;
    }

    /*
     * Horizontal chunk update.
     * The horizontal chunk is always chunkX[0] - 1 or chunkX[0] + 1 and
     * chunkY[0], depending on the selected character's coordinates.
     */
    if (NBCHUNKS > 1) {
        if (charX >= charChunkX * chunkPixelLenght &&
            charX < charChunkX * chunkPixelLenght + chunkPixelLenght/2) {
            chunk[1].chunkX = chunk[0].chunkX - 1;
        }
        else {
            chunk[1].chunkX = chunk[0].chunkX + 1;
        }

        chunk[1].chunkY = chunk[0].chunkY;
    }

    /*
     * Vertical chunk update.
     * The vertical chunk is always chunkX[0] and chunkY[0] - 1
     * or chunkY[0] + 1, depending on the selected character's coordinates.
     */
    if (NBCHUNKS > 2) {
        if (charY >= charChunkY * chunkPixelHeight &&
            charY < charChunkY * chunkPixelHeight + chunkPixelHeight/2) {
            chunk[2].chunkY = chunk[0].chunkY - 1;
        }
        else {
            chunk[2].chunkY = chunk[0].chunkY + 1;
        }

        chunk[2].chunkX = chunk[0].chunkX;
    }

    /*
     * Diagonal chunk update.
     * The diagonal chunk always has the same chunkX value as the horizontal
     * chunk and the same chunkY value as the vertical chunk.
     */
    if (NBCHUNKS > 3) {
        chunk[3].chunkX = chunk[1].chunkX;
        chunk[3].chunkY = chunk[2].chunkY;
    }

    /* Update the chunks' update states. */
    setChunkUpdateState(chunk);

    /* Update chunks if there was a change. */
    chunkLoadChunks(chunk, false);
}

/*
 * Sets the updated state of all chunks to false if they had a change in chunk
 * id.
 */
static void
setChunkUpdateState(Chunk chunk[])
{
    for (int i = 0; i < NBCHUNKS; i++) {
        if (chunk[i].chunkX != chunk[i].oldChunkX ||
           chunk[i].chunkY != chunk[i].oldChunkY) {
            chunk[i].updated = false;
        }
    }
}

/* Returns a file name corresponding to the directory of a chunk data file. */
const char *
chunkGetFileName(int chunkX, int chunkY)
{
    char fileName[30];

    sprintf(fileName, "Demo/chunks/%d,%d.txt", chunkX, chunkY);

    return strdup(fileName);
}

/* Creates an initializes a chunk, then returns it. */
Chunk
chunkCreateChunk(void)
{
    Chunk chunk;

    chunk.oldChunkX = 0;
    chunk.oldChunkY = 0;
    chunk.chunkX = 0;
    chunk.chunkY = 0;
    chunk.nbObjects = 0;
    chunk.updated = false;

    for (int i = 0; i < TILESX; i++) {
        for (int j = 0; j < TILESY; j++) {
            chunk.tile[i][j] = tileCreateTile();
        }
    }

    return chunk;
}

/* Frees memory of the dynamically allocated members of the chunk. */
void
chunkDestroy(Chunk *chunk)
{
    objectDeallocate(chunk);
}
