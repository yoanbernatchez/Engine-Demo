#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL.h>
#include <SDL_image.h>
#include "entity.h"
#include "player.h"
#include "../../Mini_Engine/Engine/globals.h"
#include "../../Mini_Engine/Time/time.h"

/*---------------------------------------------------------------------------*/
/* Local function prototypes                                                 */
/*---------------------------------------------------------------------------*/

/**
 * @brief Makes the player face a direction and walk towards it if there was
 *        a keyboard event with directional arrows.
 *
 * @param player: Player to move.
 * @param event:  Contains keyboard events used to move the player.
 */
static void player_walk (EngCharacter *player, EngEvent event);

/**
 * @brief Check position of the player and do something for certain positions.
 *
 * @param player: Player to check the position of.
 */
static void player_check_position (EngCharacter *player);

/*---------------------------------------------------------------------------*/
/* Player function implementations                                           */
/*---------------------------------------------------------------------------*/

/* Handles player movement and player actions. */
void
player_handler (EngCharacter *player, EngEvent event)
{
    player_walk (player, event);
    player_check_position (player);
}

/*
 * Makes the player face a direction and walk towards it if there was
 * a keyboard event with directional arrows.
 */
static void
player_walk (EngCharacter *player, EngEvent event)
{
    if (eng_has_time_elapsed (player->timer, true, ENG_MILLISECOND, 17)) {
        if (event.right_pressed) {
            eng_char_move_character (player, player->speed, 0);
            player->direction = ENG_RIGHT;
        }
        if (event.left_pressed) {
            eng_char_move_character (player, -player->speed, 0);
            player->direction = ENG_LEFT;
        }
        if (event.up_pressed) {
            eng_char_move_character (player, 0, -player->speed);
            player->direction = ENG_UP;
        }
        if (event.down_pressed) {
            eng_char_move_character (player, 0, player->speed);
            player->direction = ENG_DOWN;
        }
        if (!event.down_pressed && !event.up_pressed &&
            !event.left_pressed && !event.right_pressed) {
            player->action_id =  0;
        }
        else
            player->action_id = 1;
    }

    entity_villager_update_src (player);
}

/* Check position of the player and do something for certain positions. */
static void
player_check_position (EngCharacter *player)
{
    int char_chunk_x = eng_char_get_chunk_x (player->x);
    int char_chunk_y = eng_char_get_chunk_y (player->y);

    /*
     * We check for specific positions that have special interactions
     * such as teleportation (doors in particular).
     */
    if (char_chunk_x == 0 && char_chunk_y == 0) {
        /* Door to go to personal house. */
        if (eng_char_get_tile_x (player->x) == 6 &&
            eng_char_get_tile_y (player->y) == 4) {
            player->x = 10 * TILESIZE * TILESX + 1.5 * TILESIZE;
            player->y = 10 * TILESIZE * TILESY + 2.9 * TILESIZE;
        }
        /* Door to house 2. */
        else if (eng_char_get_tile_x (player->x) == 40 &&
                 eng_char_get_tile_y (player->y) == 10) {
            player->x = 13 * TILESIZE * TILESX + 3.5 * TILESIZE;
            player->y = 12 * TILESIZE * TILESY + 4.9 * TILESIZE;
        }
        /* Door to house 3. */
        else if (eng_char_get_tile_x (player->x) == 45 &&
                 eng_char_get_tile_y (player->y) == 11) {
            player->x = 14 * TILESIZE * TILESX + 2.5 * TILESIZE;
            player->y = 14 * TILESIZE * TILESY + 4.9 * TILESIZE;
        }
        /* Door to house 4. */
        else if (eng_char_get_tile_x (player->x) == 39 &&
                 eng_char_get_tile_y (player->y) == 15) {
            player->x = 16 * TILESIZE * TILESX + 1.5 * TILESIZE;
            player->y = 16 * TILESIZE * TILESY + 2.9 * TILESIZE;
        }
    }
    else if (char_chunk_x == 0 && char_chunk_y == -1) {
        /* Northern farm building. */
        if (eng_char_get_tile_x (player->x) == 38 &&
            eng_char_get_tile_y (player->y) == 61) {
            player->x = 12 * TILESIZE * TILESX + 2.5 * TILESIZE;
            player->y = 13 * TILESIZE * TILESY + 4.9 * TILESIZE;
        }
    }
    else if (char_chunk_x == 10 && char_chunk_y == 10) {
        /* Door to get out of personal house. */
        if (eng_char_get_tile_x (player->x) == 1 &&
            eng_char_get_tile_y (player->y) == 3) {
            player->x = 6.5 * TILESIZE;
            player->y = 5 * TILESIZE;
        }
    }
    else if (char_chunk_x == 13 && char_chunk_y == 12) {
        /* Door to get out of house 2. */
        if (eng_char_get_tile_x (player->x) == 3 &&
            eng_char_get_tile_y (player->y) == 5) {
            player->x = 40.5 * TILESIZE;
            player->y = 11 * TILESIZE;
        }
    }
    else if (char_chunk_x == 14 && char_chunk_y == 14) {
        /* Door to get out of house 3. */
        if (eng_char_get_tile_x (player->x) == 2 &&
            eng_char_get_tile_y (player->y) == 5) {
            player->x = 45.5 * TILESIZE;
            player->y = 12 * TILESIZE;
        }
    }
    else if (char_chunk_x == 12 && char_chunk_y == 13) {
        /* Door to get out of farm house. */
        if (eng_char_get_tile_x (player->x) == 2 &&
            eng_char_get_tile_y (player->y) == 5) {
            player->x = 38.5 * TILESIZE;
            player->y = -2 * TILESIZE;
        }
    }
    else if (char_chunk_x == 16 && char_chunk_y == 16) {
        /* Door to get out of house 4. */
        if (eng_char_get_tile_x (player->x) == 1 &&
            eng_char_get_tile_y (player->y) == 3) {
            player->x = 39.5 * TILESIZE;
            player->y = 16 * TILESIZE;
        }
    }
}

/*
 * Checks the position of the player to determine in which zone he is,
 * then return the zone id.
 */
int
player_get_zone (EngCharacter player)
{
    /* Value for unknown zones is -1. */
    int value = -1;

    /* My room. */
    if (player.x > 10 * TILESIZE * TILESX &&
        player.x < 10 * TILESIZE * TILESX + TILESIZE * 3 &&
        player.y > 10 * TILESIZE * TILESY &&
        player.y < 10 * TILESIZE * TILESY + TILESIZE * 3) {
        value = 0;
    }
    /* Eastern farm. */
    else if (player.x >= 12 * TILESIZE && player.x < 22 * TILESIZE) {
        value = 1;
    }
    /* Path finding demo. */
    else if (player.x >= 23 * TILESIZE && player.x < 34 * TILESIZE) {
        value = 2;
    }
    /* Northern farm. */
    else if (player.x >= 35 * TILESIZE && player.x < 55 * TILESIZE &&
             player.y > -5 * TILESIZE && player.y < 6 * TILESIZE) {
        value = 3;
    }
    /* Zabura village. */
    else if (player.x >= 35 * TILESIZE && player.x < 49 * TILESIZE &&
             player.y >= 6 * TILESIZE && player.y < 19 * TILESIZE) {
        value = 4;
    }

    return value;
}
