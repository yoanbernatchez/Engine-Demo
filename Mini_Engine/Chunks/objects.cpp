#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../File_Utilities/file_utilities.h"
#include "chunk.h"
#include "objects.h"

/*---------------------------------------------------------------------------*/
/* Local function prototypes                                                 */
/*---------------------------------------------------------------------------*/

/**
 * @brief Allocates memory for the object dynamic array in a chunk, size
 *        depends on the value of nbObjects.
 *
 * @param chunk:      Array of chunks each containing objects.
 * @param chunkIndex: Defines which chunk of data will be modified.
 * @param nbObjects:  The number of objects to allocate memory for (if 0, we
 *                    free the memory instead).
 */
static void allocateObjects(Chunk *chunk, int nbObjects);

/*---------------------------------------------------------------------------*/
/* Object functions implementation                                           */
/*---------------------------------------------------------------------------*/

/* Modifies the object data stored in a chunk file with new values. */
void
objectModifyFileObject(int chunkX, int chunkY, int index, int id,
                            int x, int y)
{
    int cursorIndex = 0;
    int startIndex = 0;
    int endIndex = 0;
    int nbObjects = 0;
    int comma = 0;
    const char* fileName = chunkGetFileName(chunkX, chunkY);
    char newData[20];
    char c = '!';

    nbObjects = objectGetNbObjects(chunkX, chunkY);
    cursorIndex = fileGetIndexAfterString(fileName, "objects{");

    FILE* file = fopen(fileName, "r");

    if (file != NULL && cursorIndex >= 0 && nbObjects > 0 && index < nbObjects) {
        /* Advance file cursor to object data. */
        fseek(file, cursorIndex, SEEK_SET);

        /* Find the starting position for modification. */
        while (comma < index && c != '}' && !feof(file)) {
            c = fgetc(file);

            if (c == ',') {
                comma++;
            }
        }

        startIndex = ftell(file);

        /* Advance so that the character is not a comma anymore. */
        c = fgetc(file);

        /*
         * Find the ending position for modification by finding the next comma
         * or }.
         */
        while (c != ',' && c != '}' && !feof(file)) {
            c = fgetc(file);
        }

        endIndex = ftell(file);

        fileCloseFile(file);

        /* Modify data. */
        snprintf(newData, 20, "%d %d %d", id, x, y);
        fileReplaceWithString(fileName, newData, startIndex, endIndex - 1);
    }

    fileCloseFile(file);
}

/* Finds the nth object in a chunk file and deletes its data from the file. */
void
objectRemoveFileObject(int chunkX, int chunkY, int index)
{
    int cursorIndex = 0;
    int startIndex = 0;
    int endIndex = 0;
    int nbObjects = 0;
    int comma = 0;
    const char* fileName = chunkGetFileName(chunkX, chunkY);
    char c = '!';

    nbObjects = objectGetNbObjects(chunkX, chunkY);
    cursorIndex = fileGetIndexAfterString(fileName, "objects{");

    FILE* file = fopen(fileName, "r");

    if (file != NULL && cursorIndex >= 0 && nbObjects > 0 && index < nbObjects) {
        /* Advance file cursor to object data. */
        fseek(file, cursorIndex, SEEK_SET);

        /* Find the starting position for the removal. */
        while (comma < index && c != '}' && !feof(file)) {
            c = fgetc(file);

            if (c == ',') {
                comma++;
            }
        }

        startIndex = ftell(file);

        /* Advance so that the character is not a comma anymore. */
        c = fgetc(file);

        /*
         * Find the ending position for the removal by finding the next comma
         * or }.
         */
        while (c != ',' && c != '}' && !feof(file)) {
            c = fgetc(file);
        }

        endIndex = ftell(file);

        fileCloseFile(file);

        /*
         * In the case where there is only one object, we remove 1 from
         * endIndex so that the } does not get deleted.
         */
        if (index == 0 && nbObjects == 1) {
            fileReplaceWithString(fileName, "", startIndex, endIndex - 1);
        }

        /*
         * If the removed object is the first object in the file, we remove the
         * comma that comes after it.
         */
        else if (index == 0) {
            fileReplaceWithString(fileName, "", startIndex, endIndex);
        }

        /*
         * If it isn't the first object, we remove the comma that comes before
         * it.
         */
        else {
            fileReplaceWithString(fileName, "", startIndex - 1, endIndex - 1);
        }
    }

    fileCloseFile(file);
}

/*
 * Adds the data for an object at the end of the object list in a
 * chunk file.
 */
