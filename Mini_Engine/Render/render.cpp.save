#include <stdio.h>
#include <SDL.h>
#include <limits.h>
#include "../Characters/character.h"
#include "render.h"

typedef struct {
    int y;
    int objectIndex;
    int chunkIndex;
    bool isCharacter;
} Triplet;

static void
selectionSort(Triplet *order, int nbObjects);

/*
 * Pastes to the renderer all the tiles and objects from the array of chunk
 * data.
 */
void
renderTiles(SDL_Renderer *renderer, Chunk chunk[], Character player,
            SDL_Texture *tileText[], int nbTextures)
{
    int tileTextureIndex = 0;
    int nbHorizontalTiles = 0;
    int nbVerticalTiles = 0;

    SDL_QueryTexture(tileText[0], NULL, NULL, &nbHorizontalTiles, &nbVerticalTiles);

    nbHorizontalTiles /= TILESIZE;
    nbVerticalTiles /= TILESIZE;

    SDL_Rect src = {0, 0, TILESIZE, TILESIZE};
    SDL_Rect dst = {0, 0, TILESIZE, TILESIZE};

    /* Copy tiles to renderer. */
    for (int h = 0; h < NBCHUNKS; h++) {
        for (int i = 0; i < TILESY; i++) {
            for (int j = 0; j < TILESX; j++) {
                src.x = (chunk[h].tile[j][i].id % nbHorizontalTiles) * TILESIZE;
                src.y = (chunk[h].tile[j][i].id / nbVerticalTiles) * TILESIZE;

                dst.x = j * TILESIZE + chunk[h].chunkX*TILESX*TILESIZE + player.dst.x + player.centerX - player.x;
                dst.y = i * TILESIZE + chunk[h].chunkY*TILESY*TILESIZE + player.dst.y + player.centerY - player.y;

                tileTextureIndex = chunk[h].tile[j][i].id / (nbHorizontalTiles * nbVerticalTiles);

                /*
                 * Make sure that something exists at the index, then copy to
                 * renderer.
                 */
                if (tileTextureIndex < nbTextures) {
                    SDL_RenderCopy(renderer, tileText[tileTextureIndex], &src, &dst);
                }
            }
        }
    }
}

void
renderBackgroundObjects(SDL_Renderer *renderer, SDL_Texture *text[],
                        Character character[], Chunk chunk[])
{

}

void
renderHybridObjects(SDL_Renderer *renderer, SDL_Texture *charText[],
                    SDL_Texture *objText[], Character character[], int nbCharacters, Chunk chunk[])
{
    int nbObjects = 0;
    int orderIndex = 0;
    SDL_Rect rect = {0,0,64,64};

    nbObjects = nbCharacters;

    /* Check how many objects there are to copy to the renderer. */
    for (int i = 0; i < NBCHUNKS; i++) {
        for(int j = 0; j < chunk[i].nbObjects; j++) {
            if (chunk[i].object[j].renderMode == RENDER_HYBRID) {
                nbObjects++;
            }
        }
    }

    Triplet order[nbObjects];

    /* Assign values to the order structure, readying them to be sorted. */
    for (int i = 0; i < NBCHUNKS; i++) {
        for(int j = 0; j < chunk[i].nbObjects; j++) {
            if (chunk[i].object[j].renderMode == RENDER_HYBRID) {
                order[orderIndex].y = chunk[i].object[j].y;
                order[orderIndex].isCharacter = false;
                order[orderIndex].objectIndex = j;
                order[orderIndex].chunkIndex = i;
                orderIndex++;
            }
        }
    }

    for (int i = 0; i < nbCharacters; i++) {
        order[orderIndex].y = character[i].y;
        order[orderIndex].isCharacter = true;
        order[orderIndex].objectIndex = i;
        order[orderIndex].chunkIndex = -1;
        orderIndex++;
    }

    /* Sort the objects based on their y values. */
    selectionSort(order, nbObjects);

    for (int i = 0; i < nbObjects; i++) {
        if (order[i].isCharacter) {
            SDL_RenderCopy(renderer, charText[0], &character[order[i].objectIndex].src, &character[order[i].objectIndex].dst);
        }
        else {
            rect.x = chunk[order[i].chunkIndex].object[order[i].objectIndex].x + character[0].dst.x + character[0].centerX - character[0].x;
            rect.y = chunk[order[i].chunkIndex].object[order[i].objectIndex].y + character[0].dst.y - chunk[order[i].chunkIndex].object[order[i].objectIndex].centerY + character[0].centerY - character[0].y;
            rect.w = 64;
            rect.h = 64;
            SDL_RenderCopy(renderer,
                           objText[chunk[order[i].chunkIndex].object[order[i].objectIndex].textureIndex],
                           &chunk[order[i].chunkIndex].object[order[i].objectIndex].src,
                           &rect);
        }
    }
}

static void
selectionSort(Triplet *order, int nbObjects)
{
    Triplet temp = {0, 0, 0, false};
    int indexMin = 0;

    for (int i = 0; i < nbObjects; i++) {

        indexMin = i;

        for (int j = i; j < nbObjects; j++) {
            if (order[j].y < order[indexMin].y) {
                indexMin = j;
            }
        }

        temp = order[i];
        order[i] = order[indexMin];
        order[indexMin] = temp;
    }
}

void
renderForegroundObjects()
{

}

