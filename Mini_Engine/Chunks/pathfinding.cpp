#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pathfinding.h"

/* Local structures. */
typedef struct _EngNode {
    int x;
    int y;
    int d;
} EngNode;
/**< Node structure used for pathfinding. */

/*---------------------------------------------------------------------------*/
/* Local function prototypes                                                 */
/*---------------------------------------------------------------------------*/

/**
 * @brief Adds a new node to the dynamic array new_tiles if the specified tile
 *        equals zero.
 *
 * @param old_tiles:      Array of old tile nodes.
 * @param new_tiles:      Pointer to an array of new tile nodes.
 * @param tile:           Collision map.
 * @param old_tile_index: The index of the old tile to check for adjacent zero
 *                        tiles.
 * @param nb_new_tiles:   Number of new tile nodes.
 * @param offset_x:       -1 for left adjacent tile, 1 for right adjacent tile.
 * @param offset_y:       -1 for up adjacent tile, 1 for down adjacent tile.
 *
 * @return 0 if there was an error in memory assignment, 1 if successful.
 */
static int add_new_node (EngNode *old_tiles, EngNode **new_tiles,
                          int tile[][TILESY*NBCHUNKS/2], int old_tile_index,
                          int *nb_new_tiles, int offset_x, int offset_y);

/**
 * @brief Adds a step and a direction to a path.
 *
 * @param tile:           Collision map.
 * @param path:           The path we add a step and direction to.
 * @param dir_index:      The index of direction in which we put a value.
 * @param value:          The wave value of the tile currently observed.
 * @param starting_point: The tile to observe (+ the offset).
 * @param offset_x:       Offset in x to the tile to observe.
 * @param offset_y:       Offset in y to the tile to observe.
 */
static void add_step (int tile[][TILESY*NBCHUNKS/2], EngPath *path,
                      int dir_index, int *value, EngPoint2d starting_point,
                      int offset_x, int offset_y);

/**
 * @brief Returns true if starting and ending points are within the index range
 *        of an array of size TILESX * NBCHUNKS / 2 by TILESY * NBCHUNKS / 2.
 *
 * @param starting_point: Point to test (where the path starts).
 * @param ending_point:   Point to test (where the path ends).
 *
 * @return True if it respects the limits of an array of size
 *         TILESX * NBCHUNKS / 2 by TILESY * NBCHUNKS / 2, false otherwise.
 */
static bool respects_array_limits (EngPoint2d starting_point,
                                   EngPoint2d ending_point);

/**
 * @brief Creates a path by assigning values to the direction int array and
 *        returning it.
 *
 * @param starting_point: The tile we start creating a path from.
 * @param tile:           Array of tiles with wave values.
 *
 * @return A path structure with directions and information regarding the
 *         existence of the path (NULL if path does not exist).
 */
static EngPath * create_path (EngPoint2d starting_point,
                              int tile[][TILESY*NBCHUNKS/2]);

/**
 * @brief Finds and removes all duplicate nodes.
 *
 * @param new_tiles:    An array of nodes to be processed.
 * @param nb_new_tiles: The size of the array.
 *
 * @return The new size of the array of nodes.
 */
static int remove_duplicates (EngNode *new_tiles, int nb_new_tiles);

/**
 * @brief Gives the array of tiles a value for each individual tile,
 *        corresponding to a collision map, based on the array of chunks.
 *
 * @param chunk: Array of chunk data.
 * @param tile:  Array of tile data.
 */
static void get_collision_map (EngChunk chunk[],
                               int tile[][TILESY*NBCHUNKS/2]);

/**
 * @brief Sets a specific order to the chunks and saves the order in an array.
 *        Top-left: 0, top-right: 1, bottom-left: 2, bottom-right: 3.
 *
 * @param chunk: Array of chunk data.
 * @param order: Array of int that describes the order in which chunks need to
 *               be processed.
 */
