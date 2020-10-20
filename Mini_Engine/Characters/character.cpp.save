/*===========================================================================*/
/* File: character.cpp                                                       */
/* Author: YOAN BERNATCHEZ                                                   */
/* Created On: 2020-08-15                                                    */
/* Developed Using: SDL2                                                     */
/* Function: Provides the user with an easy way to implement characters.     */
/*===========================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "character.h"

/*
 * The DST coordinates of everything including chunks, objects and characters
 * are based on the player character, therefore having a player character is
 * essential, even if the player is invisible and has no purpose.
 */

/*---------------------------------------------------------------------------*/
/* Local function prototypes                                                 */
/*---------------------------------------------------------------------------*/

/**
 * @brief Updates the hitbox coordinates for a character.
 *
 * @param character: The character to update.
 *
 * @sa char_update_dst ()
 */
static void char_update_hitbox (EngCharacter *character);

/**
 * @brief Updates the destination coordinates for a character, base on a main
 *        character.
 *
 * @param player:    The main character (serves as a point of reference to
 *                   update other characters).
 * @param character: The character to update.
 *
 * @sa char_update_hitbox ()
 */
static void char_update_dst (EngCharacter player, EngCharacter *character);

/*---------------------------------------------------------------------------*/
/* Character function implementations                                        */
/*---------------------------------------------------------------------------*/

/* Finds out which chunk a point ends in and returns it's id. */
int
eng_char_get_chunk_x (int x)
{
    int chunk_x = 0;

    if (TILESIZE != 0)
        chunk_x = floor ((double) x / (TILESIZE * TILESX));
    else
        printf ("Error: division by zero in %s %d.\n", __FILE__, __LINE__);

    return chunk_x;
}

/* Finds out which chunk a point ends in and returns it's id. */
int
eng_char_get_chunk_y (int y)
{
    int chunk_y = 0;

    if (TILESIZE != 0)
        chunk_y = floor ((double) y / (TILESIZE * TILESY));
    else
        printf ("Error: division by zero in %s %d.\n", __FILE__, __LINE__);

    return chunk_y;
}

/*
 * Finds out which tile a point ends in and returns its
 * value.
 */
int
eng_char_get_tile_x (int x)
{
    int tile_x = 0;

    if (TILESIZE != 0)
        tile_x = abs (eng_char_get_chunk_x (x) * TILESIZE * TILESX - x) /
                 TILESIZE;
    else
        printf ("Error: division by zero in %s %d.\n", __FILE__, __LINE__);

    return tile_x;
}

/*
 * Finds out which tile a point ends in and returns its
 * value.
 */
int
eng_char_get_tile_y (int y)
{
    int tile_y = 0;

    if (TILESIZE != 0)
        tile_y = abs (eng_char_get_chunk_y (y) * TILESIZE * TILESY - y) /
                 TILESIZE;
    else
        printf ("Error: division by zero in %s %d.\n", __FILE__, __LINE__);

    return tile_y;
}

/*
 * Sets a new collision structure filled with collision data to a
 * character.
 */
void
eng_char_set_collision (EngCharacter *character, EngCollision collision)
{
    character->collision = collision;
}

/* Sets the action id for a character. */
void
eng_char_set_action (EngCharacter *character, int action_id)
{
    character->action_id = action_id;
}

/* Sets the direction for a character. */
void
eng_char_set_direction (EngCharacter *character, EngDirectionType direction)
{
    character->direction = direction;
}

/* Sets a character to be affected by collision or not. */
void
eng_char_set_is_collidable (EngCharacter *character,
                            bool is_affected_by_collision)
{
    character->is_affected_by_collision = is_affected_by_collision;
}

/* Allocates memory for n timers in a character structure. */
void
eng_char_create_timers (EngCharacter *character, int nb_timers)
{
    if (character->nb_timers == 0)
        character->timer = (double*) malloc (nb_timers * sizeof(double));
    else
        character->timer = (double*) realloc (character->timer, nb_timers *
                                              sizeof(double));

    for (int i = 0; i < nb_timers; i++)
        character->timer[i] = 0;

    character->nb_timers = nb_timers;
}

