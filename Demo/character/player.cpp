#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL.h>
#include <SDL_image.h>
#include "player.h"
#include "../../Mini_Engine/Engine/globals.h"
#include "../../Mini_Engine/Time/time.h"

SDL_Texture *
getVillagerTexture(SDL_Renderer *renderer)
{
    SDL_Surface *surf = IMG_Load("Demo/assets/character_sprite.png");

    if (surf == NULL) {
        printf("%s\n", SDL_GetError());
    }

    SDL_Texture *text = SDL_CreateTextureFromSurface(renderer, surf);

    if (text == NULL) {
        printf("%s\n", SDL_GetError());
    }

    return text;
}

void
playerCreateTimers(Character *character, int number)
{
    if (character->nbTimers == 0) {
        character->timer = (double*) malloc(number * sizeof(double));
    }
    else {
        character->timer = (double*) realloc(character->timer, number * sizeof(double));
    }
}

void
playerWalk(Character *character, EngineEvent event)
{
    if (timeHasElapsed(character->timer, true, MILLISECOND, 17)) {
        if (event.rightPressed) {
            characterMoveCharacter(character, character->speed, 0);
        }
        if (event.leftPressed) {
            characterMoveCharacter(character, -character->speed, 0);
        }
        if (event.upPressed) {
            characterMoveCharacter(character, 0, -character->speed);
        }
        if (event.downPressed) {
            characterMoveCharacter(character, 0, character->speed);
        }
    }
}
