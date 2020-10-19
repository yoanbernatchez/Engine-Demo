#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "../Chunks/chunk.h"
#include "test_chunk.h"

static void test_chunk_init (void);
static void test_chunk_rotate_chunk (void);
static void test_chunk_get_file_name (void);

void
test_chunk (void)
{
    printf("\n> Unit testing chunk functions...\n\n");
    test_chunk_init();
    test_chunk_rotate_chunk();
    test_chunk_get_file_name();
}

static void
test_chunk_init (void)
{
    EngChunk chunk[NBCHUNKS];

    for (int i = 0; i < NBCHUNKS; i++)
        chunk[i] =  eng_chunk_create_chunk ();

    /* Testing chunkInit (simple assignment). */
    eng_chunk_set_main_chunk (chunk, -5, 5);
    assert (chunk[0].chunk_x == -5);
    assert (chunk[0].chunk_y == 5);

    for (int i = 0; i < NBCHUNKS; i++)
        eng_chunk_destroy (&chunk[i]);
}

static void
test_chunk_rotate_chunk (void)
{
    EngChunk chunk[NBCHUNKS];
    for (int i = 0; i < NBCHUNKS; i++)
        chunk[i] = eng_chunk_create_chunk ();

    /*
     * Testing chunkRotateChunks (4 scenarios).
     * Case: (3, 2) on chunk 0, 0
     *       (1, 0)
     */
    eng_chunk_rotate_chunks (chunk, 0, 0, 0, 0);
    assert (chunk[0].chunk_x == 0);
    assert (chunk[0].chunk_y == 0);
    assert (chunk[1].chunk_x == -1);
    assert (chunk[1].chunk_y == 0);
    assert (chunk[2].chunk_x == 0);
    assert (chunk[2].chunk_y == -1);
    assert (chunk[3].chunk_x == -1);
    assert (chunk[3].chunk_y == -1);

    /*
     * Case: (2, 3) in close negatives
     *       (0, 1)
     */
    eng_chunk_rotate_chunks (chunk, -1, 0, -1, 0);
    assert (chunk[0].chunk_x == -1);
    assert (chunk[0].chunk_y == 0);
    assert (chunk[1].chunk_x == 0);
    assert (chunk[1].chunk_y == 0);
    assert (chunk[2].chunk_x == -1);
    assert (chunk[2].chunk_y == -1);
    assert (chunk[3].chunk_x == 0);
    assert (chunk[3].chunk_y == -1);

    /*
     * Case: (0, 1) in far negatives
     *       (2, 3)
     */
    eng_chunk_rotate_chunks (chunk, -1 -10 * TILESIZE * TILESX,
                             -1 -10 * TILESIZE * TILESY, -10, -10);
    assert (chunk[0].chunk_x == -10);
    assert (chunk[0].chunk_y == -10);
    assert (chunk[1].chunk_x == -9);
    assert (chunk[1].chunk_y == -10);
    assert (chunk[2].chunk_x == -10);
    assert (chunk[2].chunk_y == -9);
    assert (chunk[3].chunk_x == -9);
    assert (chunk[3].chunk_y == -9);

    /*
     * Case: (1, 0) in far positives
     *       (3, 2)
     */

    eng_chunk_rotate_chunks (chunk, 4 * TILESIZE * TILESX + 1,
                             TILESIZE * TILESY / 2 + 5 * TILESIZE * TILESY,
                             4, 5);
    assert (chunk[0].chunk_x == 4);
    assert (chunk[0].chunk_y == 5);
    assert (chunk[1].chunk_x == 3);
    assert (chunk[1].chunk_y == 5);
    assert (chunk[2].chunk_x == 4);
    assert (chunk[2].chunk_y == 6);
    assert (chunk[3].chunk_x == 3);
    assert (chunk[3].chunk_y == 6);

    for (int i = 0; i < NBCHUNKS; i++)
        eng_chunk_destroy (&chunk[i]);
}

static void
test_chunk_get_file_name (void)
{
    assert (strcmp (eng_chunk_get_file_name (-5, 4),
                    "Demo/chunks/-5,4.txt") == 0);
    assert (strcmp (eng_chunk_get_file_name (0, 1934),
                    "Demo/chunks/0,1934.txt") == 0);
}
