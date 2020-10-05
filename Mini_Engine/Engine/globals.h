#ifndef GLOBALS_H_INCLUDED
#define GLOBALS_H_INCLUDED

/**
 * Number of chunks to be loaded at the same time.
 * DO NOT CHANGE. The number of chunks cannot be
 * anything other than 4 for now.
 */
#define NBCHUNKS 4
#define TILESIZE 64     /**< The size of a tile in pixels (x and y).    */
#define TILESX 64       /**< The number of horizontal tiles in a chunk. */
#define TILESY 64       /**< The number of vertical tiles in a chunk.   */

#include <SDL.h>
#include <stdbool.h>

/** Enumeration of directions a character or object can be facing. */
enum EngineDirectionType {DOWN, UP, RIGHT, LEFT};

enum EngineRenderMode{RENDER_BACKGROUND, RENDER_HYBRID, RENDER_FOREGROUND};

/*---------------------------------------------------------------------------*/
/* Typedefs required globally                                                */
/*---------------------------------------------------------------------------*/

typedef struct _collision{
    bool left;
    bool right;
    bool up;
    bool down;
} Collision;
/**< Structure containing collision data in the form of booleans. */

typedef struct _char{
    int x;
    int y;
    int centerX;
    int centerY;
    int spriteLenght;
    int spriteHeight;
    int frame;
    int actionId;
    int direction;
    int speed;
    bool isPlayerControlled;
    bool isAffectedByCollision;

    double *timer;
    int nbTimers;

    SDL_Rect hitbox;
    SDL_Rect src;
    SDL_Rect dst;

    Collision collision;
} Character;
/**< Structure containing character data (position, sprite size, etc). */

typedef struct
{
    bool leftPressed;
    bool rightPressed;
    bool upPressed;
    bool downPressed;

    bool windowResized;
} EngineEvent;
/**< Structure containing booleans corresponding to events. */

typedef struct
{
    int x;
    int y;
} Point2d;
/**< Structure containing booleans corresponding to events. */

typedef struct
{
    int id;
    int frame;
    bool collision;
} Tile;
/**< Structure containing tile information (used in chunks). */

typedef struct
{
    int id;
    int x;
    int y;
    int centerY;
    int frame;
    int nbFrames;
    int textureIndex;
    int renderMode;

    SDL_Rect src;
    SDL_Rect dst;
} Object;
/**< Structure containing object information (used in chunks). */

typedef struct
{
    int oldChunkX;
    int oldChunkY;
    int chunkX;
    int chunkY;
    int nbObjects;
    bool updated;

    Tile tile[TILESX][TILESY];
    Object *object;
} Chunk;
/**<
 * Structure containing chunk information, such as
 * tiles and objects.
 */

#endif /* GLOBALS_H_INCLUDED */
