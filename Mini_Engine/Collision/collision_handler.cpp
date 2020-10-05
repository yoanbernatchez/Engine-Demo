#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "collision_handler.h"

static int getChunkIndex(Chunk chunk[], int chunkX, int chunkY);
static bool checkCollisionOnTile(Chunk chunk[], Point2d point,
                                 int offsetX, int offsetY);

/**
 *
 *
 * @param event: Structure containing events
 *
 * @return A collision structure with data relative to the collision of
 *         projected hit box coordinates.
 */
Collision
getCollisionInfo(Chunk chunk[], Character character,
                          EngineEvent event)
{
    Collision collision = {false};

    /* Points of the character's hit box. */
    Point2d topLeft = {character.hitbox.x, character.hitbox.y};
    Point2d topRight = {character.hitbox.x + character.hitbox.w,
                        character.hitbox.y};
    Point2d bottomLeft = {character.hitbox.x,
                          character.hitbox.y + character.hitbox.h};
    Point2d bottomRight = {character.hitbox.x + character.hitbox.w,
                           character.hitbox.y + character.hitbox.h};

        /* Check for collision when going left*/
        if (event.leftPressed) {
            collision.left = checkCollisionOnTile(chunk, topLeft, -character.speed, 0);
            if (!collision.left) {
                collision.left = checkCollisionOnTile(chunk, bottomLeft, -character.speed, 0);
            }
        }
        if (event.rightPressed) {
            collision.right = checkCollisionOnTile(chunk, topRight, character.speed, 0);
            if (!collision.right) {
                collision.right = checkCollisionOnTile(chunk, bottomRight, character.speed, 0);
            }
        }
        if (event.upPressed) {
            collision.up = checkCollisionOnTile(chunk, topLeft, 0, -character.speed);
            if (!collision.up) {
                collision.up = checkCollisionOnTile(chunk, topRight, 0, -character.speed);
            }
        }
        if (event.downPressed) {
            collision.down = checkCollisionOnTile(chunk, bottomLeft, 0, character.speed);
            if (!collision.down) {
                collision.down = checkCollisionOnTile(chunk, bottomRight, 0, character.speed);
            }
        }

    return collision;
}

/**
 * @brief Checks if a specified point ends up on a tile with the collision tag.
 *
 * @param chunk:   Array of chunks in which to check collision.
 * @param point:   A hit box point.
 * @param offsetX: Offset to apply to the x value of the hit box point.
 * @param offsetY: Offset to apply to the y value of the hit box point.
 *
 * @return False if the point is in a tile without collision, true if it is
 *         in a tile with collision.
 */
/* Checks if a specified point ends up on a tile with the collision tag. */
static bool
checkCollisionOnTile(Chunk chunk[], Point2d point, int offsetX, int offsetY)
{
    bool collision = false;
    int chunkIndex = 0;
    Point2d tile = {-1, -1};

    /*
     * Find the tile that the selected point from the character's hit box
     * would end up on if it was affected by an offset.
     */
    tile.x = characterGetTileX(point.x + offsetX);
    tile.y = characterGetTileY(point.y + offsetY);

    /*
     * Same thing here but this time we are finding the chunk that the point
     * ends up in depending on the offset.
     */
    chunkIndex = getChunkIndex(chunk, characterGetChunkX(point.x + offsetX),
                               characterGetChunkY(point.y + offsetY));

    if (chunk[chunkIndex].tile[tile.x][tile.y].collision) {
        collision = true;
    }

    return collision;
}

/**
 * @brief Scans an array of chunks and returns the index of the chunk with
 *        the request x and y chunk values.
 *
 * @param chunk:  Array of chunks to scan.
 * @param chunkX: Value of the chunk in x to find in the array of chunks.
 * @param chunkY: Value of the chunk in y to find in the array of chunks.
 *
 * @return The index of the chunk with the corresponding chunkX and chunkY
 *         values from the array of chunks sent in parameters.
 */
/*
 * Scans an array of chunks and returns the index of the chunk with the
 * requested x and y values.
 */
static int
getChunkIndex(Chunk chunk[], int chunkX, int chunkY)
{
    int index = -1;

    for (int i = 0; i<NBCHUNKS; i++) {
        index = i;
        if (chunk[i].chunkX == chunkX && chunk[i].chunkY == chunkY) {
            break;
        }
    }

    return index;
}
