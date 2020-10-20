/*===========================================================================*/
/* File: objects.cpp                                                         */
/* Author: YOAN BERNATCHEZ                                                   */
/* Created On: 2020-07-22                                                    */
/* Developed Using: SDL2                                                     */
/* Function: Provides the user with a way to create, delete and modify       */
/*           objects.                                                        */
/*===========================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include "chunk.h"
#include "objects.h"
#include "../File_Utilities/file_utilities.h"

/*---------------------------------------------------------------------------*/
/* Local function prototypes                                                 */
/*---------------------------------------------------------------------------*/

/**
 * @brief Allocates memory for the object dynamic array in a chunk, size
 *        depends on the value of nb_objects.
 *
 * @param chunk:       Array of chunks each containing objects.
 * @param chunk_index: Defines which chunk of data will be modified.
 * @param nb_objects:  The number of objects to allocate memory for (if 0, we
 *                     free the memory instead).
 */
static void allocate_objects (EngChunk *chunk, int nb_objects);

/*---------------------------------------------------------------------------*/
/* Object function implementations                                           */
/*---------------------------------------------------------------------------*/

/* Modifies the object data stored in a chunk file with new values. */
void
eng_object_modify_file_object (int chunk_x, int chunk_y, int index, int id,
                               int x, int y)
{
    int cursor_index = 0;
    int start_index = 0;
    int end_index = 0;
    int nb_objects = 0;
    int comma = 0;
    const char *file_name = eng_chunk_get_file_name (chunk_x, chunk_y);
    char new_data[20];
    char c = '!';

    nb_objects = eng_object_get_nb_objects (chunk_x, chunk_y);
    cursor_index = eng_file_get_index_after_string (file_name, "objects{");

    FILE *file = fopen (file_name, "r");

    if (file != NULL && cursor_index >= 0 && nb_objects > 0 &&
        index < nb_objects) {
        /* Advance file cursor to object data. */
        fseek (file, cursor_index, SEEK_SET);

        /* Find the starting position for modification. */
        while (comma < index && c != '}' && !feof (file)) {
            c = fgetc (file);

            if (c == ',')
                comma++;
        }

        start_index = ftell (file);

        /* Advance so that the character is not a comma anymore. */
        c = fgetc (file);

        /*
         * Find the ending position for modification by finding the next comma
         * or }.
         */
        while (c != ',' && c != '}' && !feof (file))
            c = fgetc (file);

        end_index = ftell (file);

        eng_file_close_file (file);

        /* Modify data. */
        snprintf (new_data, 20, "%d %d %d", id, x, y);
        eng_file_replace_with_string (file_name, new_data, start_index,
                                      end_index - 1);
    }

    free ((char*) file_name);
    file = eng_file_close_file (file);
}

/* Finds the nth object in a chunk file and deletes its data from the file. */
void
eng_object_remove_file_object (int chunk_x, int chunk_y, int index)
{
    int cursor_index = 0;
    int start_index = 0;
    int end_index = 0;
    int nb_objects = 0;
    int comma = 0;
    const char *file_name = eng_chunk_get_file_name (chunk_x, chunk_y);
    char c = '!';

    nb_objects = eng_object_get_nb_objects (chunk_x, chunk_y);
    cursor_index = eng_file_get_index_after_string (file_name, "objects{");

    FILE *file = fopen (file_name, "r");

    if (file != NULL && cursor_index >= 0 && nb_objects > 0 &&
        index < nb_objects) {
        /* Advance file cursor to object data. */
        fseek (file, cursor_index, SEEK_SET);

        /* Find the starting position for the removal. */
        while (comma < index && c != '}' && !feof (file)) {
            c = fgetc (file);

            if (c == ',')
                comma++;
        }

        start_index = ftell (file);

        /* Advance so that the character is not a comma anymore. */
        c = fgetc (file);

        /*
         * Find the ending position for the removal by finding the next comma
         * or }.
         */
        while (c != ',' && c != '}' && !feof (file))
            c = fgetc(file);

        end_index = ftell (file);

        eng_file_close_file (file);

        /*
         * In the case where there is only one object, we remove 1 from
         * endIndex so that the } does not get deleted.
         */
        if (index == 0 && nb_objects == 1) {
            eng_file_replace_with_string (file_name, "", start_index,
                                          end_index - 1);
        }
        /*
         * If the removed object is the first object in the file, we remove the
         * comma that comes after it.
         */
        else if (index == 0) {
            eng_file_replace_with_string (file_name, "", start_index,
                                          end_index);
        }
        /*
         * If it isn't the first object, we remove the comma that comes before
         * it.
         */
        else {
            eng_file_replace_with_string (file_name, "", start_index - 1,
                                          end_index - 1);
        }
    }

    free ((char*) file_name);
    file = eng_file_close_file (file);
}

/*
 * Adds the data for an object at the end of the object list in a
 * chunk file.
 */
