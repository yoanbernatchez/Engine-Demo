#ifndef RENDER_H_INCLUDED
#define RENDER_H_INCLUDED

#include <SDL.h>
#include "../Engine/globals.h"

/**
 * @brief Pastes to the renderer all the tiles and objects from the array
 *        of chunk data.
 *
 * @param renderer:     Target renderer.
 * @param chunk:        Array of chunk containing tiles and objects to display.
 * @param charX:        Position of a character in x.
 * @param charY:        Position of a character in y.
 * @param charCenterX:  Center position of a character in x.
 * @param charCenterY:  Center position of a character in y.
 * @param tileText:     Array of textures used to display tiles.
 * @param objectText:   Array of textures used to display objects.
 */
void eng_render_tiles (SDL_Renderer *renderer, EngChunk chunk[],
                      EngCharacter player, SDL_Texture *tileText[],
                      int nbTextures);
/**
 * @brief Renders objects and characters in a specific order on screen.
 *
 * @param renderer:      Renderer to copy to.
 * @param char_text:     Character sprite textures.
 * @param obj_text:      Object sprite textures.
 * @param character:     Array of characters to print on screen.
 * @param nb_characters: Number of characters to print on screen.
 * @param chunk:         Chunks containing the objects to render.
 */
void eng_render_objects (SDL_Renderer *renderer, SDL_Texture *charText[],
                         SDL_Texture *objText[], EngCharacter character[],
                         int nbCharacters, EngChunk chunk[]);

#endif /* RENDER_H_INCLUDED */
