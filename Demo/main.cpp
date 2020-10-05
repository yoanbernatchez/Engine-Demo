#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "character/player.h"
#include "objects/objects.h"
#include "../Mini_Engine/Render/render.h"
#include "../Mini_Engine/Engine/globals.h"
#include "../Mini_Engine/HUD/window.h"
#include "../Mini_Engine/Time/time.h"
#include "../Mini_Engine/File_Utilities/file_utilities.h"

#include "../Mini_Engine/Chunks/chunk.h"
#include "../Mini_Engine/Chunks/tile.h"
#include "../Mini_Engine/Characters/character.h"

#include "../Mini_Engine/Events/events.h"
#include "../Mini_Engine/Collision/collision_handler.h"
#include "../Mini_Engine/Chunks/pathfinding.h"
#include "../Mini_Engine/Tests/tests.h"

int main(int argc, char * argv[])
{
    /* Initialize SDL. */
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();

    /* Create base window and renderer. */
    SDL_Window* window;
    window = SDL_CreateWindow("Demo", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, 900, 700,
                              SDL_WINDOW_RESIZABLE);

    SDL_Renderer* renderer;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (window == NULL || renderer == NULL) {
       printf("Could not create window or renderer.\n");
       return -1;
    }

    /* Initialize chunks. */
    Chunk chunk[NBCHUNKS];
    for(int i = 0; i < NBCHUNKS; i++){
        chunk[i] = chunkCreateChunk();
    }

    /* Initialize characters. */
    Character character[2];
    character[0] = characterCreateCharacter(0, 0, 50/2, 75, 50, 75, 40, 40, true);
    playerCreateTimers(&character[0], 1);
    character[1] = characterCreateCharacter(-100, 0, 50/2, 75, 50, 75, 40, 40, false);

    /* Load sprite sheets. */
    SDL_Texture *villagerText[1];
    villagerText[0] = getVillagerTexture(renderer);
    SDL_Texture *objectText[1];
    objectText[0] = getObjectsTexture(renderer);
    SDL_Surface *tileSurf = IMG_Load("Demo/assets/tile_sprite.bmp");
    SDL_Texture *tileText[1];
    tileText[0] = SDL_CreateTextureFromSurface(renderer, tileSurf);
    if(tileText == NULL) printf("Could not load tile sprites.\n");

    characterCenterOnScreen(window, &character[0]);

    /* Run engine tests. */
    engineTestAll();

    SDL_Event sdlEvent;
    EngineEvent event = {false, false, false, false};
    double renderTimer = timeGetRealTime();

    /* Main Loop. */
    while(eventHandleEvents(sdlEvent, &event)){

        SDL_PollEvent(&sdlEvent);

        /* Updating. */
        characterUpdate(character[0], &character[0]);
        characterSetCollision(&character[0], getCollisionInfo(chunk, character[0], event));
        playerWalk(&character[0], event);
        characterUpdate(character[0], &character[1]);
        chunkRotateChunks(chunk, character[0].x, character[0].y,
                          characterGetChunkX(character[0].x), characterGetChunkY(character[0].y));
        objectAssignProperties(chunk, 0);
        if(event.windowResized){
            characterCenterOnScreen(window, &character[0]);
            event.windowResized = false;
        }

        /* Rendering. */
        if(timeHasElapsed(&renderTimer, true, MILLISECOND, 17)){
            renderTiles(renderer, chunk, character[0], tileText, 1);

            renderHybridObjects(renderer, villagerText, objectText, character, 2, chunk);
            SDL_RenderPresent(renderer);
        }
    }

    /* Destroy allocated resources. */
    SDL_DestroyTexture(villagerText[0]);

    return 0;
}
