#include <assert.h>
#include <stdio.h>
#include "../Engine/globals.h"
#include "../Chunks/chunk.h"
#include "../Chunks/tile.h"
#include "test_tile.h"

static void test_tile_modify_tile_id (void);
static void test_tile_load_tiles (void);

void
test_tile (void)
{
    printf("\n> Unit testing tile functions...\n\n");
    test_tile_modify_tile_id ();
    test_tile_load_tiles ();
}

static void
test_tile_modify_tile_id (void)
{
    EngChunk chunk = eng_chunk_create_chunk ();
    /* All tiles in this file are of id 14. */
    chunk.chunk_x = -2000;
    chunk.chunk_y = -2000;

    /* We make a change to the tile x: 0, y: 0 in the file. */
    eng_tile_modify_file_id (-2000, -2000, 0, 0, 12);
    eng_tile_load_tiles (&chunk);

    assert (chunk.tile[0][0].id == 12);

#if TILESX >= 20 && TILESY >= 19
    /* We make a change to the tile x: 20, y: 19 in the file. */
    eng_tile_modify_file_id (-2000, -2000, 20, 19, 6);
    eng_tile_load_tiles (&chunk);

    assert (chunk.tile[20][19].id == 6);
#endif

    /* Reset the file to its original content. */
    eng_tile_modify_file_id (-2000, -2000, 0, 0, 14);
    eng_tile_modify_file_id (-2000, -2000, 20, 19, 14);

    /*
     * Now we try to make a change that is out of bounds and check
     * that all tiles are still 14.
     */
    eng_tile_modify_file_id (-2000, -2000, -10, 4805, 34);
    eng_tile_load_tiles (&chunk);

    for (int i = 0; i < TILESX; i++) {
        for (int j = 0; j < TILESY; j++) {
            assert (chunk.tile[i][j].id == 14);
        }
    }

    eng_chunk_destroy (&chunk);
}

static void
test_tile_load_tiles (void)
{
    EngChunk chunk = eng_chunk_create_chunk ();
    chunk.chunk_x = -2000;
    chunk.chunk_y = -2000;

    /* Load a chunk file that contains only tiles with the id 14. */
    eng_tile_load_tiles (&chunk);

    for (int i = 0; i < TILESX; i++) {
        for (int j = 0; j < TILESY; j++) {
            assert (chunk.tile[i][j].id == 14);
        }
    }

    eng_chunk_destroy (&chunk);
}
