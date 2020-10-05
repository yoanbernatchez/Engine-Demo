#ifndef RENDER_H_INCLUDED
#define RENDER_H_INCLUDED

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
void renderTiles(SDL_Renderer *renderer, Chunk chunk[], Character player,
                 SDL_Texture *tileText[], int nbTextures);

void
renderHybridObjects(SDL_Renderer *renderer, SDL_Texture *charText[],
                    SDL_Texture *objText[], Character character[], int nbCharacters, Chunk chunk[]);

#endif // RENDER_H_INCLUDED