void
eng_object_add_file_object (int chunk_x, int chunk_y, int id, int x, int y)
{
    int cursor_index = 0;
    int nb_objects = eng_object_get_nb_objects (chunk_x, chunk_y);
    int buffer_size = 100;
    const char *file_name = eng_chunk_get_file_name (chunk_x, chunk_y);
    char new_object_data[buffer_size];

    /* Seek the location of object data. */
    cursor_index = eng_file_get_index_after_string (file_name, "objects{");

    FILE *file = fopen (file_name, "r");

    if (file != NULL && cursor_index >= 0) {
        /* Position the file cursor to the end of "objects{". */
        fseek (file, cursor_index, SEEK_SET);
        cursor_index = ftell (file);

        /* Ready up newObjectData as formatted text. */
        if (nb_objects == 0)
            snprintf (new_object_data, buffer_size, "%d %d %d", id, x, y);
        else {
            snprintf (new_object_data, buffer_size, ",%d %d %d", id, x, y);

            /* Advance to the end of the object data (before the {). */
            while (fgetc (file) != '}' && !feof(file)) {
                /* Advance. */
            }

            cursor_index = ftell (file) - 1;
        }

        file = eng_file_close_file (file);

        /* Paste in file. */
        eng_file_replace_with_string (file_name, new_object_data,
                                      cursor_index, cursor_index);
    }

    free ((char*) file_name);
    file = eng_file_close_file (file);
}

/*
 * Scans the chunk file and returns the number of objects present in the
 * file.
 */
int
eng_object_get_nb_objects (int chunk_x, int chunk_y)
{
    int nb_objects = 0;
    int nb_commas = 0;
    int cursor_index = 0;
    char c = '!';
    const char *file_name = eng_chunk_get_file_name (chunk_x, chunk_y);

    /* Seek the location of object data. */
    cursor_index = eng_file_get_index_after_string (file_name, "objects{");

    FILE *file = fopen (file_name, "r");

    if (file != NULL && cursor_index >= 0) {
        /* Position the file cursor to the end of "objects{". */
        fseek (file, cursor_index, SEEK_SET);

        c = fgetc (file);

        if (c == '}') {
            /* If the first character read is }, then there is no objects. */
        }
        else {
            while (c != '}' && !feof (file)) {
                c = fgetc (file);

                if (c == ',')
                    nb_commas++;
            }
            nb_objects = nb_commas + 1;
        }
    }

    free ((char*) file_name);
    file = eng_file_close_file (file);

    return nb_objects;
}

/*
 * Allocates memory for the object dynamic array in a chunk, size depends
 * on the value of nb_objects.
 */
static void
allocate_objects (EngChunk *chunk, int nb_objects)
{
    if (chunk->nb_objects == 0 && nb_objects == 0) {

    }
    else if (chunk->nb_objects != 0 && nb_objects == 0)
        free (chunk->object);
    else if (chunk->nb_objects == 0 && nb_objects != 0)
        chunk->object = (EngObject*) malloc (nb_objects * sizeof(EngObject));
    else {
        chunk->object =
        (EngObject*) realloc (chunk->object, nb_objects * sizeof(EngObject));
    }

    chunk->nb_objects = nb_objects;
}

/*
 * Stores object data coming from the file corresponding to chunk_x and
 * chunk_y into chunk.
 */
void
eng_object_load_objects (EngChunk *chunk)
{
    int cursor_index = 0;
    int nb_objects =
    eng_object_get_nb_objects (chunk->chunk_x, chunk->chunk_y);
    SDL_Rect null_rect = {0, 0, 0, 0};

    const char *file_name =
    eng_chunk_get_file_name (chunk->chunk_x, chunk->chunk_y);

    /* Seek the location of object data. */
    cursor_index = eng_file_get_index_after_string (file_name, "objects{");
    FILE *file = fopen (file_name, "r");

    if (file != NULL && cursor_index >= 0) {
        /* Position the file cursor to the end of "objects{". */
        fseek (file, cursor_index, SEEK_SET);

        allocate_objects (chunk, nb_objects);

        /*
        * Scan all the objects in the file and assign them their respective
        * values.
        */
        for (int i = 0; i < nb_objects; i++) {
            fscanf (file, "%d %d %d,", &chunk->object[i].id,
                    &chunk->object[i].x,
                    &chunk->object[i].y);

            /* Initialize every element of object. */
            chunk->object[i].center_y = 0;
            chunk->object[i].frame = 0;
            chunk->object[i].nb_frames = 0;
            chunk->object[i].render_mode = 0;
            chunk->object[i].texture_index = 0;
            chunk->object[i].dst = null_rect;
            chunk->object[i].src = null_rect;
        }

        file = eng_file_close_file (file);
    }

    free ((char*) file_name);
}

/*
 * Frees memory allocated to objects in a chunk.
 */
void
eng_object_deallocate (EngChunk *chunk)
{
    if (chunk->nb_objects != 0)
        free(chunk->object);

    chunk->nb_objects = 0;
}
