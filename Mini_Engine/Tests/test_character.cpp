#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include "../Characters/character.h"
#include "test_character.h"

static void test_char_get_chunk_x (void);
static void test_char_get_chunk_y (void);
static void test_char_get_tile_x (void);
static void test_char_get_tile_y (void);
static void test_char_center_on_screen (void);
static void test_char_move_character (void);

void
test_character (void)
{
    printf("\n> Unit testing character functions...\n\n");
    test_char_get_chunk_x ();
    test_char_get_chunk_y ();
    test_char_get_tile_x ();
    test_char_get_tile_y ();
    test_char_center_on_screen ();
    test_char_move_character ();
}

static void
test_char_get_chunk_x (void)
{
    if (TILESIZE * TILESX != 0) {
        assert (eng_char_get_chunk_x (3 * TILESIZE * TILESX) == 3);
        assert (eng_char_get_chunk_x (- 2 * TILESIZE * TILESX) == -2);
        assert (eng_char_get_chunk_x (0) == 0);
    }
    else
        assert (eng_char_get_chunk_x (1092) == 0);
}

static void
test_char_get_chunk_y (void)
{
    if (TILESIZE * TILESY != 0) {
        assert (eng_char_get_chunk_y (-6 * TILESIZE * TILESY) == -6);
        assert (eng_char_get_chunk_y (7 * TILESIZE * TILESY) == 7);
        assert (eng_char_get_chunk_y (0) == 0);
    }
    else
        assert (eng_char_get_chunk_y (1092) == 0);
}

static void
test_char_get_tile_x (void)
{
    if (TILESIZE != 0) {
        assert (eng_char_get_tile_x (3 * TILESIZE * TILESX) == 0);

        if (TILESX > 0) {
#if TILESX > 1
            assert (eng_char_get_tile_x (7 * TILESIZE * TILESX + TILESIZE) ==
                    1);
#endif
            assert (eng_char_get_tile_x (-3 * TILESIZE * TILESX - 1) ==
                    TILESX - 1);
        }
    }
    else
        assert (eng_char_get_tile_x (102933) == 0);
}

static void
test_char_get_tile_y (void)
{
    if (TILESIZE != 0) {
        assert (eng_char_get_tile_y (3 * TILESIZE * TILESY) == 0);

        if (TILESY > 0) {
#if TILESY > 1
            assert (eng_char_get_tile_y (7 * TILESIZE * TILESY + TILESIZE) ==
                    1);
#endif
            assert (eng_char_get_tile_y (-3 * TILESIZE * TILESY - 1) ==
                    TILESY - 1);
        }
    }
    else
        assert (eng_char_get_tile_y (102933) == 0);
}

static void
test_char_center_on_screen (void)
{
    SDL_Window *window = SDL_CreateWindow ("", -200, -300, 200, 300,
                                           SDL_WINDOW_BORDERLESS);

    EngCharacter character = eng_char_create_character (0, 0, 0, 0, 50, 75,
                                                        50, 75, true);

    /* Regular test. */
    eng_char_center_on_screen (window, &character);
    assert (character.dst.x == (200 - character.dst.w) / 2);
    assert (character.dst.y == (300 - character.dst.h) / 2);

    /* Test with negative character destination. */
    SDL_SetWindowSize (window, 1, 1);
    eng_char_center_on_screen (window, &character);
    assert (character.dst.x == (1 - character.dst.w) / 2);
    assert (character.dst.y == (1 - character.dst.h) / 2);

    SDL_DestroyWindow (window);
}

static void
test_char_move_character (void)
{
    EngCharacter character = eng_char_create_character (0, 0, 0, 0, 0, 0,
                                                        0, 0, true);
    EngCollision collision = {true, true, true, true};
    character.collision = collision;

    /* Test for up and right movement when affected by collision. */
    eng_char_move_character(&character, 5, 5);
    assert (character.x == 0);
    assert (character.y == 0);

    /* Test for down and right movement when unaffected by collision. */
    character.collision.down = false;
    character.collision.right = false;
    eng_char_move_character (&character, 5, 5);
    assert (character.x == 5);
    assert (character.y == 5);

    /* Test for left and up movement when affected by collision. */
    eng_char_move_character (&character, -5, -5);
    assert (character.x == 5);
    assert (character.y == 5);

    /* Test for left and up movement when unaffected by collision. */
    character.collision.left = false;
    character.collision.up = false;
    eng_char_move_character (&character, -5, -5);
    assert (character.x == 0);
    assert (character.y == 0);

    /* Test when isAffectByCollision is turned off. */
    character.collision.down = true;
    character.collision.up = true;
    character.collision.right = true;
    character.collision.left = true;
    character.is_affected_by_collision = false;

    /* Right and down. */
    eng_char_move_character (&character, 5, 5);
    assert (character.x == 5);
    assert (character.y == 5);

    /* Left and up. */
    eng_char_move_character (&character, -5, -5);
    assert (character.x == 0);
    assert (character.y == 0);
}