static void chunk_get_order_of_chunks (EngChunk chunk[], int order[]);

/*---------------------------------------------------------------------------*/
/* Path finding functions implementation                                     */
/*---------------------------------------------------------------------------*/

/*
 * Returns a path from a starting point to an ending point that takes
 * in account tile collision (wave propagation method).
 *
 * The wave propagation method may be slow when dealing with large amount of
 * tiles. A solution would be to also offer Dijkstra's algorithm or A*, which
 * are more efficient.
 *
 * A path will always be returned, but may not exist. When a path does not
 * exist, the pointer returned is NULL.
 *
 * eng_pathfind_detroy() must be called after usage of path.
 *
 * NOTE: This algorithm has been written with memory allocation checks, which
 *       makes the function look a little bit heavy, however, it allows the
 *       program to keep running even if the OS did not lend memory. If the OS
 *       did not allocate memory and the algorithm kept going without checks,
 *       it could have caused eventual crashes.
 *
 * TODO: This is a very long function and there are probably ways to decompose
 *       it even more.
 */
EngPath *
eng_pathfind_get_path (EngChunk chunk[],
                       int starting_tile_x, int starting_tile_y,
                       int ending_tile_x, int ending_tile_y)
{
    EngPath *path = NULL;
    EngNode *old_tiles = NULL;
    EngNode *new_tiles = NULL;
    int tile[TILESX * NBCHUNKS / 2][TILESY * NBCHUNKS / 2];
    int wave_value = 1;
    bool is_mem_invalid = false;

    int nb_old_tiles = 1;
    int nb_new_tiles = 0;

    EngPoint2d starting_point = {starting_tile_x, starting_tile_y};
    EngPoint2d ending_point = {ending_tile_x, ending_tile_y};

    /*
     * Check if starting point and ending points are within array limits,
     * otherwise we return a NULL path.
     */
    if (respects_array_limits (starting_point, ending_point)) {

        get_collision_map (chunk, tile);

        /*
         * Make sure that the starting tile and ending tile do not have
         * collision set on them (if one of them does, we return a NULL path).
         */
        if (tile[starting_point.x][starting_point.y] != -1 &&
            tile[ending_point.x][ending_point.y] != -1) {

            /* Initialization of our first old tile node. */
            old_tiles = (EngNode*) malloc (nb_old_tiles * sizeof(EngNode));

            /* Check if memory was allocated. */
            if (old_tiles == NULL) {
                is_mem_invalid = true;
                goto MEM_ERROR;
            }

            old_tiles[0].x = ending_point.x;
            old_tiles[0].y = ending_point.y;
            old_tiles[0].d = 0;

            tile[ending_point.x][ending_point.y] = wave_value;

            /*
             * In this loop, we give a wave propagation value to all the tiles
             * in the tile array.
             */
            while (nb_old_tiles != 0) {
                /*
                 * For every old tile, check if adjacent tiles have a value of
                 * 0 if so, add them to the new_tiles node array. For every
                 * adjacent tile, we also do a memory allocation check.
                 */
                for (int i = 0; i < nb_old_tiles; i++) {
                    tile[old_tiles[i].x][old_tiles[i].y] = wave_value;

                    /* Check for left adjacent tile. */
                    if (add_new_node (old_tiles, &new_tiles, tile, i,
                                      &nb_new_tiles, -1, 0) == 0) {
                        is_mem_invalid = true;
                        goto MEM_ERROR;
                    }

                    /* Check for right adjacent tile. */
                    if (add_new_node (old_tiles, &new_tiles, tile, i,
                                      &nb_new_tiles, 1, 0) == 0) {
                        is_mem_invalid = true;
                        goto MEM_ERROR;
                    }

                    /* Check for up adjacent tile. */
                    if (add_new_node (old_tiles, &new_tiles, tile, i,
                                      &nb_new_tiles, 0, -1) == 0) {
                        is_mem_invalid = true;
                        goto MEM_ERROR;
                    }

                    /* Check for down adjacent tile. */
                    if (add_new_node (old_tiles, &new_tiles, tile, i,
                                      &nb_new_tiles, 0, 1) == 0) {
                        is_mem_invalid = true;
                        goto MEM_ERROR;
                    }
                }

                nb_new_tiles = remove_duplicates (new_tiles, nb_new_tiles);

                /* Transfer data from new_tiles nodes to old_tiles nodes. */
                if (old_tiles != NULL) {
                    free (old_tiles);
                    old_tiles = NULL;
                }

                nb_old_tiles = nb_new_tiles;

                if (nb_old_tiles != 0) {
                    old_tiles = (EngNode*) malloc (nb_old_tiles *
                                                   sizeof(EngNode));
                    if (old_tiles == NULL) {
                        is_mem_invalid = true;
                        goto MEM_ERROR;
                    }
                }

                for (int j = 0; j < nb_old_tiles; j++) {
                    old_tiles[j].x = new_tiles[j].x;
                    old_tiles[j].y = new_tiles[j].y;
                    old_tiles[j].d = new_tiles[j].d;
                }

                /* Get rid of our new_tiles nodes. */
                if (new_tiles != NULL) {
                    free (new_tiles);
                    new_tiles = NULL;
                }

                nb_new_tiles = 0;

                wave_value++;
            }
            path = create_path (starting_point, tile);
        }
    }

     /*
      * In case of an error in memory allocation, for example, if the OS did
      * not lend memory as expected, we return a NULL path and an error
      * message.
      */
MEM_ERROR:
    if (is_mem_invalid)
        printf ("Unable to allocate memory in %s %d\n.", __FILE__, __LINE__);
    if (old_tiles != NULL)
        free (old_tiles);
    if (new_tiles != NULL)
        free (new_tiles);

    return path;
}

