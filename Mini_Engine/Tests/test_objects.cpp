#include <assert.h>
#include <stdio.h>
#include "../Engine/globals.h"
#include "../Chunks/chunk.h"
#include "../Chunks/objects.h"
#include "test_objects.h"

static void test_object_load_objects (void);
static void test_object_get_nb_objects (void);
static void test_object_add_file_object (void);
static void test_object_remove_file_object (void);
static void test_object_modify_file_object (void);

void
test_objects (void)
{
    printf("\n> Unit testing object functions...\n\n");
    test_object_load_objects ();
    test_object_get_nb_objects ();
    test_object_add_file_object ();
    test_object_remove_file_object ();
    test_object_modify_file_object ();
}

static void
test_object_load_objects (void)
{
    EngChunk chunk = eng_chunk_create_chunk ();
    chunk.chunk_x = -2000;
    chunk.chunk_y = -2000;

    eng_object_load_objects (&chunk);

    assert (chunk.object[0].id == 5);
    assert (chunk.object[0].x == 200);
    assert (chunk.object[0].y == 10);

    assert (chunk.object[1].id == -2);
    assert (chunk.object[1].x == -10024);
    assert (chunk.object[1].y == 13);

    eng_chunk_destroy (&chunk);
}

static void
test_object_get_nb_objects (void)
{
    /* Regular test. */
    int nb_objects = eng_object_get_nb_objects (-2000, -2000);
    assert (nb_objects == 2);

    /* Test with non-existent file or empty file without objects. */
    nb_objects = eng_object_get_nb_objects (-2000000, -2000000);
    assert (nb_objects == 0);
}

static void
test_object_add_file_object (void)
{
    EngChunk chunk = eng_chunk_create_chunk ();
    int nb_objects = 0;
    chunk.chunk_x = -2000;
    chunk.chunk_y = -2000;

    /* We add an object in a file that already contains two. */
    eng_object_add_file_object (-2000, -2000, 57, 10, 320);
    eng_object_load_objects (&chunk);
    nb_objects = eng_object_get_nb_objects (-2000, -2000);

    assert (nb_objects == 3);
    assert (chunk.object[2].id == 57);
    assert (chunk.object[2].x == 10);
    assert (chunk.object[2].y == 320);

    /* Reset the file to its original content. */
    eng_object_remove_file_object (-2000, -2000, 2);

    eng_chunk_destroy (&chunk);
}

static void
test_object_remove_file_object (void)
{
    EngChunk chunk = eng_chunk_create_chunk ();
    int nb_objects = 0;
    chunk.chunk_x = -2000;
    chunk.chunk_y = -2000;

    /* We remove an object in a file that contains two. */
    eng_object_remove_file_object (-2000, -2000, 1);
    nb_objects = eng_object_get_nb_objects (-2000, -2000);

    assert (nb_objects == 1);

    /* Reset the file to its original content. */
    eng_object_add_file_object (-2000, -2000, -2, -10024, 13);

    eng_chunk_destroy (&chunk);
}

static void
test_object_modify_file_object (void)
{
    EngChunk chunk = eng_chunk_create_chunk ();
    chunk.chunk_x = -2000;
    chunk.chunk_y = -2000;

    eng_object_load_objects (&chunk);

    assert (chunk.object[0].id == 5);
    assert (chunk.object[0].x == 200);
    assert (chunk.object[0].y == 10);

    eng_object_modify_file_object (-2000, -2000, 0, -15, 24, 903);

    eng_object_load_objects (&chunk);

    assert (chunk.object[0].id == -15);
    assert (chunk.object[0].x == 24);
    assert (chunk.object[0].y == 903);

    /* Reset file to its original content. */
    eng_object_modify_file_object (-2000, -2000, 0, 5, 200, 10);

    eng_chunk_destroy (&chunk);
}
