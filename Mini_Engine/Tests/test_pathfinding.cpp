#include <stdio.h>
#include <assert.h>
#include "../Chunks/chunk.h"
#include "../Chunks/tile.h"
#include "../Chunks/pathfinding.h"
#include "test_pathfinding.h"

static void test_pathfind_get_path (void);

void
test_pathfinding (void)
{
    printf("\n> Unit testing pathfinding functions...\n\n");
    test_pathfind_get_path();
}

static void
test_pathfind_get_path (void)
{
    EngPath *path;
    int nb_chunks = 4;
    int tiles_x = 64;
    int tiles_y = 64;
    EngChunk chunk[nb_chunks];

    for (int i = 0; i < nb_chunks; i++)
        chunk[i] = eng_chunk_create_chunk ();

    chunk[0].chunk_x = 0;
    chunk[0].chunk_y = 0;
    chunk[1].chunk_x = -1;
    chunk[1].chunk_y = 0;
    chunk[2].chunk_x = 0;
    chunk[2].chunk_y = -1;
    chunk[3].chunk_x = -1;
    chunk[3].chunk_y = -1;

    /* Test when the starting tile is a tile with collision. */
    chunk[0].tile[0][0].id = 0;
    chunk[0].tile[1][0].id = 1;
    eng_tile_set_collision (chunk, 0, true);
    path = eng_pathfind_get_path (chunk, tiles_x, tiles_y, tiles_x + 1,
                                  tiles_y);

    assert (path == NULL);


    /* Test when ending tile is a tile with collision. */
    path = eng_pathfind_get_path (chunk, tiles_x + 1, tiles_y, tiles_x,
                                  tiles_y);
    assert (path == NULL);

    /* Test when destination goes out of scope negatively. */
    eng_tile_set_collision (chunk, 0, false);
    path = eng_pathfind_get_path (chunk, tiles_x, tiles_y, -100, -200);
    assert (path == NULL);

    /* Test when destination goes out of scope positively. */
    eng_tile_set_collision (chunk, 0, false);
    path = eng_pathfind_get_path (chunk, tiles_x, tiles_y,
                                  tiles_x * (NBCHUNKS + 1),
                                  tiles_y * (NBCHUNKS + 1));
    assert (path == NULL);

    /* Test destination unreachable. */
    eng_tile_set_collision(chunk, 0, true);
    chunk[0].tile[0][0].has_collision = false;
    chunk[1].tile[tiles_x - 2][0].has_collision = false;
    path = eng_pathfind_get_path(chunk, tiles_x, tiles_y, tiles_x - 2, tiles_y);
    assert(path == NULL);


    /* Test starting point = ending point. */
    chunk[0].tile[0][0].has_collision = false;
    chunk[1].tile[0][0].has_collision = false;
    chunk[2].tile[0][0].has_collision = false;
    chunk[3].tile[0][0].has_collision = false;
    path = eng_pathfind_get_path (chunk, 66, 66, 66, 66);
    assert (path == NULL);

#if TILESX == 64 && TILESY == 64
    /*
     * Test path is found.
     * Note: This is hard to test if TILESX is different than tilesX or
     *       TILESY is different than tilesY
     */
    chunk[0].tile[0][0].has_collision = false;
    chunk[1].tile[tiles_x - 1][0].has_collision = false;
    chunk[1].tile[tiles_x - 2][0].has_collision = false;
    chunk[1].tile[tiles_x - 2][1].has_collision = false;
    chunk[1].tile[tiles_x - 2][2].has_collision = false;
    path = eng_pathfind_get_path (chunk, tiles_x, tiles_y, tiles_x - 2,
                                  tiles_y + 2);
    assert (path->nb_steps == 4);
    assert (path->does_path_exist);

    eng_pathfind_destroy_path (&path);
#endif

    for (int i = 0; i < nb_chunks; i++)
        eng_chunk_destroy (&chunk[i]);
}
