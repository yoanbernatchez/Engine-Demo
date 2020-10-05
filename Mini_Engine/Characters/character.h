#ifndef CHARACTER_HEADER_H_INCLUDED
#define CHARACTER_HEADER_H_INCLUDED

#include "../Engine/globals.h"

/**
 * @brief Finds out which chunk a point ends in and returns it's id.
 *
 * @param x: The point's position in x.
 *
 * @return The chunk in y the point ends in.
 *
 * @sa characterGetChunkY()
 */
int characterGetChunkX(int x);

/**
 * @brief Finds out which chunk a point ends in and returns it's id.
 *
 * @param y: The point's position in y.
 *
 * @return The chunk in y the point ends in.
 *
 * @sa characterGetChunkX()
 */
int characterGetChunkY(int y);

/**
 * @brief Finds out which tile the a point ends on (in a chunk) and returns its
 *        value.
 *
 * @param x: Position in x of the point.
 *
 * @return The tile the point ends on in x.
 *
 * @sa characterGetTileY()
 */
int characterGetTileX(int x);

/**
 * @brief Finds out which tile a point ends on (in a chunk) and returns its
 *        value.
 *
 * @param y: Position in y of a point.
 *
 * @return The tile the point ends on in y.
 *
 * @sa characterGetTileX()
 */
int characterGetTileY(int y);

/**
 * @brief Sets a new collision structure filled with collision data to a
 *        character.
 *
 * @param character: Character that receives the new structure.
 * @param collision: Collision structure containing collision data.
 */
void characterSetCollision(Character *character, Collision collision);

/**
 * @brief Sets the action id for a character.
 *
 * @param character: Character that receives a new action id.
 * @param actionId:  Id of the action to give to the character
 *                   (example: IDLE: 0, WALKING: 1, RUNNING: 2, ...).
 *
 * @sa characterSetDirection()
 */
void characterSetAction(Character *character, int actionId);

/**
 * @brief Sets the direction for a character.
 *
 * @param character: Character that receives a new direction.
 * @param direction: Direction to give to the character.
 *
 * @sa characterSetAction()
 */
void characterSetDirection(Character *character, EngineDirectionType direction);

/**
 * @brief Sets a character to be affected by collision or not.
 *
 * @param character:           Character with the isAffectByCollision element
 *                             to modify.
 * @param isAffectByCollision: False if not affect by collision, true if
 *                             affected.
 */
void characterSetIsCollidable(Character *character, bool isAffectedByCollision);

/**
 * @brief Centers a character on screen (based on window size).
 *
 * @param window:    SDL_Window with size information.
 * @param character: Character to center.
 */
void characterCenterOnScreen(SDL_Window *window, Character *character);

/**
 * @brief Performs a collision check on a character if the character is
 *        affected by collision, then moves the character.
 *
 * @param character: The character to move.
 * @param amountX:   How much to move in the x axis.
 * @param amountY:   How much to move in the y axis.
 */
void characterMoveCharacter(Character *character, int amountX, int amountY);

/**
 * @brief Updates the hitbox, the source and destination coordinates of a
 *        character.
 *
 * @param player:    The main character (serves as a point of reference to
 *                   update other characters).
 * @param character: The character to update.
 */
void characterUpdate(Character player, Character *character);

/**
 * @brief Copies a character to the renderer.
 *
 * @param renderer:  Targeted renderer to copy images to.
 * @param charText:  Texture containing the character's sprites.
 * @param character: The character to render.
 */
void characterRenderCharacter(SDL_Renderer *renderer, SDL_Texture *charText, Character character);

/**
 * @brief Initializes a character structure and returns it. This is the safe
 *        way to create characters.
 *
 * @param x:                  Position of the character in x on the map.
 * @param y:                  Position of the character in y on the map.
 * @param centerX:            Center of the character in x.
 * @param centerY:            Center of the character in y.
 * @param spriteLength:       Length of the character's sprite.
 * @param spriteHeight:       Height of the character's sprite.
 * @param hitboxW:            Width of the character's hitbox.
 * @param hitboxH:            Height of the character's hitbox.
 * @param isPlayerControlled: True if controlled by player, false if not.
 *
 * @return An initialized character structure.
 */
Character characterCreateCharacter(int x, int y, int centerX, int centerY, int spriteLenght, int spriteHeight, int hitboxW, int hitboxH, bool isPlayerControlled);

#endif /* CHARACTER_HEADER_H_INCLUDED */
