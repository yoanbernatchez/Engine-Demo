#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../File_Utilities/file_utilities.h"
#include "tile.h"
#include "chunk.h"

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
static int getIdFromFile(FILE* file);

/*---------------------------------------------------------------------------*/
/* Tile function implementations                                             */
/*---------------------------------------------------------------------------*/

/* Modifies the value of a tile in a chunk text file. */
void
tileModifyFileId(int chunkX, int chunkY, int tileX, int tileY, int newId)
{
    FILE* file;
    char buffer[20];
    char c = '!';
    const char* fileName = chunkGetFileName(chunkX, chunkY);
    int cursorIndex = 0;
    int startIndex = 0;
    int endIndex = 0;
    int comma = 0;

    /* Seek the location of tile data. */
    cursorIndex = fileGetIndexAfterString(fileName, "tile{");

    file = fopen(fileName, "r");

    if (file != NULL && cursorIndex >= 0 && tileX >= 0 && tileY >= 0 &&
        newId >= 0) {
        /* Advance file cursor to tile data. */
        fseek(file, cursorIndex, SEEK_SET);

        /*
         * In file, advance to the position of the desired tile data. Here,
         * since data is delimited by commas, we simply advance the the nth
         * comma which associated with the tile we are looking for.
         */
        while (comma < tileX + TILESX * tileY && c != '}' && !feof(file)) {
            c = fgetc(file);

            if (c == ',') {
                comma++;
            }
        }

        if (c != '}') {
            startIndex = ftell(file);

            c = fgetc(file);

            /*
             * In file, advance to the position after the comma of the desired
             * tile.
             */
            while (c != ',' && c != '}' && !feof(file)) {
                c = fgetc(file);
            }

            /*
             * We remove 1 from the endIndex because we do not want the ,
             * to be included.
             */
            endIndex = ftell(file) - 1;

            fileCloseFile(file);

            fileReplaceWithString(fileName, itoa(newId, buffer, 10),
                                  startIndex, endIndex);
        }
        else {
            printf("Error: tile requested is out of bounds in file %s\n",
                   fileName);
        }
    }

    fileCloseFile(file);
}

/*
 * Stores tile data coming from the file corresponding to chunkX and chunkY
 * into chunk[chunkIndex].
 */
void
tileLoadTiles(Chunk *chunk)
{
    FILE* file;
    int cursorIndex = 0;
    int error = 0;

    const char* fileName =
    chunkGetFileName(chunk->chunkX, chunk->chunkY);

    /* Seek the location of tile data. */
    cursorIndex = fileGetIndexAfterString(fileName, "tile{");

    file = fopen(fileName, "r");

    if (file != NULL && cursorIndex >= 0) {
        /* Advance file cursor to tile data. */
        fseek(file, cursorIndex, SEEK_SET);

        /* Retrieve and store tile ids. */
        for (int j = 0; j < TILESY; j++) {
            for (int i = 0; i < TILESX; i++) {
                chunk->tile[i][j].id = getIdFromFile(file);

                if (chunk->tile[i][j].id == -1) {
                    error++;
                }
            }
        }

        /* Handle expected more tiles. */
        if (error > 0) {
            printf("%d tile id(s) could not be retrieved from \"%s\"\n",
                    error, fileName);
        }
    }
    else {
        printf("Impossible to load tiles, chunk index is out of scope.\n");
    }

    fileCloseFile(file);
}

/* Takes in a tile id from a formatted file and returns the id. */
static int
getIdFromFile(FILE* file)
{
    int id = -1;

    fscanf(file, "%d,", &id);

    return id;
}

/* Sets the collision of all tiles with a certain id to true or false. */
void
tileSetCollision(Chunk chunk[], int id, bool hasCollision)
{
    for (int i = 0; i < NBCHUNKS; i++) {
        for (int x = 0; x < TILESX; x++) {
            for (int y = 0; y < TILESY; y++) {
                if (chunk[i].tile[x][y].id == id) {
                    chunk[i].tile[x][y].collision = hasCollision;
                }
            }
        }
    }
}

/* Creates an initializes a tile, then returns it. */
Tile
tileCreateTile(void)
{
    Tile tile;

    tile.id = 0;
    tile.frame = 0;
    tile.collision = false;

    return tile;
}
