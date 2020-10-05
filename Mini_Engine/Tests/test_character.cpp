#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include "../Characters/character.h"
#include "test_character.h"
static void testCharacterGetChunkX(void);
static void testCharacterGetChunkY(void);
static void testCharacterGetTileX(void);
static void testCharacterGetTileY(void);
static void testCharacterCenterOnScreen(void);
static void testCharacterMoveCharacter(void);

void
testCharacter(void)
{
    testCharacterGetChunkX();
    testCharacterGetChunkY();
    testCharacterGetTileX();
    testCharacterGetTileY();
    testCharacterCenterOnScreen();
    testCharacterMoveCharacter();
}

static void
testCharacterGetChunkX(void)
{
    if (TILESIZE * TILESX != 0) {
        assert(characterGetChunkX(3 * TILESIZE * TILESX) == 3);
        assert(characterGetChunkX(- 2 * TILESIZE * TILESX) == -2);
        assert(characterGetChunkX(0) == 0);
    }
    else {
        assert(characterGetChunkX(1092) == 0);
    }
}

static void
testCharacterGetChunkY(void)
{
    if (TILESIZE * TILESY != 0) {
        assert(characterGetChunkY(-6 * TILESIZE * TILESY) == -6);
        assert(characterGetChunkY(7 * TILESIZE * TILESY) == 7);
        assert(characterGetChunkY(0) == 0);
    }
    else {
        assert(characterGetChunkY(1092) == 0);
    }
}

static void
testCharacterGetTileX(void)
{
    if (TILESIZE != 0) {
        assert(characterGetTileX(3 * TILESIZE * TILESX) == 0);

        if (TILESX > 0) {
#if TILESX > 1
            assert(characterGetTileX(7 * TILESIZE * TILESX + TILESIZE) == 1);
#endif
            assert(characterGetTileX(-3 * TILESIZE * TILESX - 1) ==
                   TILESX - 1);
        }
    }
    else {
        assert(characterGetTileX(102933) == 0);
    }
}

static void
testCharacterGetTileY(void)
{
    if (TILESIZE != 0) {
        assert(characterGetTileY(3 * TILESIZE * TILESY) == 0);


        if (TILESY > 0) {
#if TILESY > 1
            assert(characterGetTileY(7 * TILESIZE * TILESY + TILESIZE) == 1);
#endif
            assert(characterGetTileY(-3 * TILESIZE * TILESY - 1) ==
                   TILESY - 1);
        }
    }
    else {
        assert(characterGetTileY(102933) == 0);
    }
}

static void
testCharacterCenterOnScreen(void)
{
    SDL_Window *window = SDL_CreateWindow("", -200, -300, 200, 300, SDL_WINDOW_BORDERLESS);

    Character character = characterCreateCharacter(0, 0, 0, 0, 50, 75, 50, 75, true);

    /* Regular test. */
    characterCenterOnScreen(window, &character);
    assert(character.dst.x == (200 - character.dst.w) / 2);
    assert(character.dst.y == (300 - character.dst.h) / 2);

    /* Test with negative character destination. */
    SDL_SetWindowSize(window, 1, 1);
    characterCenterOnScreen(window, &character);
    assert(character.dst.x == (1 - character.dst.w) / 2);
    assert(character.dst.y == (1 - character.dst.h) / 2);

    SDL_DestroyWindow(window);
}

static void
testCharacterMoveCharacter(void)
{
    Character character = characterCreateCharacter(0, 0, 0, 0, 0, 0, 0, 0, true);
    Collision collision = {true, true, true, true};
    character.collision = collision;

    /* Test for up and right movement when affected by collision. */
    characterMoveCharacter(&character, 5, 5);
    assert(character.x == 0);
    assert(character.y == 0);

    /* Test for down and right movement when unaffected by collision. */
    character.collision.down = false;
    character.collision.right = false;
    characterMoveCharacter(&character, 5, 5);
    assert(character.x == 5);
    assert(character.y == 5);

    /* Test for left and up movement when affected by collision. */
    characterMoveCharacter(&character, -5, -5);
    assert(character.x == 5);
    assert(character.y == 5);

    /* Test for left and up movement when unaffected by collision. */
    character.collision.left = false;
    character.collision.up = false;
    characterMoveCharacter(&character, -5, -5);
    assert(character.x == 0);
    assert(character.y == 0);

    /* Test when isAffectByCollision is turned off. */
    character.collision.down = true;
    character.collision.up = true;
    character.collision.right = true;
    character.collision.left = true;
    character.isAffectedByCollision = false;

    /* Right and down. */
    characterMoveCharacter(&character, 5, 5);
    assert(character.x == 5);
    assert(character.y == 5);

    /* Left and up. */
    characterMoveCharacter(&character, -5, -5);
    assert(character.x == 0);
    assert(character.y == 0);
}
