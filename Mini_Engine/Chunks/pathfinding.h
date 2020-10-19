#ifndef PATHFINDING_H_INCLUDED
#define PATHFINDING_H_INCLUDED

#include "../Engine/globals.h"

typedef struct _EngPath
{
    int *direction;
    int nb_steps;
    bool does_path_exist;
} EngPath;
/**<
 * Structure containing a path for an NPC to follow.
 */

/**
 * @brief Returns a path from a starting point to an ending point that takes
 *        in account collision (wave propagation method).
 *
 * @param chunk:           Array of chunks containing tile and object
 *                         information.
 * @param starting_tile_x: Tile in x where the path starts.
 * @param starting_tile_y: Tile in y where the path starts.
 * @param ending_tile_x:   Tile in x where the path ends.
 * @param ending_tile_y:   Tile in y where the path ends.
 *
 * @return A path structure containing directions and information regarding the
 *         existence of the path.
 *
 * @sa eng_pathfind_destroy_path ()
 */
EngPath * eng_pathfind_get_path (EngChunk chunk[],
                                 int starting_tile_x, int starting_tile_y,
                                 int ending_tile_x, int ending_tile_y);

/**
 * @brief Frees memory allocated to a path.
 *
 * @param path: Pointer to the path to destroy.
 *
 * @sa eng_pathfind_get_path ()
 */
void eng_pathfind_destroy_path (EngPath **path);

#endif /* PATHFINDING_H_INCLUDED */
