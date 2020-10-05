#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include "../../Mini_Engine/Chunks/chunk.h"
#include "objects.h"

SDL_Texture *
getObjectsTexture(SDL_Renderer *renderer)
{
    SDL_Surface *surf = IMG_Load("Demo/assets/object_sprite.png");

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
objectAssignProperties(Chunk *chunk, int index)
{
    for (int i = 0; i < chunk[index].nbObjects; i++) {
        switch (chunk[index].object[i].id) {
            case 0:
                chunk[index].object[i].src.x = 0;
                chunk[index].object[i].src.y = 0;
                chunk[index].object[i].src.w = 64;
                chunk[index].object[i].src.h = 64;
                chunk[index].object[i].centerY = 64;
                chunk[index].object[i].nbFrames = 1;
                chunk[index].object[i].renderMode = RENDER_HYBRID;
                chunk[index].object[i].textureIndex = 0;
                break;
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
        }
    }
}