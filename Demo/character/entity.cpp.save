/*===========================================================================*/
/* File: entity.cpp                                                          */
/* Author: YOAN BERNATCHEZ                                                   */
/* Created On: 2020-10-15                                                    */
/* Developed Using: SDL2                                                     */
/* Function: Provides functions to create and delete entities.               */
/*===========================================================================*/

#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include "../../Mini_Engine/Time/time.h"
#include "entity.h"

/*---------------------------------------------------------------------------*/
/* Local function prototypes                                                 */
/*---------------------------------------------------------------------------*/

/**
 * @brief Safe way to create an entity and initialize it.
 *
 * @param entity: Entity to create and initialize.
 */
static void entity_create_entity (Entity *entity);

/*---------------------------------------------------------------------------*/
/* Entity function implementations                                           */
/*---------------------------------------------------------------------------*/

/* Finds, loads and returns the sprite sheet used for villagers. */
SDL_Texture *
entity_get_villager_texture (SDL_Renderer *renderer)
{
    SDL_Surface *surf = IMG_Load ("Demo/assets/character_sprite.png");

    if (surf == NULL)
        printf ("%s\n", SDL_GetError ());

    SDL_Texture *text = SDL_CreateTextureFromSurface (renderer, surf);
    SDL_FreeSurface (surf);

    if (text == NULL)
        printf ("%s\n", SDL_GetError ());

    return text;
}

/* Safe way to create an entity and initialize it. */
static void
entity_create_entity (Entity *entity)
{
    entity->path = NULL;
    entity->path_id = -1;
    entity->saved_x = 0;
    entity->saved_y = 0;
    entity->step = -1;
}

/*
 * Loads presets such as coordinates, size and more to an array of
 * entities.
 */
void
entity_load_presets (SDL_Window *window, Entity entity[])
{
    /* Entity with id 0 is the player. */
    entity[0].character =
    eng_char_create_character (0, 0, 50/2, 75, 50, 75, 25, 20, true);
    entity_create_entity (&entity[0]);
    eng_char_create_timers (&entity[0].character, 2);
    entity[0].character.x = 42.5 * TILESIZE;
    entity[0].character.y = 12.5 * TILESIZE;
    eng_char_center_on_screen (window, &entity[0].character);

    /* Entity with id 1 is the bridge villager. */
    entity[1].character =
    eng_char_create_character (22.5 * TILESIZE, 4.5 * TILESIZE, 50/2, 75, 50,
                               75, 40, 40, false);
    entity_create_entity (&entity[1]);
    eng_char_create_timers (&entity[1].character, 2);
    entity[1].character.speed = 2;
    entity[1].path_id = 0;

    /* Entity with id 2 is the bridge villager. */
    entity[2].character =
    eng_char_create_character (18.5 * TILESIZE, 9.8 * TILESIZE, 50/2, 75, 50,
                               75, 40, 40, false);
    entity_create_entity (&entity[2]);
    eng_char_create_timers (&entity[2].character, 2);
    entity[2].character.action_id = ENTITY_IDLE;
    entity[2].character.speed = 2;
    entity[2].path_id = 0;

    /* Entity with id 2 is the bridge villager. */
    entity[3].character =
    eng_char_create_character (41.5 * TILESIZE, 11.4 * TILESIZE, 50/2, 75, 50,
                               75, 40, 40, false);
    entity_create_entity (&entity[3]);
    eng_char_create_timers (&entity[3].character, 2);
    entity[3].character.action_id = ENTITY_IDLE;
    entity[3].character.speed = 2;
    entity[3].path_id = 0;

    /* Entity with id 2 is the bridge villager. */
    entity[4].character =
    eng_char_create_character (14 * TILESIZE * TILESX + 0.5 * TILESIZE,
                               14 * TILESIZE * TILESY + 2.5 * TILESIZE,
                               50/2, 75, 50, 75, 40, 40, false);
    entity_create_entity (&entity[4]);
    eng_char_create_timers (&entity[4].character, 2);
    entity[4].character.action_id = ENTITY_IDLE;
    entity[4].character.speed = 2;
    entity[4].path_id = 0;

    entity[5].character =
    eng_char_create_character (16 * TILESIZE * TILESX + 0.5 * TILESIZE,
                               16 * TILESIZE * TILESY + 2.5 * TILESIZE,
                               50/2, 75, 50, 75, 40, 40, false);
    entity_create_entity (&entity[5]);
    eng_char_create_timers (&entity[5].character, 2);
    entity[5].character.action_id = ENTITY_IDLE;
    entity[5].character.speed = 2;
    entity[5].path_id = 0;

    entity[6].character =
    eng_char_create_character (41.5 * TILESIZE,
                               0.8 * TILESIZE,
                               50/2, 75, 50, 75, 40, 40, false);
    entity_create_entity (&entity[6]);
    eng_char_create_timers (&entity[6].character, 2);
    entity[6].character.action_id = ENTITY_IDLE;
    entity[6].character.speed = 2;
    entity[6].path_id = 0;
}

/* Updates the source coordinates of a villager's sprite. */
void
entity_villager_update_src (EngCharacter *character)
{
    character->src.y = character->direction * character->src.h;

    switch (character->action_id) {
    case ENTITY_IDLE:
        character->frame = 0;
        break;
    case ENTITY_WALK:
        if (eng_has_time_elapsed (&character->timer[1], true,
                                  ENG_MILLISECOND, 120)) {
            character->frame++;
            if (character->frame > 8)
                character->frame = 1;
        }
        break;
    }

    character->src.x = character->frame * character->src.w;
}

/* Destroys and deallocated memory for an entity. */
void
entity_destroy (Entity *entity)
{
    eng_pathfind_destroy_path (&entity->path);
    eng_char_destroy_character (&entity->character);
}
