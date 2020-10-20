/*===========================================================================*/
/* File: hud_handler.cpp                                                     */
/* Author: YOAN BERNATCHEZ                                                   */
/* Created On: 2020-10-17                                                    */
/* Developed Using: SDL2                                                     */
/* Function: Provides a function that handles all the huds in the game.      */
/*===========================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL_image.h>
#include "hud_handler.h"
#include "zone_hud.h"

/* Loads presets to an array of huds. */
void
hud_load_presets (SDL_Window *window, SDL_Renderer *renderer, EngHud hud[])
{
    hud[0] = hud_create_zone_hud (renderer);
    hud_center_huds (window, hud);
}

/* Returns the sprite sheet texture for hud elements. */
SDL_Texture *
hud_get_texture (SDL_Renderer *renderer)
{
    SDL_Surface *surf = IMG_Load ("Demo/assets/hud_sprite.png");

    if (surf == NULL)
        printf ("%s\n", SDL_GetError ());

    SDL_Texture *text = SDL_CreateTextureFromSurface (renderer, surf);
    SDL_FreeSurface (surf);

    if (text == NULL)
        printf ("%s\n", SDL_GetError ());

    return text;
}

/* Checks, updates and manages all the huds. */
void
hud_handler (SDL_Window *window, SDL_Renderer *renderer, EngHud hud[],
             EngCharacter character[], double timer[])
{
    /* We check if we need to update the zone hud after a while. */
    if (eng_has_time_elapsed (&timer[0], true, ENG_MILLISECOND, 20))
        update_zone_hud (window, renderer, &hud[0], character[0], &timer[1]);
}

/* Centers all the huds on screen. */
void
hud_center_huds (SDL_Window *window, EngHud hud[])
{
    center_zone_hud (window, &hud[0]);
}

/* Sets the opacity of a hud's components and borders. */
void
set_hud_opacity (EngHud *hud, int opacity)
{
    if (opacity < 0)
        opacity = 0;
    else if (opacity > 255)
        opacity = 255;

    /* Set object opacity. */
    for (int i = 0; i < hud->nb_components; i++) {
        hud->component[i].opacity = opacity;
    }

    /* Set border opacity. */
    for (int j = 0; j < 4; j++) {
        hud->border[j].opacity = opacity;
    }
}
