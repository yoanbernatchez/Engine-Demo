#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "chunk.h"
#include "../File_Utilities/file_utilities.h"

/*---------------------------------------------------------------------------*/
/* Local function prototypes                                                 */
/*---------------------------------------------------------------------------*/

/**
 * @brief Takes in a tile id from a formatted file and returns the id.
 *
 * @param file: The file being scanned.
 *
 * @return The id of the tile that was read from a file.
 */
static int get_id_from_file (FILE *file);

/*---------------------------------------------------------------------------*/
/* Tile function implementations                                             */
/*---------------------------------------------------------------------------*/

/* Modifies the value of a tile in a chunk text file. */
void
eng_tile_modify_file_id (int chunk_x, int chunk_y, int tile_x, int tile_y,
                         int new_id)
{
    FILE *file;
    char buffer[20];
    char c = '!';
    const char *file_name = eng_chunk_get_file_name (chunk_x, chunk_y);
    int cursor_index = 0;
    int start_index = 0;
    int end_index = 0;
    int comma = 0;

    /* Seek the location of tile data. */
    cursor_index = eng_file_get_index_after_string (file_name, "tile{");

    file = fopen (file_name, "r");

    if (file != NULL && cursor_index >= 0 && tile_x >= 0 && tile_y >= 0 &&
        new_id >= 0) {
        /* Advance file cursor to tile data. */
        fseek (file, cursor_index, SEEK_SET);

        /*
         * In file, advance to the position of the desired tile data. Here,
         * since data is delimited by commas, we simply advance the the nth
         * comma which associated with the tile we are looking for.
         */
        while (comma < tile_x + TILESX * tile_y && c != '}' && !feof (file)) {
            c = fgetc (file);

            if (c == ',')
                comma++;
        }

        if (c != '}') {
            start_index = ftell (file);

            c = fgetc (file);

            /*
             * In file, advance to the position after the comma of the desired
             * tile.
             */
            while (c != ',' && c != '}' && !feof (file))
                c = fgetc (file);

            /*
             * We remove 1 from the endIndex because we do not want the ,
             * to be included.
             */
            end_index = ftell (file) - 1;

            eng_file_close_file (file);

            eng_file_replace_with_string (file_name, itoa (new_id, buffer, 10),
                                          start_index, end_index);
        }
        else {
            printf ("Error: tile requested is out of bounds in file %s\n",
                    file_name);
        }
    }

    free ((char*) file_name);
    file = eng_file_close_file (file);
}

/*
 * Stores tile data coming from the file corresponding to chunk_x and chunk_y
 * into a chunk.
 */
void
eng_tile_load_tiles (EngChunk *chunk)
{
    FILE *file;
    int cursor_index = 0;
    int error = 0;

    const char *file_name =
    eng_chunk_get_file_name (chunk->chunk_x, chunk->chunk_y);

    /* Seek the location of tile data. */
    cursor_index = eng_file_get_index_after_string (file_name, "tile{");

    file = fopen (file_name, "r");

    if (file != NULL && cursor_index >= 0) {
        /* Advance file cursor to tile data. */
        fseek (file, cursor_index, SEEK_SET);

        /* Retrieve and store tile ids. */
        for (int y = 0; y < TILESY; y++) {
            for (int x = 0; x < TILESX; x++) {
                chunk->tile[x][y].id = get_id_from_file (file);

                if (chunk->tile[x][y].id == -1)
                    error++;
            }
        }

        /* Handle expected more tiles. */
        if (error > 0) {
            printf ("%d tile id(s) could not be retrieved from \"%s\"\n",
                    error, file_name);
        }
    }
    else
        printf ("Impossible to load tiles, chunk index is out of scope.\n");

    free ((char*) file_name);
    file = eng_file_close_file (file);
}

/* Takes in a tile id from a formatted file and returns the id. */
static int
get_id_from_file (FILE *file)
{
    int id = -1;

    fscanf (file, "%d,", &id);

    return id;
}

/* Sets the collision of all tiles with a certain id to true or false. */
void
eng_tile_set_collision (EngChunk chunk[], int id, bool has_collision)
{
    for (int i = 0; i < NBCHUNKS; i++) {
        for (int x = 0; x < TILESX; x++) {
            for (int y = 0; y < TILESY; y++) {
                if (chunk[i].tile[x][y].id == id)
                    chunk[i].tile[x][y].has_collision = has_collision;
            }
        }
    }
}

/* Resets the collision for every tile to false. */
void
eng_tile_reset_collision(EngChunk *chunk)
{
    for (int x = 0; x < TILESX; x++) {
        for (int y = 0; y < TILESY; y++)
            chunk->tile[x][y].has_collision = false;
    }
}

/* Creates an initializes a tile, then returns it. */
EngTile
eng_tile_create_tile (void)
{
    EngTile tile;

    tile.id = 0;
    tile.frame = 0;
    tile.has_collision = false;

    return tile;
}
