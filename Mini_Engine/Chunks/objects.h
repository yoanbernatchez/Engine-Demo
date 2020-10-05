#ifndef OBJECTS_H_INCLUDED
#define OBJECTS_H_INCLUDED

#include "../Engine/globals.h"

/**
 * @brief Scans the chunk file and returns the number of objects present in
 *        the file.
 *
 * @param chunkX: The chunk id of the file in x corresponding to the chunk to
 *                scan.
 * @param chunkY: The chunk id of the file in y corresponding to the chunk to
 *                scan.
 *
 * @return The number of objects in the chunk specified in parameters.
 */
int objectGetNbObjects(int chunkX, int chunkY);

/**
 * @brief Adds the data for an object at the end of the object list in a
 *        chunk file.
 *
 * @param chunkX: The chunk id of the file in x corresponding to the chunk to
 *                modify.
 * @param chunkY: The chunk id of the file in y corresponding to the chunk to
 *                modify.
 * @param id:     Id of the object to add to file.
 * @param x:      Position in x of the object to add to file.
 * @param y:      Position in y of the object to add to file.
 *
 * @sa objectRemoveFileObject() objectModifyFileObject()
 */
void objectAddFileObject(int chunkX, int chunkY, int id, int x, int y);

/**
 * @brief Finds the nth object in a chunk file and deletes its data from the
 *        file.
 *
 * @param chunkX: The chunk id of the file in x corresponding to the chunk to
 *                modify.
 * @param chunkY: The chunk id of the file in y corresponding to the chunk to
 *                modify.
 * @param index:  Index corresponding to the object to remove in the file.
 *
 * @sa objectAddFileObject() objectModifyFileObject()
 */
void objectRemoveFileObject(int chunkX, int chunkY, int index);

/**
 * @brief Modifies the object data stored in a chunk file with new values.
 *
 * @param chunkX: The chunk id of the file in x corresponding to the chunk
 *                to modify.
 * @param chunkY: The chunk id of the file in y corresponding to the chunk
 *                to modify.
 * @param index:  The index indicating which object to modify in the file.
 * @param id:     The new id of the object.
 * @param x:      The new location in x of the object.
 * @param y:      The new location in y of the object.
 *
 * @sa objectAddFileObject() objectRemoveFileObject()
 */
void objectModifyFileObject(int chunkX, int chunkY, int index, int id, int x, int y);

/**
 * @brief Stores object data coming from file to the chunk in parameters.
 *
 * @param chunk:      Array of chunks to load objects to.
 * @param chunkIndex: Index of the chunk to load objects to.
 */
void objectLoadObjects(Chunk *chunk);

/**
 * @brief This function needs to be called at the end of the program to cleanly
 *        exit, frees the memory taken by the dynamic array "object".
 *
 * @param chunk: Chunk containing objects with memory to deallocate.
 */
void objectDeallocate(Chunk *chunk);

#endif /* OBJECTS_H_INCLUDED */
