#ifndef OBJECTS_H_INCLUDED
#define OBJECTS_H_INCLUDED

#include "../Engine/globals.h"

/**
 * @brief Scans a chunk file and returns the number of objects present in
 *        the file.
 *
 * @param chunk_x: The chunk id of the file in x corresponding to the chunk to
 *                 scan.
 * @param chunk_y: The chunk id of the file in y corresponding to the chunk to
 *                 scan.
 *
 * @return The number of objects in the chunk specified in parameters.
 */
int eng_object_get_nb_objects (int chunk_x, int chunk_y);

/**
 * @brief Adds the data for an object at the end of the object list in a
 *        chunk file.
 *
 * @param chunk_x: The chunk id of the file in x corresponding to the chunk to
 *                 modify.
 * @param chunk_y: The chunk id of the file in y corresponding to the chunk to
 *                 modify.
 * @param id:      Id of the object to add to file.
 * @param x:       Position in x of the object to add to file.
 * @param y:       Position in y of the object to add to file.
 *
 * @sa eng_object_remove_file_object () eng_object_modify_file_object ()
 */
void eng_object_add_file_object (int chunk_x, int chunk_y, int id,
                                 int x, int y);

/**
 * @brief Finds the nth object in a chunk file and deletes its data from the
 *        file.
 *
 * @param chunk_x: The chunk id of the file in x corresponding to the chunk to
 *                 modify.
 * @param chunk_y: The chunk id of the file in y corresponding to the chunk to
 *                 modify.
 * @param index:   Index corresponding to the object to remove in the file.
 *
 * @sa eng_object_add_file_object () eng_object_modify_file_object ()
 */
void eng_object_remove_file_object (int chunk_x, int chunk_y, int index);

/**
 * @brief Modifies the object data stored in a chunk file with new values.
 *
 * @param chunk_x: The chunk id of the file in x corresponding to the chunk
 *                 to modify.
 * @param chunk_y: The chunk id of the file in y corresponding to the chunk
 *                 to modify.
 * @param index:   The index indicating which object to modify in the file.
 * @param id:      The new id of the object.
 * @param x:       The new location in x of the object.
 * @param y:       The new location in y of the object.
 *
 * @sa eng_object_add_file_object () eng_object_remove_file_object ()
 */
void eng_object_modify_file_object (int chunk_x, int chunk_y, int index,
                                    int id, int x, int y);

/**
 * @brief Stores object data coming from file to the chunk in parameters.
 *
 * @param chunk: Chunk to load objects to.
 */
void eng_object_load_objects (EngChunk *chunk);

/**
 * @brief Frees memory allocated to objects in a chunk.
 *
 * @param chunk: Chunk containing objects with memory to deallocate.
 */
void eng_object_deallocate (EngChunk *chunk);

#endif /* OBJECTS_H_INCLUDED */