/*
 * Adds a new node to the dynamic array new_tiles if the specified tile
 * equals zero.
 */
static int
add_new_node (EngNode *old_tiles, EngNode **new_tiles,
              int tile[][TILESY*NBCHUNKS/2],
              int old_tile_index, int *nb_new_tiles,
              int offset_x, int offset_y)
{
    if (old_tiles[old_tile_index].x + offset_x >= 0 &&
        old_tiles[old_tile_index].x + offset_x < TILESX * 2 &&
        old_tiles[old_tile_index].y + offset_y >= 0 &&
        old_tiles[old_tile_index].y + offset_y < TILESY * 2 &&
        tile[old_tiles[old_tile_index].x + offset_x]
            [old_tiles[old_tile_index].y + offset_y] == 0) {

        /* Allocate memory for the new tile node. */
        if (*nb_new_tiles == 0) {
            *new_tiles = (EngNode*) malloc (sizeof(EngNode));

            /* Check if memory was allocated. */
            if (*new_tiles == NULL)
                return 0;
        }
        /* Reallocate memory for the new tile nodes. */
        else {
            *new_tiles = (EngNode*) realloc (*new_tiles, (*nb_new_tiles + 1) *
                                             sizeof(EngNode));
            /* Check if memory was allocated. */
            if (*new_tiles == NULL)
                return 0;
        }

        *nb_new_tiles += 1;
        EngNode *new_tiles_ptr = *new_tiles;

        /* Initializing the new tile node. */
        if (*nb_new_tiles - 1 >= 0) {
            new_tiles_ptr[*nb_new_tiles - 1].x = old_tiles[old_tile_index].x +
                                                 offset_x;
            new_tiles_ptr[*nb_new_tiles - 1].y = old_tiles[old_tile_index].y +
                                                 offset_y;
            new_tiles_ptr[*nb_new_tiles - 1].d = 0;
        }
        else
            printf ("Negative index for new_tiles in %s %d.\n" __FILE__,
                    __LINE__);
    }

    return 1;
}

