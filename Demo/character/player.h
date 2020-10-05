#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "../../Mini_Engine/Characters/character.h"

SDL_Texture * getVillagerTexture(SDL_Renderer *renderer);
void playerWalk(Character *character, EngineEvent event);
void playerCreateTimers(Character *character, int number);

#endif // PLAYER_H_INCLUDED
