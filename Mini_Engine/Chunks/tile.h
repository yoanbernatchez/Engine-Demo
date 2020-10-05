#ifndef TILE_H_INCLUDED
#define TILE_H_INCLUDED

#include "../Engine/globals.h"

/**
 * @brief Stores tile data coming from a file to a chunk.
 *
 * @param chunk: Array of chunks where the tile data will be stored.
 * @param chunkX: The chunk id in x containing the information we are trying to load.
 * @param chunkY: The chunk id in y containing the information we are trying to load.
 * @param chunkIndex: The index of the chunk array to which the tile data is saved to.
 */
void tileLoadTiles(Chunk *chunk);

/**
 * @brief Sets the collision of all tiles with a certain id to true or false.
 *
 * @param chunk:        The array of chunk to modify the collision of.
 * @param id:           The tile id to turn on collision.
 * @param hasCollision: True if we want to give collision, false if we don't.
 */
void tileSetCollision(Chunk chunk[], int id, bool hasCollision);

/**
 * @brief Modifies the value of a tile in a chunk text file.
 *
 * @param chunkX: The chunk id in x for the file to modify.
 * @param chunkY: The chunk id in y for the file to modify.
 * @param tileX:  The tile in x to be modify in the chunk file.
 * @param tileY:  The tile in y to be modify in the chunk file.
 * @param newId:  New tile id to replace the old tile id.
 */
void tileModifyFileId(int chunkX, int chunkY, int tileX, int tileY, int newId);

/**
 * @brief Creates an initializes a tile, then returns it.
 *
 * @return A new initialized tile.
 */
Tile tileCreateTile(void);

#endif /* TILE_H_INCLUDED */
