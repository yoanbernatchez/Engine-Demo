#include <stdio.h>
#include <stdlib.h>
#include "../Engine/globals.h"
#include "pathfinding.h"

/* Local structures. */
typedef struct
{
    int x;
    int y;
    int d;
} Triplet;

/*---------------------------------------------------------------------------*/
/* Local function prototypes                                                 */
/*---------------------------------------------------------------------------*/

/**
 * @brief Returns true if starting and ending points are within the index range
 *        of an array of size TILESX * NBCHUNKS / 2 by TILESY * NBCHUNKS / 2.
 *
 * @param startingPoint: Point to test (where the path starts).
 * @param endingPoint:   Point to test (where the path ends).
 *
 * @return True if it respects the limits of an array of size
 *         TILESX * NBCHUNKS / 2 by TILESY * NBCHUNKS / 2. False otherwise.
 */
static bool respectsArrayLimits(Point2d startingPoint, Point2d endingPoint);

/**
 * @brief Creates a path by assigning values to the direction int array and
 *        returning it.
 *
 * @param startingPoint: The tile we start creating a path from.
 * @param tile:          Array of tiles with wave values.
 *
 * @return A path structure with directions and information regarding the
 *         existence of the path.
 */
static Path createPath(Point2d startingPoint, int tile[][TILESY*NBCHUNKS/2]);

/**
 * @brief Finds and removes all duplicate numbers from an array of tile data.
 *
 * @param newTiles:   An array of tile data to be processed.
 * @param nbNewTiles: The size of the array.
 *
 * @return The new size of the array of tile data.
 */
static int removeDuplicates(Triplet* newTiles, int nbNewTiles);

/**
 * @brief Gives the array of tiles a value for each individual tile,
 *        corresponding to a collision map, based on the array of chunks.
 *
 * @param chunk: Array of chunk data.
 * @param tile:  Array of tile data.
 */
static void getMapInfo(Chunk chunk[], int tile[][TILESY*NBCHUNKS/2]);

/**
 * @brief Returns the order of the chunks in a specific order. Top-left: 0,
 *        top-right: 1, bottom-left: 2, bottom-right: 3.
 *
 * @param chunk: Array of chunk data.
 * @param order: Array of int that describes the order in which chunks need to
 *               be processed.
 */
static void chunkGetOrderOfChunks(Chunk chunk[], int order[]);

/*---------------------------------------------------------------------------*/
/* Pathfinding functions implementation                                      */
/*---------------------------------------------------------------------------*/

/*
 * Returns a path from a starting point to an ending point that takes
 * in account collision (wave propagation method).
 *
 * The wave propagation method may be slow when dealing with large amount of
 * tiles. A solution would be to also offer Dijkstra's algorithm, which is
 * more efficient.
 *
 * A path will always be returned, but may not exist. When a path does not
 * exist, it's doesPathExist member will be false and its nbSteps member will
 * be set to -1 (to distinguish between a path that has 0 steps).
 *
 * pathDestroy() must be called after usage of path.
 *
 * TODO: This is a very long function and there are probably ways to decompose
 *       it into functions and make it more readable.
 */
