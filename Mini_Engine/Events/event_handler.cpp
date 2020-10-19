/*
 * Author: YOAN BERNATCHEZ
 * Date: 2020-09-21
 *
 * This file contains a function that registers keyboard, window and
 * mouse events to a structure (EngEvent). The function can be modified
 * to register more events, but EngEvent should also be modified if this
 * is the case.
 */

#include "events.h"

/*
 * Transforms SDL events to booleans stored in an EngineEvent structure.
 *
 * This function can be modified by the user (for adding handled events
 * and such).
 *
 * Modify the EngEvent structure if you add handled events.
 */
bool
eng_event_handle_events (SDL_Event sdl_event, EngEvent *event)
{
    bool keep_handling_events = true;

    switch (sdl_event.type) {
    case SDL_QUIT:
        keep_handling_events = false;
        break;
    case SDL_WINDOWEVENT:
        switch (sdl_event.window.event) {
        case SDL_WINDOWEVENT_RESIZED:
            event->window_resized = true;
            break;
        }
        break;
    case SDL_KEYDOWN:
        switch (sdl_event.key.keysym.sym) {
        case SDLK_LEFT:
            event->left_pressed = true;
            break;
        case SDLK_RIGHT:
            event->right_pressed = true;
            break;
        case SDLK_UP:
            event->up_pressed = true;
            break;
        case SDLK_DOWN:
            event->down_pressed = true;
            break;
        case SDLK_ESCAPE:
            keep_handling_events = false;
            break;
        }
        break;
    case SDL_KEYUP:
        switch (sdl_event.key.keysym.sym) {
        case SDLK_LEFT:
            event->left_pressed = false;
            break;
        case SDLK_RIGHT:
            event->right_pressed = false;
            break;
        case SDLK_UP:
            event->up_pressed = false;
            break;
        case SDLK_DOWN:
            event->down_pressed = false;
            break;
        }
        break;
    }

    return keep_handling_events;
}