/*
 * Creates a path by assigning values to the direction int array and
 * returning it.
 *
 * NOTE: This function also has memory allocation failure checks. If memory
 *       wasn't allocated by the OS, the function would return a NULL path.
 */
static EngPath *
create_path (EngPoint2d starting_point, int tile[][TILESY*NBCHUNKS/2])
{
    EngPath *path = NULL;
    int value = tile[starting_point.x][starting_point.y];
    int nb_steps = value - 1;
    bool is_mem_invalid = false;

    if (nb_steps > 0) {
        /* Allocate memory for our path. */
        path = (EngPath*) malloc (sizeof(EngPath));
        if (path == NULL) {
            is_mem_invalid = true;
            goto MEM_ERROR;
        }

        /* Allocate memory for our directions. */
        path->direction = (int*) malloc (nb_steps * sizeof(int));
        if (path->direction == NULL) {
            is_mem_invalid = true;
            goto MEM_ERROR;
        }

        path->nb_steps = nb_steps;

        for (int i = 0; i < nb_steps; i++) {
            /* Try to add steps and directions. */
            add_step (tile, path, i, &value, starting_point, -1, 0);
            add_step (tile, path, i, &value, starting_point, 1, 0);
            add_step (tile, path, i, &value, starting_point, 0, -1);
            add_step (tile, path, i, &value, starting_point, 0, 1);

            /* Adjust starting point. */
            switch (path->direction[i]) {
            case ENG_LEFT:
                starting_point.x -= 1;
                break;
            case ENG_RIGHT:
                starting_point.x += 1;
                break;
            case ENG_UP:
                starting_point.y -= 1;
                break;
            case ENG_DOWN:
                starting_point.y += 1;
                break;
            }
        }

        /*
         * If the ending value is 1, then a path was found, otherwise path is
         * non-existent and is NULL.
         */
        if (value == 1)
            path->does_path_exist = true;
        else {
            free (path->direction);
            free (path);
            path = NULL;
        }
    }

    /* Memory allocation error handling. */
MEM_ERROR:
    if (is_mem_invalid)
        printf ("Unable to allocate memory in %s %d\n.", __FILE__, __LINE__);
    if (is_mem_invalid && path->direction != NULL)
        free (path->direction);
    if (is_mem_invalid && path != NULL)
        free (path);

    return path;
}

/* Adds a step and direction to a path. */
static void
add_step (int tile[][TILESY*NBCHUNKS/2], EngPath *path, int dir_index,
          int *value, EngPoint2d starting_point, int offset_x, int offset_y)
{
    int index_x = starting_point.x + offset_x;
    int index_y = starting_point.y + offset_y;

    /* Add a direction step / direction when condition is true. */
    if (tile[index_x][index_y] < *value &&
        tile[index_x][index_y] > -1) {

        /* Determine which direction to get. */
        if (offset_x == -1)
            path->direction[dir_index] = ENG_LEFT;
        else if (offset_x == 1)
            path->direction[dir_index] = ENG_RIGHT;

        if (offset_y == -1)
            path->direction[dir_index] = ENG_UP;
        else if (offset_y == 1)
            path->direction[dir_index] = ENG_DOWN;

        *value = tile[index_x][index_y];
    }
}

/* Finds and removes all duplicate nodes. */
static int
remove_duplicates (EngNode *new_tiles, int nb_new_tiles)
{
    for (int i = 0; i < nb_new_tiles; i++) {
        for (int j = i + 1; j < nb_new_tiles; j++) {

            /* Find duplicate(s). */
            if (new_tiles[i].x == new_tiles[j].x &&
                new_tiles[i].y == new_tiles[j].y) {

                /*
                 * Once duplicate is found, write the data of the next index
                 * over it, repeat process until there is no more data to
                 * handle, then free one slot of memory.
                 */
                for (int k = j; k < nb_new_tiles - 1; k++) {
                    new_tiles[k].x = new_tiles[k + 1].x;
                    new_tiles[k].y = new_tiles[k + 1].y;
                    new_tiles[k].d = new_tiles[k + 1].d;
                }

                /* Decrease size of array. */
                nb_new_tiles -= 1;

                /*
                 * Decrementing j here makes it so we can identify multiple
                 * duplicates in a single iteration of i.
                 */
                j--;
            }
        }
    }

    return nb_new_tiles;
}