Path
pathfindGetPath(Chunk chunk[], int startingTileX, int startingTileY,
                   int endingTileX, int endingTileY)
{
    Path path;
    Triplet *oldTiles;
    Triplet *newTiles;

    int nbOldTiles = 1;
    int nbNewTiles = 0;

    Point2d startingPoint = {startingTileX, startingTileY};
    Point2d endingPoint = {endingTileX, endingTileY};

    int tile[TILESX * NBCHUNKS / 2][TILESY * NBCHUNKS / 2];
    getMapInfo(chunk, tile);

    /* Check if the starting tile and ending have collision set on them. */
    if (respectsArrayLimits(startingPoint, endingPoint) &&
        tile[startingPoint.x][startingPoint.y] != -1 &&
        tile[endingPoint.x][endingPoint.y] != -1) {

        /* Memory allocation for our tile nodes. */
        oldTiles = (Triplet*) malloc(nbOldTiles * sizeof(Triplet));
        newTiles = (Triplet*) malloc(0);

        oldTiles[0].x = endingPoint.x;
        oldTiles[0].y = endingPoint.y;
        oldTiles[0].d = 0;

        int d = 1;

        tile[endingPoint.x][endingPoint.y] = 1;

        do {
            /*
             * For every old tile, check if adjacent tiles have a value of 0
             * if so, add them to the new tile array.
             * TODO: Find a more graceful way to code this.
             */
            for (int i = 0; i < nbOldTiles; i++) {
                oldTiles[i].d = d;
                tile[oldTiles[i].x][oldTiles[i].y] = d;

                if (oldTiles[i].x -1 >= 0 && oldTiles[i].x -1 < TILESX*2 &&
                    oldTiles[i].y >= 0 && oldTiles[i].y < TILESY*2 &&
                    tile[oldTiles[i].x - 1][oldTiles[i].y] == 0) {
                    nbNewTiles++;
                    newTiles =
                    (Triplet*) realloc(newTiles,(nbNewTiles)*sizeof(Triplet));
                    newTiles[nbNewTiles-1].x = oldTiles[i].x - 1;
                    newTiles[nbNewTiles-1].y = oldTiles[i].y;

                }
                if (oldTiles[i].x+1 >= 0 && oldTiles[i].x+1 < TILESX*2 &&
                    oldTiles[i].y >= 0 && oldTiles[i].y < TILESY*2 &&
                    tile[oldTiles[i].x+1][oldTiles[i].y] == 0) {
                    nbNewTiles++;
                    newTiles =
                    (Triplet*) realloc(newTiles, (nbNewTiles)*sizeof(Triplet));
                    newTiles[nbNewTiles-1].x = oldTiles[i].x + 1;
                    newTiles[nbNewTiles-1].y = oldTiles[i].y;

                }
                if (oldTiles[i].x >= 0 && oldTiles[i].x < TILESX*2 &&
                    oldTiles[i].y -1 >= 0 && oldTiles[i].y -1 < TILESY*2 &&
                    tile[oldTiles[i].x][oldTiles[i].y-1] == 0) {
                    nbNewTiles++;
                    newTiles =
                    (Triplet*) realloc(newTiles, (nbNewTiles)*sizeof(Triplet));
                    newTiles[nbNewTiles-1].x = oldTiles[i].x;
                    newTiles[nbNewTiles-1].y = oldTiles[i].y - 1;

                }
                if (oldTiles[i].x >= 0 && oldTiles[i].x < TILESX*2 &&
                    oldTiles[i].y +1 >= 0 && oldTiles[i].y +1 < TILESY*2 &&
                    tile[oldTiles[i].x][oldTiles[i].y+1] == 0) {
                    nbNewTiles++;
                    newTiles =
                    (Triplet*) realloc(newTiles, (nbNewTiles)*sizeof(Triplet));
                    newTiles[nbNewTiles-1].x = oldTiles[i].x;
                    newTiles[nbNewTiles-1].y = oldTiles[i].y + 1;
                }
            }

            nbNewTiles = removeDuplicates(newTiles, nbNewTiles);

            /* Rewrite data from newTiles to oldTiles. */
            nbOldTiles = nbNewTiles;
            oldTiles =
            (Triplet*) realloc(oldTiles, nbOldTiles * sizeof(Triplet));

            for (int j = 0; j < nbOldTiles; j++) {
                oldTiles[j].x = newTiles[j].x;
                oldTiles[j].y = newTiles[j].y;
            }

            /* Erase data in newTiles. */
            free(newTiles);
            newTiles = (Triplet*) malloc(0*sizeof(Triplet));
            nbNewTiles = 0;

            d++;

        } while (nbOldTiles != 0);

        path = createPath(startingPoint, tile);

        /* Free allocated memory. */
        free(oldTiles);
        free(newTiles);
    }
    /* If starting tile or ending tile has collision set to it. */
    else {
        path.nbSteps = -1;
        path.doesPathExist = false;
    }

    return path;
}

/*
 * Creates a path by assigning values to the direction int array and
 * returning it.
 */
static Path
createPath(Point2d startingPoint, int tile[][TILESY*NBCHUNKS/2])
{
    Path path;
    int value = tile[startingPoint.x][startingPoint.y];
    int nbSteps = value - 1;

    path.direction = (int*) malloc(nbSteps * sizeof(int));
    path.nbSteps = nbSteps;
    path.doesPathExist = false;

    /* TODO: Make this less ugly. */
    for (int i = 0; i < nbSteps; i++) {
        if (tile[startingPoint.x + 1][startingPoint.y] < value &&
            tile[startingPoint.x + 1][startingPoint.y] > -1) {
            path.direction[i] = RIGHT;
            value = tile[startingPoint.x + 1][startingPoint.y];
        }
        if (tile[startingPoint.x - 1][startingPoint.y] < value &&
            tile[startingPoint.x - 1][startingPoint.y] > -1) {
            path.direction[i] = LEFT;
            value = tile[startingPoint.x - 1][startingPoint.y];
        }
        if (tile[startingPoint.x][startingPoint.y - 1] < value &&
            tile[startingPoint.x][startingPoint.y - 1] > -1) {
            path.direction[i] = UP;
            value = tile[startingPoint.x][startingPoint.y - 1];
        }
        if (tile[startingPoint.x][startingPoint.y + 1] < value &&
            tile[startingPoint.x][startingPoint.y + 1] > -1) {
            path.direction[i] = DOWN;
            value = tile[startingPoint.x][startingPoint.y + 1];
        }

        if (path.direction[i] == RIGHT) {
            startingPoint.x += 1;
        }
        else if (path.direction[i] == LEFT) {
            startingPoint.x -= 1;
        }
        else if (path.direction[i] == UP) {
            startingPoint.y -= 1;
        }
        else if (path.direction[i] == DOWN) {
            startingPoint.y += 1;
        }
    }

    if (value == 1) {
        path.doesPathExist = true;
    }

    return path;
}

