#ifndef COLLISION_H_INCLUDED
#define COLLISION_H_INCLUDED

#include "../../Mini_Engine/Engine/globals.h"

/**
 * @brief Sets certain tiles in the array of chunks to have collision.
 *
 * @param chunk: Array of chunk to modify collision of.
 */
void set_map_collisions (EngChunk chunk[]);

#endif /* COLLISION_H_INCLUDED */
