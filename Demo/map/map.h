#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include "../../Mini_Engine/Engine/globals.h"

/**
 * @brief Keeps the map updated by rotating chunks, setting tile collisions
 *        and assigning object properties.
 *
 * @param chunk:     Array of chunk containing object and tile information.
 * @param character: Character used as reference point for updating.
 */
void map_handler (EngChunk chunk[], EngCharacter character);

#endif /* MAP_H_INCLUDED */
