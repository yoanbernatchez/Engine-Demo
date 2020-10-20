/*===========================================================================*/
/* File: map.cpp                                                             */
/* Author: YOAN BERNATCHEZ                                                   */
/* Created On: 2020-10-18                                                    */
/* Developed Using: SDL2                                                     */
/* Function: Provides a function that handles changes in the map and updates */
/*           it.                                                             */
/*===========================================================================*/

#include <stdbool.h>
#include "../../Mini_Engine/Chunks/chunk.h"
#include "../../Mini_Engine/Characters/character.h"
#include "../objects/objects.h"
#include "collision.h"

/*
 * Keeps the map updated by rotating chunks, setting tile collisions
 * and assigning object properties.
 */
void
map_handler (EngChunk chunk[], EngCharacter character)
{
    bool is_map_changed = false;
    int char_chunk_x = eng_char_get_chunk_x (character.x);
    int char_chunk_y = eng_char_get_chunk_y (character.y);

    is_map_changed = eng_chunk_rotate_chunks (chunk,
                                              character.x,
                                              character.y,
                                              char_chunk_x,
                                              char_chunk_y);
    if (is_map_changed) {
        set_map_collisions (chunk);
        object_assign_properties (chunk);
    }
}
