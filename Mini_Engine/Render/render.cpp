/*===========================================================================*/
/* File: render.cpp                                                          */
/* Author: YOAN BERNATCHEZ                                                   */
/* Created On: 2020-09-27                                                    */
/* Developed Using: SDL2                                                     */
/* Function: This file provides the user with functions to render chunks and */
/*           characters.                                                     */
/*===========================================================================*/

#include "render.h"

typedef struct _RenderObject {
    int y;
    int object_index;
    int chunk_index;
    bool is_character;
} RenderObject;
/**< Render object structure used for order of rendering. */

/*---------------------------------------------------------------------------*/
/* Local function prototypes                                                 */
/*---------------------------------------------------------------------------*/

/**
 * @param Sorts rendering objects in order of y.
 *
 * @param object:     Render objects to sort
 * @param nb_objects: Number of render objects to sort.
 */
static void selection_sort (RenderObject *object, int nb_objects);

/**
 * @brief Returns the number of objects that correspond to a specified
 *        rendering mode.
 *
 * @param chunk: Chunks containing object information.
 * @param mode:  Mode for rendering that we scan objects for.
 *
 * @return The number of render objects having a specified mode.
 */
static int get_nb_object_type (EngChunk chunk[], EngRenderMode mode);

/**
 * @brief Gives values to the rendering objects, preparing them to be sorted.
 *
 * @param chunk:         Chunks containing object information.
 * @param objects:       RenderObject array being initialized.
 * @param mode:          Object rendering mode indicating which objects we
 *                       we initialize in the RenderObjects array.
 * @param character:     Array of characters.
 * @param nb_characters: Number of characters in the array of characters.
 */
static void init_objects (EngChunk chunk[], RenderObject objects[],
                          EngRenderMode mode, EngCharacter charcter[],
                          int nb_characters);

/**
 * @brief Adds the contents of an array to a bigger array.
 *
 * @param all_objects: Array of render objects to add to.
 * @param objects:     Array of render objects to add from.
 * @param nb_objects:  Number of objects in the smaller array.
 * @param order_index: Index of the bigger array.
 */
static void add_to_array (RenderObject all_objects[], RenderObject objects[],
                          int nb_objects, int *order_index);

/*---------------------------------------------------------------------------*/
/* Render function implementations                                           */
/*---------------------------------------------------------------------------*/

/*
 * Pastes to the renderer all the tiles and objects from the array of chunk
 * data.
 */
void
eng_render_tiles (SDL_Renderer *renderer, EngChunk chunk[],
                  EngCharacter player, SDL_Texture *tile_text[],
                  int nb_textures)
{
    int tile_texture_index = 0;
    int nb_horizontal_tiles = 0;
    int nb_vertical_tiles = 0;

    SDL_QueryTexture (tile_text[0], NULL, NULL, &nb_horizontal_tiles,
                      &nb_vertical_tiles);

    nb_horizontal_tiles /= TILESIZE;
    nb_vertical_tiles /= TILESIZE;

    SDL_Rect src = {0, 0, TILESIZE, TILESIZE};
    SDL_Rect dst = {0, 0, TILESIZE, TILESIZE};

    /* Copy tiles to renderer. */
    for (int h = 0; h < NBCHUNKS; h++) {
        for (int i = 0; i < TILESY; i++) {
            for (int j = 0; j < TILESX; j++) {
                src.x = (chunk[h].tile[j][i].id % nb_horizontal_tiles) *
                        TILESIZE;
                src.y = (chunk[h].tile[j][i].id / nb_vertical_tiles) *
                        TILESIZE;

                dst.x = j * TILESIZE + chunk[h].chunk_x*TILESX*TILESIZE +
                        player.dst.x + player.center_x - player.x;
                dst.y = i * TILESIZE + chunk[h].chunk_y*TILESY*TILESIZE +
                        player.dst.y + player.center_y - player.y;

                tile_texture_index = chunk[h].tile[j][i].id /
                                     (nb_horizontal_tiles * nb_vertical_tiles);

                /*
                 * Make sure that something exists at the index, then copy to
                 * renderer.
                 */
                if (tile_texture_index < nb_textures)
                    SDL_RenderCopy (renderer, tile_text[tile_texture_index],
                                    &src, &dst);
            }
        }
    }
}
/*
 * Renders objects and characters in a specific order on screen.
 * TODO: Make this function less chaotic.
 */