/*
 * Centers a character on screen (based on window size).
 */
void
eng_char_center_on_screen (SDL_Window *window, EngCharacter *character)
{
    int ptrW = 0;
    int ptrH = 0;

    SDL_GetWindowSize (window, &ptrW, &ptrH);
    character->dst.x = (ptrW - character->dst.w) / 2;
    character->dst.y = (ptrH - character->dst.h) / 2;
}

/*
 * Performs a collision check on a character if the character is
 * affected by collision, then moves the character.
 */
void
eng_char_move_character (EngCharacter *character, int amount_x, int amount_y)
{
    if (character->is_affected_by_collision) {
        if (amount_x < 0) {
            if (!character->collision.left)
                character->x += amount_x;
        }
        else {
            if (!character->collision.right)
                character->x += amount_x;
        }

        if (amount_y < 0) {
            if (!character->collision.up)
                character->y += amount_y;
        }
        else {
            if (!character->collision.down)
                character->y += amount_y;
        }
    }
    else {
        character->x += amount_x;
        character->y += amount_y;
    }
}

/* Updates the hitbox coordinates for a character. */
static void
char_update_hitbox (EngCharacter *character)
{
    character->hitbox.x = character->x - character->hitbox.w / 2;
    character->hitbox.y = character->y - character->hitbox.h;
}

/*
 * Updates the destination coordinates for a character, base on a main
 * character.
 */
static void
char_update_dst (EngCharacter player, EngCharacter *character)
{
    if (!character->is_player_controlled) {
        character->dst.x = player.dst.x + character->x - player.x;
        character->dst.y = player.dst.y + character->y - player.y;
    }
}

/*
 * Updates the hitbox, the source and destination coordinates of a
 * character.
 */
void
eng_char_update (EngCharacter player, EngCharacter *character)
{
    char_update_hitbox (character);
    char_update_dst (player, character);
}

/* Copies a character to the renderer. */
void
eng_character_render_character (SDL_Renderer *renderer, SDL_Texture *char_text,
                                EngCharacter character)
{
    SDL_RenderCopy (renderer, char_text, &character.src, &character.dst);
}

/*
 * Initializes a character structure and returns it. This is the safe
 * way to create characters.
 */
EngCharacter
eng_char_create_character (int x, int y, int center_x, int center_y,
                           int sprite_length, int sprite_height,
                           int hitbox_w, int hitbox_h,
                           bool is_player_controlled)
{
    EngCharacter character;

    character.x = x;
    character.y = y;
    character.center_x = character.x + center_x;
    character.center_y = character.y + center_y;
    character.sprite_lenght = sprite_length;
    character.sprite_height = sprite_height;
    character.frame = 0;
    character.action_id = 0;
    character.direction = ENG_DOWN;
    character.hitbox.x = character.center_x - hitbox_w / 2;
    character.hitbox.y = character.center_y - hitbox_h / 2;
    character.hitbox.w = hitbox_w;
    character.hitbox.h = hitbox_h;
    character.src.x = 0;
    character.src.y = 0;
    character.src.w = sprite_length;
    character.src.h = sprite_height;
    character.dst.x = 0;
    character.dst.y = 0;
    character.dst.w = sprite_length;
    character.dst.h = sprite_height;
    character.speed = 3;
    character.nb_timers = 0;
    character.is_player_controlled = is_player_controlled;
    character.is_affected_by_collision = true;
    character.collision.down = false;
    character.collision.up = false;
    character.collision.right = false;
    character.collision.left = false;

    return character;
}

/* Deallocates resources allocated to a character structure. */
void
eng_char_destroy_character (EngCharacter *character)
{
    if (character->nb_timers != 0)
        free (character->timer);
}
