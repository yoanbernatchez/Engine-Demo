/*===========================================================================*/
/* File: objects.cpp                                                         */
/* Author: YOAN BERNATCHEZ                                                   */
/* Created On: 2020-10-14                                                    */
/* Developed Using: SDL2                                                     */
/* Function: Provides functions to handle game objects.                      */
/*===========================================================================*/

#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include "../../Mini_Engine/Chunks/chunk.h"
#include "objects.h"
#include "wheat.h"

/*
 * Returns a sprite sheet texture that contains the graphics of all the
 * objects.
 */
SDL_Texture *
object_get_texture (SDL_Renderer *renderer)
{
    SDL_Surface *surf = IMG_Load ("Demo/assets/object_sprite.png");

    if (surf == NULL)
        printf ("%s\n", SDL_GetError ());

    SDL_Texture *text = SDL_CreateTextureFromSurface (renderer, surf);
    SDL_FreeSurface (surf);

    if (text == NULL)
        printf ("%s\n", SDL_GetError ());

    return text;
}

/*
 * Returns a sprite sheet texture that contains the graphics of all the
 * tiles.
 */
SDL_Texture *
tile_get_texture (SDL_Renderer *renderer)
{
    SDL_Surface *surf = IMG_Load ("Demo/assets/tile_sprite.bmp");

    if (surf == NULL)
        printf ("%s\n", SDL_GetError ());

    SDL_Texture *text = SDL_CreateTextureFromSurface (renderer, surf);
    SDL_FreeSurface (surf);

    if (text == NULL)
        printf ("%s\n", SDL_GetError ());

    return text;
}

/*
 * Assigns properties to all the objects that have defined properties linked
 * to their id in the array of chunks.
 *
 * TODO: Replace this function by a file-retrieving method to get object
 *       properties.
 */
void
object_assign_properties (EngChunk chunk[])
{
    for (int i = 0; i < NBCHUNKS; i++) {
        for (int j = 0; j < chunk[i].nb_objects; j++) {
            switch (chunk[i].object[j].id) {
            /* Sign. */
            case 0:
                chunk[i].object[j].src.x = 0;
                chunk[i].object[j].src.y = 0;
                chunk[i].object[j].src.w = 40;
                chunk[i].object[j].src.h = 42;
                chunk[i].object[j].center_y = 40;
                chunk[i].object[j].nb_frames = 1;
                chunk[i].object[j].render_mode = ENG_RENDER_HYBRID;
                chunk[i].object[j].texture_index = 0;
                break;
            /* Red tree. */
            case 1:
                chunk[i].object[j].src.x = 54;
                chunk[i].object[j].src.y = 0;
                chunk[i].object[j].src.w = 180;
                chunk[i].object[j].src.h = 190;
                chunk[i].object[j].center_y = 150;
                chunk[i].object[j].nb_frames = 1;
                chunk[i].object[j].render_mode = ENG_RENDER_HYBRID;
                chunk[i].object[j].texture_index = 0;
                break;
            /* Small desk with apple. */
            case 2:
                chunk[i].object[j].src.x = 246;
                chunk[i].object[j].src.y = 0;
                chunk[i].object[j].src.w = 64;
                chunk[i].object[j].src.h = 64;
                chunk[i].object[j].center_y = 0;
                chunk[i].object[j].nb_frames = 1;
                chunk[i].object[j].render_mode = ENG_RENDER_HYBRID;
                chunk[i].object[j].texture_index = 0;
                break;
            /* Yellow bed. */
            case 3:
                chunk[i].object[j].src.x = 334;
                chunk[i].object[j].src.y = 0;
                chunk[i].object[j].src.w = 64;
                chunk[i].object[j].src.h = 128;
                chunk[i].object[j].center_y = 0;
                chunk[i].object[j].nb_frames = 1;
                chunk[i].object[j].render_mode = ENG_RENDER_HYBRID;
                chunk[i].object[j].texture_index = 0;
                break;
            /* Door mat. */
            case 4:
                chunk[i].object[j].src.x = 245;
                chunk[i].object[j].src.y = 83;
                chunk[i].object[j].src.w = 68;
                chunk[i].object[j].src.h = 37;
                chunk[i].object[j].center_y = 0;
                chunk[i].object[j].nb_frames = 1;
                chunk[i].object[j].render_mode = ENG_RENDER_BACKGROUND;
                chunk[i].object[j].texture_index = 0;
                break;
            /* Wheat. */
            case 5:
                chunk[i].object[j].src.x = 494;
                chunk[i].object[j].src.y = 0;
                chunk[i].object[j].src.w = 66;
                chunk[i].object[j].src.h = 89;
                chunk[i].object[j].center_y = 82;
                chunk[i].object[j].nb_frames = 2;
                chunk[i].object[j].render_mode = ENG_RENDER_HYBRID;
                chunk[i].object[j].texture_index = 0;
                break;
            /* Blue bed. */
            case 6:
                chunk[i].object[j].src.x = 408;
                chunk[i].object[j].src.y = 0;
                chunk[i].object[j].src.w = 64;
                chunk[i].object[j].src.h = 128;
                chunk[i].object[j].center_y = 0;
                chunk[i].object[j].nb_frames = 1;
                chunk[i].object[j].render_mode = ENG_RENDER_HYBRID;
                chunk[i].object[j].texture_index = 0;
                break;
            /* Green bed. */
            case 7:
                chunk[i].object[j].src.x = 334;
                chunk[i].object[j].src.y = 135;
                chunk[i].object[j].src.w = 64;
                chunk[i].object[j].src.h = 128;
                chunk[i].object[j].center_y = 0;
                chunk[i].object[j].nb_frames = 1;
                chunk[i].object[j].render_mode = ENG_RENDER_HYBRID;
                chunk[i].object[j].texture_index = 0;
                break;
            /* Red bed. */
            case 8:
                chunk[i].object[j].src.x = 408;
                chunk[i].object[j].src.y = 135;
                chunk[i].object[j].src.w = 64;
                chunk[i].object[j].src.h = 128;
                chunk[i].object[j].center_y = 0;
                chunk[i].object[j].nb_frames = 1;
                chunk[i].object[j].render_mode = ENG_RENDER_HYBRID;
                chunk[i].object[j].texture_index = 0;
                break;
            /* Small desk. */
            case 9:
                chunk[i].object[j].src.x = 245;
                chunk[i].object[j].src.y = 142;
                chunk[i].object[j].src.w = 64;
                chunk[i].object[j].src.h = 64;
                chunk[i].object[j].center_y = 0;
                chunk[i].object[j].nb_frames = 1;
                chunk[i].object[j].render_mode = ENG_RENDER_HYBRID;
                chunk[i].object[j].texture_index = 0;
                break;
            /* Stove top. */
            case 10:
                chunk[i].object[j].src.x = 246;
                chunk[i].object[j].src.y = 211;
                chunk[i].object[j].src.w = 64;
                chunk[i].object[j].src.h = 79;
                chunk[i].object[j].center_y = 0;
                chunk[i].object[j].nb_frames = 1;
                chunk[i].object[j].render_mode = ENG_RENDER_HYBRID;
                chunk[i].object[j].texture_index = 0;
                break;
            }
        }
    }
}

/* Handles changes and updates objects on the map. */
void
object_handler (EngChunk chunk[], double *timer)
{
    /* Update the wheat. */
    wheat_next_frame (chunk, timer);

    /* Update other objects. */
}
