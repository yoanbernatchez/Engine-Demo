#ifndef TILE_H_INCLUDED
#define TILE_H_INCLUDED

#include "../Engine/globals.h"

/**
 * @brief Stores tile data coming from a chunk file to a chunk.
 *
 * @param chunk: The chunk we load tiles to.
 */
void eng_tile_load_tiles (EngChunk *chunk);

/**
 * @brief Sets the collision of all tiles with a certain id to true or false.
 *
 * @param chunk:         The array of chunk to modify the collision of.
 * @param id:            The tile id to turn on collision for.
 * @param has_collision: True if we want to give collision, false if we don't.
 *
 * @sa eng_tile_reset_collision ()
 */
void eng_tile_set_collision (EngChunk chunk[], int id, bool has_collision);

/**
 * @brief Resets the collision of a chunk to false.
 *
 * @param chunk: Chunk in which to reset collision on.
 *
 * @sa eng_tile_set_collision ()
 */
void eng_tile_reset_collision (EngChunk *chunk);

/**
 * @brief Modifies the value of a tile in a chunk text file.
 *
 * @param chunk_x: The chunk id in x for the file to modify.
 * @param chunk_y: The chunk id in y for the file to modify.
 * @param tile_x:  The tile in x to be modify in the chunk file.
 * @param tile_y:  The tile in y to be modify in the chunk file.
 * @param new_id:  New tile id to replace the old tile id.
 */
void eng_tile_modify_file_id (int chunk_x, int chunk_y, int tile_x, int tile_y,
                              int new_id);

/**
 * @brief Creates an initializes a tile, then returns it.
 *
 * @return A new initialized tile.
 */
EngTile eng_tile_create_tile (void);

#endif /* TILE_H_INCLUDED */
