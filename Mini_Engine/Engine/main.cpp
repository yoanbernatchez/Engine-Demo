#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "globals.h"
#include "../HUD/window.h"
#include "../Time/time.h"
#include "../File_Utilities/file_utilities.h"

#include "../Chunks/chunk.h"
#include "../Chunks/tile.h"
#include "../Characters/character.h"

#include "../Events/events.h"
#include "../Collision/collision_handler.h"
#include "../Chunks/pathfinding.h"
#include "../Tests/tests.h"
#include "../../Game/HUD/hud_handler.h"
#include "../../Game/Villagers/villager_handler.h"
#include "../../Game/Player/player_handler.h"

int main(int argc, char * argv[])
{
    /* Initialize SDL. */
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();

    /* Create base window and renderer. */
    SDL_Window* window = SDL_CreateWindow("Yoko Island", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 900, 700, SDL_WINDOW_RESIZABLE);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    EngineEvent event = {false, false, false, false};

    /* Initialize chunks. */
    Chunk chunk[NBCHUNKS];
    for(int i = 0; i < NBCHUNKS; i++){
        chunk[i] = chunkCreateChunk();
    }

    /* Initialize characters. */
    Character player = characterCreateCharacter(0, 0, 50/2, 75, 50, 75, 40, 40, true);
    Character npc = characterCreateCharacter(-100, 0, 50/2, 75, 50, 75, 40, 40, false);
        chunkRotateChunks(chunk, player.x, player.y,
                          characterGetChunkX(player.x), characterGetChunkY(player.y));

testAll();


    /* Load sprite sheets. */
    SDL_Texture* villagerText = villagerLoadSpriteSheet(renderer);

    //Sprite sheets initialization
    SDL_Surface* tileSurf = IMG_Load("spritesheet0.bmp");
    SDL_Texture* tileText[2];
    tileText[0] = SDL_CreateTextureFromSurface(renderer, tileSurf);
    if(tileText == NULL) printf("error");

    //Character image
    characterCenterOnScreen(window, &player);

    SDL_Event sdlEvent;
    double renderTimer = timeGetRealTime();

    /* Main Loop. */
    while(eventHandleEvents(sdlEvent, &event)){

        SDL_PollEvent(&sdlEvent);

        /* Updating. */
        characterUpdate(player, &player);
        characterSetCollision(&player, getCollisionInfo(chunk, player, event));
        characterUpdate(player, &npc);
        chunkRotateChunks(chunk, player.x, player.y,
                          characterGetChunkX(player.x), characterGetChunkY(player.y));

        if(event.windowResized){
            characterCenterOnScreen(window, &player);
            event.windowResized = false;
        }

        /* Rendering. */
        if(timeHasElapsed(&renderTimer, true, MILLISECOND, 17)){
            chunkRenderChunks(renderer, chunk, player.x, player.y,
                              player.dst.x + player.dst.w / 2,
                              player.dst.y + player.dst.h, tileText, NULL);

            characterRenderCharacter(renderer, villagerText, player);
            characterRenderCharacter(renderer, villagerText, npc);


            SDL_RenderPresent(renderer);
        }

    }

    /* Destroy allocated resources. */
    SDL_DestroyTexture(villagerText);

    return 0;
}
