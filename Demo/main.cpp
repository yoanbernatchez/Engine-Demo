/*===========================================================================*/
/* File: main.cpp                                                            */
/* Author: YOAN BERNATCHEZ                                                   */
/* Created On: 2020-10-15                                                    */
/* Developed Using: SDL2                                                     */
/* Project: The Demo folder contains code that utilizes the game engine to   */
/*          showcase the engine's capabilities through a mini game that has  */
/*          no purpose.                                                      */
/* Function: Contains the main function that gives a structure to the mini   */
/*           game, initialization, updating, rendering, freeing, exiting.    */
/*===========================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <time.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

/* Engine includes. */
#include "../Mini_Engine/Engine/globals.h"
#include "../Mini_Engine/Render/render.h"
#include "../Mini_Engine/HUD/hud.h"
#include "../Mini_Engine/Time/time.h"
#include "../Mini_Engine/Chunks/chunk.h"
#include "../Mini_Engine/Characters/character.h"
#include "../Mini_Engine/Collision/collision_handler.h"
#include "../Mini_Engine/Events/events.h"
#include "../Mini_Engine/Tests/tests.h"

/* Engine Demo includes. */
#include "character/entity.h"
#include "character/npc.h"
#include "character/player.h"
#include "objects/objects.h"
#include "hud/hud_handler.h"
#include "map/map.h"

int
main (int argc, char * argv[])
{
    /*
     * Specifies that argc and argv are unused to the compiler (SDL requires a
     * main signature with argc and argv to compile).
     */
    (void) argc;
    (void) argv;

    /*---- Initialization ---------------------------------------------------*/

    /* Initialize SDL. */
    SDL_Init (SDL_INIT_EVERYTHING);
    TTF_Init ();

    /* Create base window and renderer. */
    SDL_Window* window;
    window = SDL_CreateWindow ("Engine Demo", SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED, 900, 700,
                               SDL_WINDOW_RESIZABLE);

    SDL_Renderer* renderer;
    renderer = SDL_CreateRenderer (window, -1, SDL_RENDERER_ACCELERATED);

    if (window == NULL || renderer == NULL) {
       printf ("Could not create SDL window or renderer.\n");
       return -1;
    }

    SDL_SetRenderDrawBlendMode (renderer, SDL_BLENDMODE_BLEND);

    /* Initialize random number generator. */
    time_t t;
    srand ((unsigned) time(&t));

    /* Load sprite sheets. */
    SDL_Texture *villager_text[1];
    villager_text[0] = entity_get_villager_texture (renderer);

    SDL_Texture *object_text[1];
    object_text[0] = object_get_texture (renderer);

    SDL_Texture *tile_text[1];
    tile_text[0] = tile_get_texture (renderer);

    SDL_Texture *hud_text = hud_get_texture (renderer);

    /* Initialize chunks. */
    EngChunk chunk[NBCHUNKS];
    for (int i = 0; i < NBCHUNKS; i++)
        chunk[i] = eng_chunk_create_chunk ();

    /* Initialize characters. */
    int nb_entities = 7;
    EngCollision collision = {false, false, false, false};
    Entity entity[nb_entities];
    entity_load_presets (window, entity);
    EngCharacter render_char[nb_entities];

    /* Initialize huds. */
    EngHud hud[1];
    hud_load_presets (window, renderer, hud);

    /* Initialize events. */
    SDL_Event sdl_event;
    EngEvent event = {false, false, false, false, false};

    /* Initialize timers. */
    double render_timer = 0;
    double hud_timer[2] = {0, 0};
    double object_timer = 0;

    /* Run engine unit tests. */
    eng_test_all();

    printf ("Walk using the directional arrows on your keyboard.\n");

    /*---- Main Loop. -------------------------------------------------------*/
    while (eng_event_handle_events (sdl_event, &event)) {

        SDL_PollEvent(&sdl_event);
        SDL_Delay(1);

        /* Updating the map. */
        map_handler (chunk, entity[0].character);

        /* Updating entities. */
        for (int i = 0; i < nb_entities; i++) {
            eng_char_update (entity[0].character, &entity[i].character);
        }

        collision = eng_get_char_collision (chunk,entity[0].character, event);
        eng_char_set_collision (&entity[0].character, collision);

        player_handler (&entity[0].character, event);
        npc_handler (chunk, entity, nb_entities);

        /* Updating objects. */
        object_handler (chunk, &object_timer);

        /* Updating huds. */
        hud_handler (window, renderer, hud, &entity[0].character, hud_timer);

        /* If the window is resized, we center the huds and the player. */
        if (event.window_resized) {
            hud_center_huds (window, &hud[0]);
            eng_char_center_on_screen (window, &entity[0].character);
            event.window_resized = false;
        }

        /* Rendering. */
        if (eng_has_time_elapsed (&render_timer, true, ENG_MILLISECOND, 17)) {
            eng_render_tiles (renderer, chunk, entity[0].character,
                              tile_text, 1);
            /*
             * eng_render_objects takes an array of characters as parameters,
             * but since characters are hidden in an entity structure, we need
             * to reassemble them in a separate array.
             */
            for (int i = 0; i < nb_entities; i++) {
                render_char[i] = entity[i].character;
            }

            eng_render_objects (renderer, villager_text, object_text,
                                render_char, nb_entities, chunk);
            eng_hud_to_renderer (renderer, hud_text, hud[0]);
            SDL_RenderPresent (renderer);
        }
    }

    /*---- Destroy all allocated resources and end program. -----------------*/
    for (int i = 0; i < nb_entities; i++)
        entity_destroy (&entity[i]);

    for (int i = 0; i < nb_entities; i++)
        eng_char_destroy_character (&render_char[i]);

    for (int i = 0; i < NBCHUNKS; i++)
        eng_chunk_destroy (&chunk[i]);

    eng_hud_destroy (&hud[0]);

    SDL_DestroyTexture (villager_text[0]);
    SDL_DestroyTexture (object_text[0]);
    SDL_DestroyTexture (tile_text[0]);

    SDL_DestroyRenderer (renderer);
    SDL_DestroyWindow (window);

    TTF_Quit ();
    SDL_Quit ();

    return 0;
}
