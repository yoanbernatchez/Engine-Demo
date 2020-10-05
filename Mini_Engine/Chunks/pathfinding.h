#ifndef PATHFINDING_H_INCLUDED
#define PATHFINDING_H_INCLUDED

#include "../Engine/globals.h"

typedef struct
{
    int *direction;
    int nbSteps;
    bool doesPathExist;
} Path;
/**<
 * Structure containing a path to follow returned by the
 * path finding system.
 */

/**
 * @brief Returns a path from a starting point to an ending point that takes
 *        in account collision (wave propagation method).
 *
 * @param chunk: Array of chunks containing tile and object information.
 * @param startingTileX: Tile in x where the path starts.
 * @param startingTileY: Tile in y where the path starts.
 * @param endingTileX:   Tile in x where the path ends.
 * @param endingTileY:   Tile in y where the path ends.
 *
 * @return A path structure containing directions and information regarding the
 *         existence of the path.
 */
Path pathfindGetPath(Chunk chunk[], int startingTileX, int startingTileY,
                        int endingTileX, int endingTileY);

/**
 * @brief Frees memory allocated to a path.
 *
 * @param path: The path to destroy.
 */
void
pathfindDestroyPath(Path *path);
#endif /* PATHFINDING_H_INCLUDED */