void
eng_render_objects (SDL_Renderer *renderer, SDL_Texture *char_text[],
                           SDL_Texture *obj_text[], EngCharacter character[],
                           int nb_characters, EngChunk chunk[])
{
    EngObject curr_obj;
    int nb_background_objects = 0;
    int nb_hybrid_objects = 0;
    int nb_foreground_objects = 0;
    int nb_all_objects = 0;
    int order_index = 0;
    int chunk_index = 0;
    int obj_index = 0;
    int chunk_offset_x = 0;
    int chunk_offset_y = 0;
    int char_offset_x = 0;
    int char_offset_y = 0;
    SDL_Rect rect = {0, 0, 0, 0};

    /* Get the number of rendering objects for each rendering type. */
    nb_background_objects = get_nb_object_type (chunk, ENG_RENDER_BACKGROUND);
    nb_hybrid_objects = nb_characters;
    nb_hybrid_objects += get_nb_object_type (chunk, ENG_RENDER_HYBRID);
    nb_foreground_objects = get_nb_object_type (chunk, ENG_RENDER_FOREGROUND);

    RenderObject background_objects[nb_background_objects];
    RenderObject hybrid_objects[nb_hybrid_objects];
    RenderObject foreground_objects[nb_foreground_objects];

    /* Gives values to our array of objects. */
    init_objects (chunk, background_objects, ENG_RENDER_BACKGROUND, character,
                  nb_characters);
    init_objects (chunk, hybrid_objects, ENG_RENDER_HYBRID, character,
                  nb_characters);
    init_objects (chunk, foreground_objects, ENG_RENDER_FOREGROUND, character,
                  nb_characters);

    /* Sort the objects based on their y values. */
    selection_sort (background_objects, nb_background_objects);
    selection_sort (hybrid_objects, nb_hybrid_objects);
    selection_sort (foreground_objects, nb_foreground_objects);
    nb_all_objects = nb_background_objects + nb_hybrid_objects +
                     nb_foreground_objects;

    /* Combine all types of objects in one array. */
    RenderObject all_objects[nb_all_objects];
    add_to_array (all_objects, background_objects, nb_background_objects,
                  &order_index);
    add_to_array (all_objects, hybrid_objects, nb_hybrid_objects,
                  &order_index);
    add_to_array (all_objects, foreground_objects, nb_foreground_objects,
                  &order_index);

    /* Render all objects. */
    for (int i = 0; i < nb_all_objects; i++) {
        obj_index = all_objects[i].object_index;
        curr_obj = chunk[chunk_index].object[obj_index];

        if (all_objects[i].is_character) {
            SDL_RenderCopy(renderer, char_text[0], &character[obj_index].src,
                           &character[obj_index].dst);
        }
        else {
            chunk_index = all_objects[i].chunk_index;
            chunk_offset_x = chunk[chunk_index].chunk_x * TILESIZE * TILESX;
            chunk_offset_y = chunk[chunk_index].chunk_y * TILESIZE * TILESY;
            char_offset_x = character[0].dst.x + character[0].center_x -
                            character[0].x;
            char_offset_y = character[0].dst.y + character[0].center_y -
                            character[0].y;

            rect.x = chunk_offset_x + curr_obj.x + char_offset_x;
            rect.y = chunk_offset_y + curr_obj.y - curr_obj.center_y +
                     char_offset_y;
            rect.w = curr_obj.src.w;
            rect.h = curr_obj.src.h;

            SDL_RenderCopy(renderer,
                           obj_text[chunk[all_objects[i].chunk_index].
                           object[obj_index].texture_index],
                           &chunk[all_objects[i].chunk_index].
                           object[obj_index].src, &rect);
        }
    }
}

/* Adds the contents of an array to a bigger array. */
static void
add_to_array (RenderObject all_objects[], RenderObject objects[],
              int nb_objects, int *order_index)
{
    for (int i = 0; i < nb_objects; i++) {
        all_objects[*order_index].chunk_index = objects[i].chunk_index;
        all_objects[*order_index].is_character = objects[i].is_character;
        all_objects[*order_index].object_index = objects[i].object_index;
        all_objects[*order_index].y = objects[i].y;

        *order_index = *order_index + 1;
    }
}

/*
 * Returns the number of objects that correspond to a specified
 * rendering mode.
 */
static int
get_nb_object_type (EngChunk chunk[], EngRenderMode mode)
{
    int nb_objects = 0;

    /* Check how many objects there are to copy to the renderer. */
    for (int i = 0; i < NBCHUNKS; i++) {
        for (int j = 0; j < chunk[i].nb_objects; j++) {
            if (chunk[i].object[j].render_mode == mode)
                nb_objects++;
        }
    }

    return nb_objects;
}

/* Gives values to the rendering objects, preparing them to be sorted. */
static void
init_objects (EngChunk chunk[], RenderObject objects[], EngRenderMode mode,
              EngCharacter character[], int nb_characters)
{
    int order_index = 0;

    /* Assign values to the order structure, readying them to be sorted. */
    for (int i = 0; i < NBCHUNKS; i++) {
        for (int j = 0; j < chunk[i].nb_objects; j++) {
            if (chunk[i].object[j].render_mode == mode) {
                objects[order_index].y = chunk[i].object[j].y + TILESY *
                                          TILESIZE * chunk[i].chunk_y;
                objects[order_index].is_character = false;
                objects[order_index].object_index = j;
                objects[order_index].chunk_index = i;
                order_index++;
            }
        }
    }

    /* Characters are all hybrid, therefore we add them to the hybrid array. */
    if (mode == ENG_RENDER_HYBRID) {
        for (int i = 0; i < nb_characters; i++) {
            objects[order_index].y = character[i].y;
            objects[order_index].is_character = true;
            objects[order_index].object_index = i;
            objects[order_index].chunk_index = -1;
            order_index++;
        }
    }

    order_index = 0;
}

/* Simple selection sort algorithm for render objects. */
static void
selection_sort (RenderObject *object, int nb_objects)
{
    RenderObject temp_obj = {0, 0, 0, false};
    int index_min = 0;

    for (int i = 0; i < nb_objects; i++) {
        index_min = i;

        for (int j = i; j < nb_objects; j++) {
            if (object[j].y < object[index_min].y)
                index_min = j;
        }

        temp_obj = object[i];
        object[i] = object[index_min];
        object[index_min] = temp_obj;
    }
}
