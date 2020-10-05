#ifndef CHUNK_HEADER_H_INCLUDED
#define CHUNK_HEADER_H_INCLUDED

#include <SDL.h>
#include "../Engine/globals.h"

/**
 * @brief Sets the main chunk's (chunk[0]) position.
 *
 * @param chunk:  Chunk array to be modified.
 * @param chunkX: The chunk in x to set to the main chunk.
 * @param chunkY: The chunk in y to set to the main chunk.
 */
void chunkSetMainChunk(Chunk chunk[], int chunkX, int chunkY);

/**
 * @brief Loads tile and object data to a chunk.
 *
 * @param chunk:      Array of chunks used to store tile data, object data
 *                    and more.
 * @param chunkIndex: The index of the chunk array to load data into.
 *
 * @param forceLoad: True if there is a need to update without checking
 *                   if the chunk has been updated.
 *
 * @sa chunkLoadChunks()
 */
void chunkLoadChunk(Chunk chunk, bool forceLoad);

/**
 * @brief Loads tile and object data to all chunks in the array of chunks
 *        in parameters.
 *
 * @param chunk: Array of chunks to fill with data such as tile data and
 *               object data.
 *
 * @param forceLoad: True if there is a need to update without checking
 *                   if the chunk has been updated.
 *
 * @sa chunkLoadChunk()
 */
void chunkLoadChunks(Chunk chunk[], bool forceLoad);

/**
 * @brief Rotates chunks based on character coordinates.
 *
 * @param chunk: Chunk array containing tile and object data.
 * @param charX: Position of the character in x.
 * @param charY: Position of the character in y.
 * @param charChunkX: Chunk in which the character currently is in (in x).
 * @param charChunkY: Chunk in which the character currently is in (in y).
 */
void chunkRotateChunks(Chunk chunk[], int charX, int charY, int charChunkX, int charChunkY);

/**
 * @brief Returns a file name corresponding to the directory of a chunk data
 *        file.
 *
 * @param chunkX: The chunk in x which we are trying to get the file name of.
 * @param chunkY: The chunk in y which we are trying to get the file name of.
 *
 * @return A string containing the directory of the wanted chunk data file.
 */
const char* chunkGetFileName(int chunkX, int chunkY);

/**
 * @brief Creates an initializes a chunk, then returns it.
 *
 * @return A new initialized chunk.
 */
Chunk chunkCreateChunk(void);

/**
 * @brief Frees memory of the dynamically allocated members of the chunk.
 *
 * @param chunk: Chunk to free.
 */
void chunkDestroy(Chunk *chunk);

#endif /* CHUNK_HEADER_H_INCLUDED */
