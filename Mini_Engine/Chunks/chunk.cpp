#include <stdio.h>
#include <string.h>
#include "chunk.h"
#include "tile.h"
#include "objects.h"

/*---------------------------------------------------------------------------*/
/* Local function prototypes                                                 */
/*---------------------------------------------------------------------------*/

/**
 * @brief Sets the updated state of all chunks to false if they had a change in
 *        chunk id.
 *
 * @param chunk: Array of chunks to update.
 */
static void set_chunk_update_state (EngChunk chunk[]);

/*---------------------------------------------------------------------------*/
/* Chunk functions implementation                                            */
/*---------------------------------------------------------------------------*/

/* Sets the main chunk's (chunk[0]) position. */
void
eng_chunk_set_main_chunk (EngChunk chunk[], int chunk_x, int chunk_y)
{
    /* Sets a certain starting chunk. */
    if (NBCHUNKS > 0) {
        chunk[0].chunk_x = chunk_x;
        chunk[0].chunk_y = chunk_y;
    }
    else
        printf("Impossible to initiate an empty chunk array.\n");
}

/*
 * Loads data such as tile data and object data to a singular chunk, determined
 * by the chunkIndex.
 */
bool
eng_chunk_load_chunk (EngChunk *chunk, bool force_load)
{
    bool result = false;

    /* Load tile and object data into one chunk. */
    if (!chunk->updated || force_load) {
        eng_chunk_destroy (chunk);
        eng_tile_load_tiles (chunk);
        eng_object_load_objects (chunk);
        chunk->updated = true;
        result = true;
    }

    return result;
}

/*
 * Loads data such as tile data and object data to all chunks in the array of
 * chunks sent in parameters.
 */
bool
eng_chunk_load_chunks (EngChunk chunk[], bool force_load)
{
    bool result = false;

    /* Load tile and object data for all chunks. */
    for (int i = 0; i < NBCHUNKS; i++) {
        if (!result)
            result = eng_chunk_load_chunk (&chunk[i], force_load);
        else
            eng_chunk_load_chunk (&chunk[i], force_load);
    }

    return result;
}

/*
 * This function updates the chunkX and chunkY coordinates for every chunk in
 * the chunk array and rotates the chunks based on character coordinates
 * if necessary.
 * chunk[0] is the main chunk and always contains the selected character.
 * chunk[1] is the horizontal chunk.
 * chunk[2] is the vertical chunk.
 * chunk[3] is the diagonal chunk.
 */
bool
eng_chunk_rotate_chunks (EngChunk chunk[], int char_x, int char_y,
                         int char_chunk_x, int char_chunk_y)
{
    int chunk_pixel_lenght = TILESIZE * TILESX; /* Length of chunk in pixels.*/
    int chunk_pixel_height = TILESIZE * TILESY; /* Height of chunk in pixels.*/

    /* Save chunk data to oldChunk. */
    for (int i = 0; i < NBCHUNKS; i++) {
        chunk[i].old_chunk_x = chunk[i].chunk_x;
        chunk[i].old_chunk_y = chunk[i].chunk_y;
    }

    /* Update main chunk to be the one the character is in. */
    if (NBCHUNKS > 0) {
        chunk[0].chunk_x = char_chunk_x;
        chunk[0].chunk_y = char_chunk_y;
    }

    /*
     * Horizontal chunk update.
     * The horizontal chunk is always chunkX[0] - 1 or chunkX[0] + 1 and
     * chunkY[0], depending on the selected character's coordinates.
     */
    if (NBCHUNKS > 1) {
        if (char_x >= char_chunk_x * chunk_pixel_lenght &&
            char_x < char_chunk_x * chunk_pixel_lenght +
            chunk_pixel_lenght / 2) {
            chunk[1].chunk_x = chunk[0].chunk_x - 1;
        }
        else {
            chunk[1].chunk_x = chunk[0].chunk_x + 1;
        }

        chunk[1].chunk_y = chunk[0].chunk_y;
    }

    /*
     * Vertical chunk update.
     * The vertical chunk is always chunkX[0] and chunkY[0] - 1
     * or chunkY[0] + 1, depending on the selected character's coordinates.
     */
    if (NBCHUNKS > 2) {
        if (char_y >= char_chunk_y * chunk_pixel_height &&
            char_y < char_chunk_y * chunk_pixel_height +
            chunk_pixel_height / 2) {
            chunk[2].chunk_y = chunk[0].chunk_y - 1;
        }
        else {
            chunk[2].chunk_y = chunk[0].chunk_y + 1;
        }
        chunk[2].chunk_x = chunk[0].chunk_x;
    }

    /*
     * Diagonal chunk update.
     * The diagonal chunk always has the same chunkX value as the horizontal
     * chunk and the same chunkY value as the vertical chunk.
     */
    if (NBCHUNKS > 3) {
        chunk[3].chunk_x = chunk[1].chunk_x;
        chunk[3].chunk_y = chunk[2].chunk_y;
    }

    /* Update the chunks' update states. */
    set_chunk_update_state (chunk);

    /* Update chunks if there was a change. */
    return eng_chunk_load_chunks (chunk, false);
}

/*
 * Sets the updated state of all chunks to false if they had a change in chunk
 * id.
 */
static void
set_chunk_update_state (EngChunk chunk[])
{
    for (int i = 0; i < NBCHUNKS; i++) {
        if (chunk[i].chunk_x != chunk[i].old_chunk_x ||
            chunk[i].chunk_y != chunk[i].old_chunk_y) {
            chunk[i].updated = false;
        }
    }
}

/* Returns a file name corresponding to the directory of a chunk data file. */
const char *
eng_chunk_get_file_name (int chunk_x, int chunk_y)
{
    char fileName[30];

    sprintf (fileName, "Demo/chunks/%d,%d.txt", chunk_x, chunk_y);

    return strdup (fileName);
}

/* Creates and initializes a chunk, then returns it. */
EngChunk
eng_chunk_create_chunk (void)
{
    EngChunk chunk;

    chunk.old_chunk_x = 0;
    chunk.old_chunk_y = 0;
    chunk.chunk_x = 0;
    chunk.chunk_y = 0;
    chunk.nb_objects = 0;
    chunk.updated = false;

    for (int i = 0; i < TILESX; i++) {
        for (int j = 0; j < TILESY; j++)
            chunk.tile[i][j] = eng_tile_create_tile ();
    }

    return chunk;
}

/* Frees memory of the dynamically allocated members of the chunk. */
void
eng_chunk_destroy (EngChunk *chunk)
{
    eng_tile_reset_collision (chunk);
    eng_object_deallocate (chunk);
}
