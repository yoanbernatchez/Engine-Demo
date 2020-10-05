/*
 * Author: YOAN BERNATCHEZ
 * Date: 2020-09-21
 *
 * This file contains a function that registers keyboard, window and
 * mouse events to a structure (EngineEvent). The function can be modified
 * to register more events, but EngineEvent should also be modified if this
 * is the case.
 */

#include "events.h"
#include <stdio.h>

/*
 * Transforms SDL events to booleans stored in an EngineEvent structure.
 *
 * This function should be modified by the user (adding handled events
 * and such).
 *
 * Modify the EngineEvent structure if you add handled events.
 */
bool eventHandleEvents(SDL_Event sdlEvent, EngineEvent* event)
{
    bool handleEvents = true;

    switch(sdlEvent.type)
    {
        case SDL_QUIT:
            handleEvents = false;
            break;

        case SDL_WINDOWEVENT:
            switch(sdlEvent.window.event)
            {
                case SDL_WINDOWEVENT_RESIZED:
                    event->windowResized = true;
                    break;
            }
            break;

        case SDL_KEYDOWN:
            switch(sdlEvent.key.keysym.sym)
            {
                case SDLK_LEFT:
                    event->leftPressed = true;
                    break;

                case SDLK_RIGHT:
                    event->rightPressed = true;
                    break;

                case SDLK_UP:
                    event->upPressed = true;
                    break;

                case SDLK_DOWN:
                    event->downPressed = true;
                    break;

                case SDLK_ESCAPE:
                    handleEvents = false;
                    break;
            }
            break;

        case SDL_KEYUP:
            switch(sdlEvent.key.keysym.sym)
            {
                case SDLK_LEFT:
                    event->leftPressed = false;
                    break;

                case SDLK_RIGHT:
                    event->rightPressed = false;
                    break;

                case SDLK_UP:
                    event->upPressed = false;
                    break;

                case SDLK_DOWN:
                    event->downPressed = false;
                    break;
            }
            break;
    }

    return handleEvents;
}
