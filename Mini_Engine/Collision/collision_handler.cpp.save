/*===========================================================================*/
/* File: collision_handler.cpp                                               */
/* Author: YOAN BERNATCHEZ                                                   */
/* Created On: 2020-08-05                                                    */
/* Developed Using: SDL2                                                     */
/* Function: Provides the user with a function that retrieves collision data */
/*           between a character and tiles.                                  */
/*===========================================================================*/

#include <stdbool.h>
#include "../Characters/character.h"
#include "collision_handler.h"

/*---------------------------------------------------------------------------*/
/* Local function prototypes                                                 */
/*---------------------------------------------------------------------------*/

/**
 * @brief Checks if a specified point ends up on a tile with the collision tag.
 *
 * @param chunk:    Array of chunks in which to check collision.
 * @param point:    A hit box point.
 * @param offset_X: Offset to apply to the x value of the hit box point.
 * @param offset_Y: Offset to apply to the y value of the hit box point.
 *
 * @return False if the point is in a tile without collision, true if it is
 *         in a tile with collision.
 */
static bool check_collision_on_tile (EngChunk chunk[], EngPoint2d point,
                                     int offset_x, int offset_y);
/**
 * @brief Scans an array of chunks and returns the index of the chunk with
 *        the requested x and y chunk values.
 *
 * @param chunk:   Array of chunks to scan.
 * @param chunk_x: Value of the chunk in x to find in the array of chunks.
 * @param chunk_y: Value of the chunk in y to find in the array of chunks.
 *
 * @return The index of the chunk with the corresponding chunk_x and chunk_y
 *         values from the array of chunks sent in parameters
 *         (-1 if not found).
 */
static int get_chunk_index (EngChunk chunk[], int chunk_x, int chunk_y);

/*---------------------------------------------------------------------------*/
/* Collision handling function implementations                               */
/*---------------------------------------------------------------------------*/

/* Returns collision data for a character in the form of booleans. */
EngCollision
eng_get_char_collision (EngChunk chunk[], EngCharacter character,
                        EngEvent event)
{
    EngCollision collision = {false, false, false, false};

    /* Points of the character's hit box. */
    EngPoint2d top_left = {character.hitbox.x, character.hitbox.y};
    EngPoint2d top_right = {character.hitbox.x + character.hitbox.w,
                            character.hitbox.y};
    EngPoint2d bottom_left = {character.hitbox.x, character.hitbox.y +
                              character.hitbox.h};
    EngPoint2d bottom_right = {character.hitbox.x + character.hitbox.w,
                               character.hitbox.y + character.hitbox.h};

        /* Check for collision when going left. */
        if (event.left_pressed) {
            collision.left = check_collision_on_tile (chunk, top_left,
                                                      -character.speed, 0);
            if (!collision.left)
                collision.left = check_collision_on_tile (chunk, bottom_left,
                                                          -character.speed, 0);
        }
        /* Check for collision when going right. */
        if (event.right_pressed) {
            collision.right = check_collision_on_tile (chunk, top_right,
                                                       character.speed, 0);
            if (!collision.right)
                collision.right = check_collision_on_tile (chunk, bottom_right,
                                                           character.speed, 0);
        }
        /* Check for collision when going up. */
        if (event.up_pressed) {
            collision.up = check_collision_on_tile (chunk, top_left, 0,
                                                    -character.speed);
            if (!collision.up)
                collision.up = check_collision_on_tile (chunk, top_right, 0,
                                                        -character.speed);
        }
        /* Check for collision when going down. */
        if (event.down_pressed) {
            collision.down = check_collision_on_tile (chunk, bottom_left, 0,
                                                      character.speed);
            if (!collision.down)
                collision.down = check_collision_on_tile (chunk, bottom_right,
                                                          0, character.speed);
        }

    return collision;
}

/* Checks if a specified point ends up on a tile with the collision tag. */
static bool
check_collision_on_tile (EngChunk chunk[], EngPoint2d point,
                         int offset_x, int offset_y)
{
    bool collision = false;
    int chunk_index = 0;
    EngPoint2d tile = {-1, -1};

    /*
     * Find the tile that the selected point from the character's hit box
     * would end up on if it was affected by an offset.
     */
    tile.x = eng_char_get_tile_x (point.x + offset_x);
    tile.y = eng_char_get_tile_y (point.y + offset_y);

    /*
     * Same thing here but this time we are finding the chunk that the point
     * ends up in depending on the offset.
     */
    chunk_index = get_chunk_index (chunk,
                                   eng_char_get_chunk_x (point.x + offset_x),
                                   eng_char_get_chunk_y (point.y + offset_y));

    if (chunk[chunk_index].tile[tile.x][tile.y].has_collision)
        collision = true;

    return collision;
}

/*
 * Scans an array of chunks and returns the index of the chunk with the
 * requested x and y values.
 */
static int
get_chunk_index (EngChunk chunk[], int chunk_x, int chunk_y)
{
    int index = -1;

    for (int i = 0; i < NBCHUNKS; i++) {
        index = i;
        if (chunk[i].chunk_x == chunk_x && chunk[i].chunk_y == chunk_y)
            break;
    }

    return index;
}