void
objectAddFileObject(int chunkX, int chunkY, int id, int x, int y)
{
    int cursorIndex = 0;
    int nbObjects = objectGetNbObjects(chunkX, chunkY);

    const char* fileName = chunkGetFileName(chunkX, chunkY);
    char newObjectData[100];

    /* Seek the location of object data. */
    cursorIndex = fileGetIndexAfterString(fileName, "objects{");

    FILE* file = fopen(fileName, "r");

    if (file != NULL && cursorIndex >= 0) {
        /* Position the file cursor to the end of "objects{". */
        fseek(file, cursorIndex, SEEK_SET);
        cursorIndex = ftell(file);

        /* Ready up newObjectData as formatted text. */
        if (nbObjects == 0) {
            snprintf(newObjectData, 100, "%d %d %d", id, x, y);
        }
        else {
            snprintf(newObjectData, 100, ",%d %d %d", id, x, y);

            /* Advance to the end of the object data (before the {). */
            while(fgetc(file) != '}' && !feof(file)){}
            cursorIndex = ftell(file) - 1;
        }

        file = fileCloseFile(file);

        /* Paste in file. */
        fileReplaceWithString(fileName, newObjectData, cursorIndex,
                              cursorIndex);
    }

    file = fileCloseFile(file);
}

/*
 * Scans the chunk file and returns the number of objects present in the
 * file.
 */
int
objectGetNbObjects(int chunkX, int chunkY)
{
    int nbObjects = 0;
    int nbCommas = 0;
    int cursorIndex = 0;
    char c = '!';
    const char* fileName = chunkGetFileName(chunkX, chunkY);

    /* Seek the location of object data. */
    cursorIndex = fileGetIndexAfterString(fileName, "objects{");

    FILE* file = fopen(fileName, "r");

    if (file != NULL && cursorIndex >= 0) {
        /* Position the file cursor to the end of "objects{". */
        fseek(file, cursorIndex, SEEK_SET);

        c = fgetc(file);

        if (c == '}') {
            /* If the first character read is }, then there is no objects. */
        }
        else {
            while (c != '}' && !feof(file)) {
                c = fgetc(file);

                if (c == ',') {
                    nbCommas++;
                }
            }

            nbObjects = nbCommas + 1;
        }
    }

    fileCloseFile(file);

    return nbObjects;
}

/*
 * Allocates memory for the object dynamic array in a chunk, size depends
 * on the value of nbObjects.
 */
static void
allocateObjects(Chunk *chunk, int nbObjects)
{
    if (chunk->nbObjects == 0 && nbObjects == 0) {

    }
    else if (chunk->nbObjects != 0 && nbObjects == 0) {
        free(chunk->object);
    }
    else if (chunk->nbObjects == 0 && nbObjects != 0) {
        chunk->object =
        (Object*) malloc(nbObjects * sizeof(Object));
    }
    else {
        chunk->object =
        (Object*) realloc(chunk->object, nbObjects * sizeof(Object));
    }

    chunk->nbObjects = nbObjects;
}

/*
 * Stores object data coming from the file corresponding to chunkX and
 * chunkY into chunk[chunkIndex].
 */
void
objectLoadObjects(Chunk *chunk)
{
    int cursorIndex = 0;
    int nbObjects =
    objectGetNbObjects(chunk->chunkX, chunk->chunkY);

    const char* fileName =
    chunkGetFileName(chunk->chunkX, chunk->chunkY);

    /* Seek the location of object data. */
    cursorIndex = fileGetIndexAfterString(fileName, "objects{");
    FILE *file = fopen(fileName, "r");

    if (file != NULL && cursorIndex >= 0) {

        /* Position the file cursor to the end of "objects{". */
        fseek(file, cursorIndex, SEEK_SET);

        allocateObjects(chunk, nbObjects);

        /*
        * Scan all the objects in the file and assign them their respective
        * values.
        */
        for (int i = 0; i < nbObjects; i++) {
            fscanf(file, "%d %d %d,", &chunk->object[i].id,
                   &chunk->object[i].x,
                   &chunk->object[i].y);
        }
    }

    file = fileCloseFile(file);
}

/*
 * This function needs to be called at the end of the program to cleanly
 * exit, frees the memory taken by the dynamic array "object".
 *
 * Probably should only be called at the end of the program.
 */
void
objectDeallocate(Chunk *chunk)
{
    if (chunk->nbObjects != 0) {
        free(chunk->object);
    }

    chunk->nbObjects = 0;
}
