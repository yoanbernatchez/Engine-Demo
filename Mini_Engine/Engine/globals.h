#ifndef GLOBALS_H_INCLUDED
#define GLOBALS_H_INCLUDED

/**
 * Number of chunks to be loaded at the same time.
 * DO NOT CHANGE. The number of chunks cannot be
 * anything other than 4 for now.
 */
#define NBCHUNKS 4
#define TILESIZE 64    /**< The size of a tile in pixels (x and y).    */
#define TILESX 64      /**< The number of horizontal tiles in a chunk. */
#define TILESY 64      /**< The number of vertical tiles in a chunk.   */
/*
 * Change TILESIZE, TILESX AND TILESY to your needs, as long as TILESX
 * and TILESY are larger than zero and TILESIZE larger than 10.
 */


#include <SDL.h>
#include <stdbool.h>

/** Enumeration of directions a character or object can be facing. */
enum EngDirectionType {ENG_DOWN, ENG_UP, ENG_RIGHT, ENG_LEFT};

/** Enumeration of render modes for objects. */
enum EngRenderMode {ENG_RENDER_BACKGROUND, ENG_RENDER_HYBRID,
                    ENG_RENDER_FOREGROUND};

/*---------------------------------------------------------------------------*/
/* Global types                                                              */
/*---------------------------------------------------------------------------*/

typedef struct _EngCollision {
    bool left;
    bool right;
    bool up;
    bool down;
} EngCollision;
/**< Structure containing collision data in the form of booleans. */

typedef struct _EngChar {
    int x;
    int y;
    int center_x;
    int center_y;
    int sprite_lenght;
    int sprite_height;
    int frame;
    int action_id;
    int direction;
    int speed;
    bool is_player_controlled;
    bool is_affected_by_collision;

    double *timer;
    int nb_timers;

    SDL_Rect hitbox;
    SDL_Rect src;
    SDL_Rect dst;

    EngCollision collision;
} EngCharacter;
/**< Structure containing character data (position, sprite size, etc). */

typedef struct _EngEvent {
    bool left_pressed;
    bool right_pressed;
    bool up_pressed;
    bool down_pressed;

    bool window_resized;
} EngEvent;
/**< Structure containing booleans corresponding to events. */

typedef struct _EngPoint2d {
    int x;
    int y;
} EngPoint2d;
/**< Base structure containing two variables. */

typedef struct _EngTile {
    int id;
    int frame;
    bool has_collision;
} EngTile;
/**< Structure containing tile information (used in chunks). */

typedef struct _EngObject {
    int id;
    int x;
    int y;
    int center_y;
    int frame;
    int nb_frames;
    int texture_index;
    int render_mode;

    SDL_Rect src;
    SDL_Rect dst;
} EngObject;
/**< Structure containing object information (used in chunks). */

typedef struct _EngChunk {
    int old_chunk_x;
    int old_chunk_y;
    int chunk_x;
    int chunk_y;
    int nb_objects;
    bool updated;

    EngTile tile[TILESX][TILESY];
    EngObject *object;
} EngChunk;
/**<
 * Structure containing chunk information, such as
 * tiles and objects.
 */

#endif /* GLOBALS_H_INCLUDED */
