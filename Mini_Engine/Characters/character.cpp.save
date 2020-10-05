#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL.h>
#include "character.h"

/*
 * The DST coordinates of everything including chunks, objects and characters are based on the player character, therefore
 * having a player character is essential, even if the player is invisible and has no purpose.
 */

/*---------------------------------------------------------------------------*/
/* Local function prototypes                                                 */
/*---------------------------------------------------------------------------*/

/**
 * @brief Updates the hitbox coordinates for a character.
 *
 * @param character: The character to update.
 *
 * @sa characterUpdateDst()
 */
static void characterUpdateHitbox(Character *character);

/**
 * @brief Updates the destination coordinates for a character, base on a main
 *        character.
 *
 * @param player:    The main character (serves as a point of reference to
 *                   update other characters).
 * @param character: The character to update.
 *
 * @sa characterUpdateHitbox()
 */
static void characterUpdateDst(Character player, Character *character);

/*---------------------------------------------------------------------------*/
/* Character functions implementation                                        */
/*---------------------------------------------------------------------------*/

/* Finds out which chunk a point ends in and returns it's id. */
int
characterGetChunkX(int x)
{
    int chunkX = 0;

    if (TILESIZE != 0) {
        chunkX = floor((double) x / (TILESIZE * TILESX));
    }
    else {
        printf("Error: division by zero in %s %d.\n", __FILE__, __LINE__);
    }

    return chunkX;
}

/* Finds out which chunk a point ends in and returns it's id. */
int
characterGetChunkY(int y)
{
    int chunkY = 0;

    if (TILESIZE != 0) {
        chunkY = floor((double) y / (TILESIZE*TILESY));
    }
    else {
        printf("Error: division by zero in %s %d.\n", __FILE__, __LINE__);
    }

    return chunkY;
}

/*
 * Finds out which tile the character is on (in a chunk) and returns its
 * value.
 */
int
characterGetTileX(int x)
{
    int tileX = 0;

    if (TILESIZE != 0) {
        tileX = abs(characterGetChunkX(x) * TILESIZE * TILESX - x) / TILESIZE;
    }
    else {
        printf("Error: division by zero in %s %d.\n", __FILE__, __LINE__);
    }

    return tileX;
}

/*
 * Finds out which tile the character is on (in a chunk) and returns its
 * value.
 */
int
characterGetTileY(int y)
{
    int tileY = 0;

    if (TILESIZE != 0) {
        tileY = abs(characterGetChunkY(y) * TILESIZE * TILESY - y) / TILESIZE;
    }
    else {
        printf("Error: division by zero in %s %d.\n", __FILE__, __LINE__);
    }

    return tileY;
}

/*
 * Sets a new collision structure filled with collision data to a
 * character.
 */
void
characterSetCollision(Character *character, Collision collision)
{
    character->collision = collision;
}

/* Sets the action id for a character. */
void
characterSetAction(Character *character, int actionId)
{
    character->actionId = actionId;
}

/* Sets the direction for a character. */
void
characterSetDirection(Character *character, EngineDirectionType direction)
{
    character->direction = direction;
}

/* Sets a character to be affected by collision or not. */
void
characterSetIsCollidable(Character *character, bool isAffectedByCollision)
{
    character->isAffectedByCollision = isAffectedByCollision;
}

/*
 * Centers a character on screen (based on window size).
 */
void
characterCenterOnScreen(SDL_Window *window, Character *character)
{
    int ptrW = 0;
    int ptrH = 0;

    SDL_GetWindowSize(window, &ptrW, &ptrH);
    character->dst.x = (ptrW - character->dst.w) / 2;
    character->dst.y = (ptrH - character->dst.h) / 2;
}

/*
 * Performs a collision check on a character if the character is
 * affected by collision, then moves the character.
 */
void
characterMoveCharacter(Character *character, int amountX, int amountY)
{
    if (character->isAffectedByCollision) {
        if (amountX < 0) {
            if (!character->collision.left) {
                character->x += amountX;
            }
        }
        else {
            if (!character->collision.right) {
                character->x += amountX;
            }
        }

        if (amountY < 0) {
            if (!character->collision.up) {
                character->y += amountY;
            }
        }
        else {
            if (!character->collision.down) {
                character->y += amountY;
            }
        }
    }
    else {
        character->x += amountX;
        character->y += amountY;
    }
}

/* Updates the hitbox coordinates for a character. */
static void
characterUpdateHitbox(Character *character)
{
    character->hitbox.x = character->x - character->hitbox.w / 2;
    character->hitbox.y = character->y - character->hitbox.h;
}

/*
 * Updates the destination coordinates for a character, base on a main
 * character.
 */
static void
characterUpdateDst(Character player, Character *character)
{
    if (!character->isPlayerControlled) {
        character->dst.x = player.dst.x + character->x - player.x;
        character->dst.y = player.dst.y + character->y - player.y;
    }
}

/*
 * Updates the hitbox, the source and destination coordinates of a
 * character.
 */
void
characterUpdate(Character player, Character *character)
{
    characterUpdateHitbox(character);
    characterUpdateDst(player, character);
}

/* Copies a character to the renderer. */
void
characterRenderCharacter(SDL_Renderer *renderer, SDL_Texture *charText,
                         Character character)
{
    SDL_RenderCopy(renderer, charText, &character.src, &character.dst);
}

/*
 * Initializes a character structure and returns it. This is the safe
 * way to create characters.
 */
Character
characterCreateCharacter(int x, int y, int centerX, int centerY,
                         int spriteLength, int spriteHeight,
                         int hitboxW, int hitboxH, bool isPlayerControlled)
{
    Character character;

    character.x = x;
    character.y = y;
    character.centerX = character.x + centerX;
    character.centerY = character.y + centerY;
    character.spriteLenght = spriteLength;
    character.spriteHeight = spriteHeight;
    character.frame = 0;
    character.actionId = 0;
    character.direction = DOWN;
    character.hitbox.x = character.centerX - hitboxW / 2;
    character.hitbox.y = character.centerY - hitboxH / 2;
    character.hitbox.w = hitboxW;
    character.hitbox.h = hitboxH;
    character.src.x = 0;
    character.src.y = 0;
    character.src.w = spriteLength;
    character.src.h = spriteHeight;
    character.dst.x = 0;
    character.dst.y = 0;
    character.dst.w = spriteLength;
    character.dst.h = spriteHeight;
    character.speed = 3;
    character.nbTimers = 0;
    character.isPlayerControlled = isPlayerControlled;
    character.isAffectedByCollision = true;
    character.collision.down = false;
    character.collision.up = false;
    character.collision.right = false;
    character.collision.left = false;

    return character;
}