/* Finds and removes all duplicate numbers from an array of tile data. */
static int
removeDuplicates(Triplet* newTiles, int nbNewTiles)
{
    for (int i = 0; i < nbNewTiles; i++) {
        for (int j = i + 1; j < nbNewTiles; j++) {

            /* Find duplicate(s). */
            if (newTiles[i].x == newTiles[j].x &&
                newTiles[i].y == newTiles[j].y) {
                /*
                 * Once duplicate is found, write the data of the next index
                 * over it, repeat process until there is no more data to
                 * handle, then free one slot of memory.
                 */
                for (int k = j; k < nbNewTiles-1; k++) {
                    newTiles[k] = newTiles[k+1];
                }

                /* Decrease size of array. */
                newTiles = (Triplet*) realloc(newTiles, (nbNewTiles - 1) *
                                              sizeof(Triplet));
                nbNewTiles--;

                /*
                 * Decrementing j here makes it so we can identify multiple
                 * duplicates in a single iteration of i.
                 */
                j--;
            }
        }
    }

    return nbNewTiles;
}

/*
 * Gives the array of tiles a value for each individual tile, corresponding
 * to a collision map, based on the array of chunks. Tiles will be assigned
 * -1 if the corresponding tile in the array of chunks has the collision set
 * to true, otherwise, tiles are assigned 0.
 */
static void
getMapInfo(Chunk chunk[], int tile[][TILESY*NBCHUNKS/2])
{
    int order[NBCHUNKS];
    int index = 0;
    chunkGetOrderOfChunks(chunk, order);

    /* We iterate for every tile in the four chunks combined map. */
    for (int i = 0; i < TILESX * NBCHUNKS / 2; i++) {
        for (int j = 0; j < TILESY * NBCHUNKS / 2; j++) {

            /* Find the chunk index corresponding to the pair (i, j). */
            index = 0;
            if (i >= TILESX) index += 1;
            if (j >= TILESY) index += 2;

            /*
             * Finally, set the value of each tile to -1 if there is
             * collision on the original tile.
             */
            if (chunk[order[index]].tile[i % TILESX][j % TILESY].collision) {
                tile[i % (TILESX * 2)][j % (TILESY * 2)] = -1;
            }
            else {
                tile[i % (TILESX * 2)][j % (TILESY * 2)] = 0;
            }
        }
    }
}

/*
 * Returns the order of the chunks in this specific order: top-left: 0,
 * top-right: 1, bottom-left: 2, bottom-right: 3, where the numbers are
 * the index of the array.
 */
static void
chunkGetOrderOfChunks(Chunk chunk[], int order[])
{
    /*
     * Sort in 2D to get the order of chunks, following the logic
     * of the chunkRotateChunks functions.
     */
    if (NBCHUNKS > 3 && chunk[0].chunkX < chunk[1].chunkX &&
        chunk[0].chunkY < chunk[2].chunkY) {
        order[0] = 0;
        order[1] = 1;
        order[2] = 2;
        order[3] = 3;
    }
    else if (NBCHUNKS > 3 && chunk[0].chunkX > chunk[1].chunkX &&
             chunk[0].chunkY < chunk[2].chunkY) {
        order[0] = 1;
        order[1] = 0;
        order[2] = 3;
        order[3] = 2;
    }
    else if (NBCHUNKS > 3 && chunk[0].chunkX < chunk[1].chunkX &&
             chunk[0].chunkY > chunk[2].chunkY) {
        order[0] = 2;
        order[1] = 3;
        order[2] = 0;
        order[3] = 1;
    }
    else if (NBCHUNKS > 3) {
        order[0] = 3;
        order[1] = 2;
        order[2] = 1;
        order[3] = 0;
    }
}

/*
 * Returns true if starting and ending points are within the index range
 * of an array of size TILESX * NBCHUNKS / 2 by TILESY * NBCHUNKS / 2.
 */
static bool
respectsArrayLimits(Point2d startingPoint, Point2d endingPoint)
{
    bool result = true;

    if (startingPoint.x < 0 || startingPoint.y < 0 ||
        endingPoint.x < 0 || endingPoint.y < 0) {
        result = false;
    }

    if (startingPoint.x >= TILESX * NBCHUNKS / 2 ||
        startingPoint.y >= TILESY * NBCHUNKS / 2 ||
        endingPoint.x >= TILESX * NBCHUNKS / 2 ||
        endingPoint.y >= TILESY * NBCHUNKS / 2) {
        result = false;
    }

    return result;
}

/* Frees memory allocated to a path. */
void
pathfindDestroyPath(Path *path)
{
    if (path->nbSteps > 0) {
        free(path->direction);
    }
}