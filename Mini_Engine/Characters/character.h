#ifndef CHARACTER_HEADER_H_INCLUDED
#define CHARACTER_HEADER_H_INCLUDED

#include <stdbool.h>
#include <SDL.h>
#include "../Engine/globals.h"

/**
 * @brief Finds out which chunk a point ends in and returns it's id.
 *
 * @param x: The point's coordinates in x.
 *
 * @return The chunk in y the point ends in.
 *
 * @sa eng_char_get_chunk_y ()
 */
int eng_char_get_chunk_x (int x);

/**
 * @brief Finds out which chunk a point ends in and returns it's id.
 *
 * @param y: The point's coordinates in y.
 *
 * @return The chunk in y the point ends in.
 *
 * @sa eng_char_get_chunk_x ()
 */
int eng_char_get_chunk_y (int y);

/**
 * @brief Finds out which tile a point ends on (in a chunk) and returns its
 *        value.
 *
 * @param x: The point's coordinates in x.
 *
 * @return The tile the point ends on in x.
 *
 * @sa eng_char_get_tile_y ()
 */
int eng_char_get_tile_x (int x);

/**
 * @brief Finds out which a point ends on (in a chunk) and returns its
 *        value.
 *
 * @param y: The point's coordinates in y.
 *
 * @return The tile the point ends on in y.
 *
 * @sa eng_char_get_tile_x ()
 */
int eng_char_get_tile_y (int y);

/**
 * @brief Sets a new collision structure filled with collision data to a
 *        character.
 *
 * @param character: Character that receives the new structure.
 * @param collision: Collision structure containing collision data.
 */
void eng_char_set_collision (EngCharacter *character, EngCollision collision);

/**
 * @brief Sets the action id for a character.
 *
 * @param character: Character that receives a new action id.
 * @param action_id: Id of the action to give to the character
 *                   (example: IDLE: 0, WALKING: 1, RUNNING: 2, ...).
 *
 * @sa eng_char_set_direction ()
 */
void eng_char_set_action (EngCharacter *character, int action_id);

/**
 * @brief Sets the direction for a character.
 *
 * @param character: Character that receives a new direction.
 * @param direction: Direction to give to the character.
 *
 * @sa eng_char_set_action ()
 */
void eng_char_set_direction (EngCharacter *character,
                             EngDirectionType direction);

/**
 * @brief Sets a character to be affected by collision or not.
 *
 * @param character:              Character with the is_affected_by_collision
 *                                element to modify.
 * @param is_affect_by_collision: False if not affect by collision, true if
 *                                affected.
 */
void eng_char_set_is_collidable (EngCharacter *character,
                                 bool is_affected_by_collision);

/**
 * @brief Centers a character on screen (based on window size).
 *
 * @param window:    SDL_Window with size information.
 * @param character: Character to center.
 */
void eng_char_center_on_screen (SDL_Window *window, EngCharacter *character);

/**
 * @brief Performs a collision check on a character if the character is
 *        affected by collision, then moves the character.
 *
 * @param character: The character to move.
 * @param amount_x:  How much to move in the x axis.
 * @param amount_y:  How much to move in the y axis.
 */
void eng_char_move_character (EngCharacter *character, int amount_x,
                              int amount_y);

/**
 * @brief Updates the hitbox, the source and destination coordinates of a
 *        character.
 *
 * @param player:    The main character (serves as a point of reference to
 *                   update other characters).
 * @param character: The character to update.
 */
void eng_char_update (EngCharacter player, EngCharacter *character);

/**
 * @brief Copies a character to the renderer.
 *
 * @param renderer:  Targeted renderer to copy images to.
 * @param char_text: Texture containing the character's sprites.
 * @param character: The character to render.
 */
void eng_char_render_character (SDL_Renderer *renderer, SDL_Texture *char_text,
                                EngCharacter character);

/**
 * @brief Initializes a character structure and returns it. This is the safe
 *        way to create characters.
 *
 * @param x:                    Position of the character in x on the map.
 * @param y:                    Position of the character in y on the map.
 * @param center_x:             Center of the character in x.
 * @param center_y:             Center of the character in y.
 * @param sprite_length:        Length of the character's sprite.
 * @param sprite_height:        Height of the character's sprite.
 * @param hitbox_w:             Width of the character's hitbox.
 * @param hitbox_h:             Height of the character's hitbox.
 * @param is_player_controlled: True if controlled by player, false if not.
 *
 * @return An initialized character structure.
 */
EngCharacter eng_char_create_character (int x, int y,
                                        int center_x, int center_y,
                                        int sprite_lenght, int sprite_height,
                                        int hitbox_w, int hitbox_h,
                                        bool is_player_controlled);

/**
 * @brief Destroys and deallocates resources given to a character structure.
 *
 * @param character: Character structure to destroy.
 */
void eng_char_destroy_character (EngCharacter *character);

/**
 * @brief Allocates timers to a character structure.
 *
 * @param character: Character to allocate memory to.
 * @param nb_timers: The number of timers to allocate memory for.
 */
void eng_char_create_timers (EngCharacter *character, int nb_timers);

#endif /* CHARACTER_HEADER_H_INCLUDED */
