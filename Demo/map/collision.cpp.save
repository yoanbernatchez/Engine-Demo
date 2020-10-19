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
