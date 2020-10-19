#ifndef ZONE_HUD_H_INCLUDED
#define ZONE_HUD_H_INCLUDED

#include <SDL.h>
#include "../../Mini_Engine/HUD/hud.h"
#include "../../Mini_Engine/Characters/character.h"
#include "../../Mini_Engine/Time/time.h"

/**
 * @brief Returns a hud structure that has been initialized with zone hud
 *        presets.
 *
 * @param renderer: Renderer allowing us to create new textures.
 *
 * @return A hud structure filled with the zone hud presets.
 */
EngHud hud_create_zone_hud (SDL_Renderer *renderer);

/**
 * @brief Center the zone hud on screen.
 *
 * @param window: Window allowing us to center a hud on screen.
 * @param hud:    Hud corresponding to the zone hud.
 */
void center_zone_hud (SDL_Window *window, EngHud *hud);

/**
 * @brief Checks if we enter a new zone and if we need to update the texture
 *        of the zone hud. If not, simply dims the zone hud until it's
 *        invisible.
 *
 * @param window:   Window allowing us to center the zone hud on screen.
 * @param renderer: Renderer allowing us to create new textures.
 * @param hud:      Zone hud structure.
 * @param player:   Player we retrieve the zone from.
 * @param timer:    Timer for dimming or showing the zone hud.
 */
void update_zone_hud (SDL_Window *window, SDL_Renderer *renderer, EngHud *hud,
                      EngCharacter player, double *timer);


#endif /* ZONE_HUD_H_INCLUDED */
