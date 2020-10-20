/*===========================================================================*/
/* File: collision.cpp                                                       */
/* Author: YOAN BERNATCHEZ                                                   */
/* Created On: 2020-10-18                                                    */
/* Developed Using: SDL2                                                     */
/* Function: Provides a function that sets collision in chunks.              */
/*===========================================================================*/

#include "../../Mini_Engine/Engine/globals.h"
#include "../../Mini_Engine/Chunks/tile.h"
#include "collision.h"

/* Sets certain tiles in the array of chunks to have collision. */
void
set_map_collisions (EngChunk chunk[])
{
    for (int i = 0; i < 45; i++)
        eng_tile_set_collision (chunk, i, true);

    eng_tile_set_collision (chunk, 42, false);
}
