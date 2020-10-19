#ifndef CHUNK_HEADER_H_INCLUDED
#define CHUNK_HEADER_H_INCLUDED

#include <stdbool.h>
#include <SDL.h>
#include "../Engine/globals.h"

/**
 * @brief Sets the main chunk's (chunk[0]) position.
 *
 * @param chunk:   Chunk array to be modified.
 * @param chunk_x: The chunk in x to set to the main chunk.
 * @param chunk_y: The chunk in y to set to the main chunk.
 */
void eng_chunk_set_main_chunk (EngChunk chunk[], int chunk_x, int chunk_y);

/**
 * @brief Loads tile and object data to a chunk.
 *
 * @param chunk:       Chunk to store data to.
 * @param chunk_index: The index of the chunk array to load data into.
 * @param force_load:  True if there is a need to update without checking
 *                     if the chunk has been updated.
 *
 * @return True if the chunk was changed and loaded, false otherwise.
 *
 * @sa eng_chunk_load_chunks ()
 */
bool eng_chunk_load_chunk (EngChunk *chunk, bool force_load);

/**
 * @brief Loads tile and object data to all chunks in the array of chunks
 *        in parameters.
 *
 * @param chunk:      Array of chunks to fill with data such as tile data and
 *                    object data.
 * @param force_load: True if there is a need to update without checking
 *                    if the chunk has been updated.
 *
 * @return True if at least one chunk changed and loaded, false otherwise.
 *
 * @sa eng_chunk_load_chunk ()
 */
bool eng_chunk_load_chunks (EngChunk chunk[], bool force_load);

/**
 * @brief Rotates chunks based on character coordinates.
 *
 * @param chunk:        Chunk array containing tile and object data.
 * @param char_x:       Position of the character in x.
 * @param char_y:       Position of the character in y.
 * @param char_chunk_x: Chunk in which the character currently is in (in x).
 * @param char_chunk_y: Chunk in which the character currently is in (in y).
 *
 * @return True if at least one chunk changed and loaded, false otherwise.
 */
bool eng_chunk_rotate_chunks (EngChunk chunk[], int char_x, int char_y,
                              int char_chunk_x, int char_chunk_y);

/**
 * @brief Returns a file name corresponding to the directory of a chunk data
 *        file.
 *
 * @param chunk_x: The chunk in x which we are trying to get the file name of.
 * @param chunk_y: The chunk in y which we are trying to get the file name of.
 *
 * @return A string containing the directory of the wanted chunk data file.
 */
const char * eng_chunk_get_file_name (int chunk_x, int chunk_y);

/**
 * @brief Creates and initializes a chunk, then returns it.
 *
 * @return A new initialized chunk.
 */
EngChunk eng_chunk_create_chunk (void);

/**
 * @brief Frees memory of the dynamically allocated members of the chunk.
 *
 * @param chunk: Chunk to free.
 */
void eng_chunk_destroy (EngChunk *chunk);

#endif /* CHUNK_HEADER_H_INCLUDED */