/*
 * Gives the array of tiles a value for each individual tile, corresponding
 * to a collision map, based on the array of chunks. Tiles will be assigned
 * -1 if the corresponding tile in the array of chunks has the collision set
 * to true, otherwise, tiles are assigned 0.
 */
static void
get_collision_map (EngChunk chunk[], int tile[][TILESY*NBCHUNKS/2])
{
    int order[NBCHUNKS];
    int index = 0;
    chunk_get_order_of_chunks (chunk, order);

    /* We iterate for every tile in the four chunks combined map. */
    for (int i = 0; i < TILESX * NBCHUNKS / 2; i++) {
        for (int j = 0; j < TILESY * NBCHUNKS / 2; j++) {

            /* Find the chunk index corresponding to the pair (i, j). */
            index = 0;
            if (i >= TILESX)
                index += 1;
            if (j >= TILESY)
                index += 2;

            /*
             * Finally, set the value of each tile to -1 if there is
             * collision on the original tile.
             */
            if (chunk[order[index]].tile[i % TILESX][j % TILESY].has_collision)
                tile[i % (TILESX * 2)][j % (TILESY * 2)] = -1;
            else
                tile[i % (TILESX * 2)][j % (TILESY * 2)] = 0;
        }
    }
}

/*
 * Returns the order of the chunks in this specific order: top-left: 0,
 * top-right: 1, bottom-left: 2, bottom-right: 3, where the numbers are
 * the index of the array.
 */
static void
chunk_get_order_of_chunks (EngChunk chunk[], int order[])
{
    /*
     * Sort in 2D to get the order of chunks, following the logic
     * of the eng_chunk_rotate_chunks functions.
     */
    if (NBCHUNKS > 3 && chunk[0].chunk_x < chunk[1].chunk_x &&
        chunk[0].chunk_y < chunk[2].chunk_y) {
        order[0] = 0;
        order[1] = 1;
        order[2] = 2;
        order[3] = 3;
    }
    else if (NBCHUNKS > 3 && chunk[0].chunk_x > chunk[1].chunk_x &&
             chunk[0].chunk_y < chunk[2].chunk_y) {
        order[0] = 1;
        order[1] = 0;
        order[2] = 3;
        order[3] = 2;
    }
    else if (NBCHUNKS > 3 && chunk[0].chunk_x < chunk[1].chunk_x &&
             chunk[0].chunk_y > chunk[2].chunk_y) {
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
respects_array_limits (EngPoint2d starting_point, EngPoint2d ending_point)
{
    bool result = true;

    if (starting_point.x < 0 || starting_point.y < 0 ||
        ending_point.x < 0 || ending_point.y < 0) {
        result = false;
    }
    else if (starting_point.x >= TILESX * NBCHUNKS / 2 ||
             starting_point.y >= TILESY * NBCHUNKS / 2 ||
             ending_point.x >= TILESX * NBCHUNKS / 2 ||
             ending_point.y >= TILESY * NBCHUNKS / 2) {
        result = false;
    }

    return result;
}

/* Frees memory allocated to a path. */
void
eng_pathfind_destroy_path (EngPath **path)
{
    EngPath *path_ptr = *path;

    if (*path != NULL) {
        if (path_ptr->direction != NULL) {
            free (path_ptr->direction);
            path_ptr->direction = NULL;
        }

        free (*path);
        *path = NULL;
    }
}
