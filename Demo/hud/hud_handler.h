#ifndef HUD_HANDLER_H_INCLUDED
#define HUD_HANDLER_H_INCLUDED

#include <SDL.h>
#include "../../Mini_Engine/HUD/hud.h"
#include "../../Mini_Engine/Characters/character.h"
#include "../../Mini_Engine/Time/time.h"

/**
 * @brief Loads presets to an array of huds.
 *
 * @param window:   SDL_Window allowing us to center the huds on screen.
 * @param renderer: Renderer allowing us to create textures for the huds.
 */
void hud_load_presets (SDL_Window *window, SDL_Renderer *renderer,
                       EngHud hud[]);

/**
 * @brief Returns the sprite sheet texture for hud elements.
 *
 * @param renderer: Renderer allowing us to create textures.
 *
 * @return A hud sprite sheet texture.
 */
SDL_Texture * hud_get_texture (SDL_Renderer *renderer);

/**
 * @brief Checks, updates and manages all the huds.
 *
 * @param window:    Window allowing us to center a hud on screen.
 * @param renderer:  Renderer allowing us to create textures.
 * @param hud:       Array of huds to handle.
 * @param character: Array of characters for huds to get data from.
 * @param timer:     Array of timers for huds, used for updating purposes.
 */
void hud_handler (SDL_Window *window, SDL_Renderer *renderer, EngHud hud[],
                  EngCharacter character[], double timer[]);

/**
 * @brief Centers all the huds on screen.
 *
 * @param window: Window allowing us to center huds on screen.
 * @param hud: Array of huds to center on screen.
 */
void hud_center_huds (SDL_Window *window, EngHud hud[]);

/**
 * @brief Sets the opacity of a hud's components and borders.
 *
 * @param hud:     Hud to modify the opacity of.
 * @param opacity: New opacity to give (0-255).
 */
void set_hud_opacity (EngHud *hud, int opacity);

#endif /* HUD_HANDLER_H_INCLUDED */
