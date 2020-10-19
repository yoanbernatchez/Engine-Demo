#include <assert.h>
#include <stdio.h>
#include <SDL.h>
#include "test_hud.h"
#include "../HUD/hud.h"

static void test_hud_create_hud (void);
static void test_hud_hide_component (void);
static void test_hud_show_component (void);
static void test_hud_recolor_component_outline (void);
static void test_hud_resize_component_outline (void);
static void test_hud_hide_component_outline (void);
static void test_hud_show_component_outline (void);
static void test_hud_get_component_index (void);
static void test_hud_get_nb_component_type (void);
static void test_hud_resize_component (void);
static void test_hud_reset_component_size (void);
static void test_hud_remove_component (void);
static void test_hud_add_background (void);
static void test_hud_add_textbox (void);
static void test_hud_add_image (void);
static void test_hud_move_hud (void);
static void test_hud_hide_borders (void);
static void test_hud_show_borders (void);

/* All the unit tests for windows functions. */
void
test_hud (void)
{
    printf("\n> Unit testing hud functions...\n\n");
    test_hud_create_hud ();
    test_hud_hide_component ();
    test_hud_show_component ();
    test_hud_recolor_component_outline ();
    test_hud_resize_component_outline ();
    test_hud_hide_component_outline ();
    test_hud_show_component_outline ();
    test_hud_get_component_index ();
    test_hud_get_nb_component_type ();
    test_hud_resize_component ();
    test_hud_reset_component_size ();
    test_hud_remove_component ();
    test_hud_add_background ();
    test_hud_add_textbox ();
    test_hud_add_image ();
    test_hud_move_hud ();
    test_hud_hide_borders ();
    test_hud_show_borders ();
}

static void
test_hud_create_hud (void)
{
    /* Case 1: User inputs positive sizes. */
    EngHud hud = eng_hud_create_hud (2, 4, 6, 8, 10);

    /* Test for basic member initialization. */
    assert (hud.x == 2);
    assert (hud.y == 4);
    assert (hud.w == 6);
    assert (hud.h == 8);
    assert (hud.border_size == 10);

    /*
     * Could use a for loop here to check all four borders, but then we would
     * not know which border failed the test.
     */

    /* Test for 1st border initialization. */
    assert (hud.border[0].is_visible);
    assert (hud.border[0].opacity == 255);
    assert (hud.border[0].src.x == 0);
    assert (hud.border[0].src.y == 0);
    assert (hud.border[0].src.w == 0);
    assert (hud.border[0].src.h == 0);
    assert (hud.border[0].dst.x == 2);
    assert (hud.border[0].dst.y == 4);
    assert (hud.border[0].dst.w == 10);
    assert (hud.border[0].dst.h == 28);

    /* Test for 2nd border initialization. */
    assert (hud.border[1].is_visible);
    assert (hud.border[1].opacity == 255);
    assert (hud.border[1].src.x == 0);
    assert (hud.border[1].src.y == 0);
    assert (hud.border[1].src.w == 0);
    assert (hud.border[1].src.h == 0);
    assert (hud.border[1].dst.x == 12);
    assert (hud.border[1].dst.y == 4);
    assert (hud.border[1].dst.w == 6);
    assert (hud.border[1].dst.h == 10);

    /* Test for 3rd border initialization. */
    assert (hud.border[2].is_visible);
    assert (hud.border[2].opacity == 255);
    assert (hud.border[2].src.x == 0);
    assert (hud.border[2].src.y == 0);
    assert (hud.border[2].src.w == 0);
    assert (hud.border[2].src.h == 0);
    assert (hud.border[2].dst.x == 18);
    assert (hud.border[2].dst.y == 4);
    assert (hud.border[2].dst.w == 10);
    assert (hud.border[2].dst.h == 28);

    /* Test for 4th border initialization. */
    assert (hud.border[3].is_visible);
    assert (hud.border[3].opacity == 255);
    assert (hud.border[3].src.x == 0);
    assert (hud.border[3].src.y == 0);
    assert (hud.border[3].src.w == 0);
    assert (hud.border[3].src.h == 0);
    assert (hud.border[3].dst.x == 12);
    assert (hud.border[3].dst.y == 22);
    assert (hud.border[3].dst.w == 6);
    assert (hud.border[3].dst.h == 10);

    eng_hud_destroy (&hud);

    /* Case 2: User inputs negative sizes. */
    hud = eng_hud_create_hud (-2, -4, -6, -8, -10);

    assert (hud.x == -2);
    assert (hud.y == -4);
    assert (hud.w == 0);
    assert (hud.h == 0);
    assert (hud.border_size == 0);

    eng_hud_destroy (&hud);
}

static void
test_hud_hide_component (void)
{
    EngHud hud = eng_hud_create_hud (0, 0, 0, 0, 0);
    SDL_Rect dst = {0, 0, 0, 0};
    SDL_Color color = {0, 0, 0, 0};

    eng_hud_add_background (&hud, color, dst);
    hud.component[0].is_visible = true;

    /* Test index within bounds. */
    eng_hud_hide_component (&hud, 0);
    assert (!hud.component[0].is_visible);

    /* Test index out of bounds. */
    assert (!eng_hud_hide_component (&hud, 1));

    eng_hud_destroy (&hud);
}

static void
test_hud_show_component (void)
{
    EngHud hud = eng_hud_create_hud (0, 0, 0, 0, 0);
    SDL_Rect dst = {0, 0, 0, 0};
    SDL_Color color = {0, 0, 0, 0};

    eng_hud_add_background (&hud, color, dst);
    hud.component[0].is_visible = false;

    /* Test index within bounds. */
    eng_hud_show_component (&hud, 0);
    assert (hud.component[0].is_visible);

    /* Test index out of bounds. */
    assert (!eng_hud_show_component (&hud, 1));

    eng_hud_destroy (&hud);
}

static void
test_hud_recolor_component_outline (void)
{
    EngHud hud = eng_hud_create_hud (0, 0, 0, 0, 0);
    SDL_Rect dst = {0, 0, 0, 0};
    SDL_Color color = {100, 50, 65, 255};

    eng_hud_add_background (&hud, color, dst);

    /* Test with index within bounds. */
    eng_hud_recolor_component_outline (&hud, 0, color);
    assert (hud.component[0].outline_color.r == 100);
    assert (hud.component[0].outline_color.g == 50);
    assert (hud.component[0].outline_color.b == 65);
    assert (hud.component[0].outline_color.a == 255);

    /* Test with index out of bounds. */
    assert (!eng_hud_recolor_component_outline (&hud, 1, color));

    eng_hud_destroy (&hud);
}

static void
test_hud_resize_component_outline (void)
{
    EngHud hud = eng_hud_create_hud (0, 0, 0, 0, 0);
    SDL_Rect dst = {50, -40, 100, 200};
    SDL_Color color = {100, 50, 65, 255};

    eng_hud_add_background (&hud, color, dst);

    /* Case where the outline size is positive. */
    eng_hud_resize_component_outline (&hud, 0, 12);
    assert (hud.component[0].outline_dst.x == 38);
    assert (hud.component[0].outline_dst.y == -52);
    assert (hud.component[0].outline_dst.w == 124);
    assert (hud.component[0].outline_dst.h == 224);
    assert (hud.component[0].outline_size == 12);

    /* Case where the outline size is negative. */
    eng_hud_resize_component_outline (&hud, 0, -12);
    assert (hud.component[0].outline_dst.x == 62);
    assert (hud.component[0].outline_dst.y == -28);
    assert (hud.component[0].outline_dst.w == 76);
    assert (hud.component[0].outline_dst.h == 176);
    assert (hud.component[0].outline_size == -12);

    /* Case where w and h would be negative. */
    eng_hud_resize_component_outline (&hud, 0, -500);
    assert (hud.component[0].outline_dst.x == 550);
    assert (hud.component[0].outline_dst.y == 460);
    assert (hud.component[0].outline_dst.w == 0);
    assert (hud.component[0].outline_dst.h == 0);
    assert (hud.component[0].outline_size == -500);

    /* Case where index if out of bounds. */
    assert (!eng_hud_resize_component_outline(&hud, 1, 0));

    eng_hud_destroy (&hud);
}

static void
test_hud_hide_component_outline (void)
{
    EngHud hud = eng_hud_create_hud (0, 0, 0, 0, 0);
    SDL_Rect dst = {0, 0, 0, 0};
    SDL_Color color = {100, 50, 65, 255};

    eng_hud_add_background (&hud, color, dst);
    hud.component[0].has_outline = true;

    /* Test case where index is valid. */
    eng_hud_hide_component_outline (&hud, 0);
    assert (!hud.component[0].has_outline);

    /* Test case where index is out of bounds. */
    assert (!eng_hud_hide_component_outline (&hud, 2));

    eng_hud_destroy (&hud);
}

static void
test_hud_show_component_outline (void)
{
    EngHud hud = eng_hud_create_hud (0, 0, 0, 0, 0);
    SDL_Rect dst = {0, 0, 0, 0};
    SDL_Color color = {100, 50, 65, 255};

    eng_hud_add_background (&hud, color, dst);
    hud.component[0].has_outline = false;

    /* Test case where index is valid. */
    eng_hud_show_component_outline (&hud, 0);
    assert (hud.component[0].has_outline);

    /* Test case where index is out of bounds. */
    assert (!eng_hud_show_component_outline (&hud, 2));

    eng_hud_destroy (&hud);
}

static void
test_hud_get_component_index (void)
{
    int index = 0;

    EngHud hud = eng_hud_create_hud (0, 0, 0, 0, 0);
    SDL_Rect dst = {0, 0, 0, 0};
    SDL_Color color = {100, 50, 65, 255};

    /* Case where we do not find requested object. */
    index = eng_hud_get_component_index (hud, ENG_BACKGROUND, 4);
    assert (index == -1);

    /* Case where there is more than one of the same object. */
    eng_hud_add_background (&hud, color, dst);
    eng_hud_add_image (&hud, dst, dst);
    eng_hud_add_background (&hud, color, dst);
    index = eng_hud_get_component_index (hud, ENG_BACKGROUND, 1);
    assert (index == 2);

    /* Case where there is only one of a specified object. */
    index = eng_hud_get_component_index (hud, ENG_IMAGE, 0);
    assert (index == 1);

    eng_hud_destroy (&hud);
}

static void
test_hud_get_nb_component_type (void)
{
    int nb_objects = 0;

    EngHud hud = eng_hud_create_hud (0, 0, 0, 0, 0);
    SDL_Rect dst = {0, 0, 0, 0};
    SDL_Color color = {100, 50, 65, 255};

    nb_objects = eng_hud_get_nb_component_type (hud, ENG_BACKGROUND);

    /* Testing case where there is no object of the specified type. */
    assert (nb_objects == 0);

    /* Add three window background objects. */
    for (int i = 0; i < 3; i++)
        eng_hud_add_background (&hud, color, dst);

    nb_objects = eng_hud_get_nb_component_type (hud, ENG_BACKGROUND);

    /* Test case where there is objects of the specified type. */
    assert (nb_objects == 3);

    eng_hud_destroy (&hud);
}

static void
test_hud_resize_component (void)
{
    EngHud hud = eng_hud_create_hud (0, 0, 0, 0, 0);
    SDL_Rect dst = {50, 50, 100, 200};
    SDL_Color color = {100, 50, 65, 255};

    eng_hud_add_background (&hud, color, dst);

    /* Positive case. */
    eng_hud_resize_component (&hud, 0, 2);
    assert (hud.component[0].dst.x == 0);
    assert (hud.component[0].dst.y == -50);
    assert (hud.component[0].dst.w == 200);
    assert (hud.component[0].dst.h == 400);

    /* Negative case. */
    eng_hud_resize_component (&hud, 0, -1);
    assert (hud.component[0].dst.x == 0);
    assert (hud.component[0].dst.y == 0);
    assert (hud.component[0].dst.w == 0);
    assert (hud.component[0].dst.h == 0);

    /* Zero case. */
    hud.component[0].dst = dst;
    eng_hud_resize_component (&hud, 0, 0);
    assert (hud.component[0].dst.x == 100);
    assert (hud.component[0].dst.y == 150);
    assert (hud.component[0].dst.w == 0);
    assert (hud.component[0].dst.h == 0);

    eng_hud_destroy (&hud);
}

static void
test_hud_reset_component_size (void)
{
    EngHud hud = eng_hud_create_hud (0, 0, 0, 0, 0);
    SDL_Rect dst = {50, 50, 100, 200};
    SDL_Color color = {100, 50, 65, 255};

    eng_hud_add_background (&hud, color, dst);

    /* Test index is within bounds. */
    assert (eng_hud_resize_component (&hud, 0, 2));

    eng_hud_reset_component_size (&hud, 0);

    assert (hud.component[0].dst.x == 50);
    assert (hud.component[0].dst.y == 50);
    assert (hud.component[0].dst.w == 100);
    assert (hud.component[0].dst.h == 200);

    /* Test index is out of bounds. */
    assert (!eng_hud_resize_component (&hud, 1, 0));

    eng_hud_destroy (&hud);
}

static void
test_hud_remove_component (void)
{
    EngHud hud = eng_hud_create_hud (0, 0, 0, 0, 0);
    SDL_Rect dst = {50, 50, 100, 200};
    SDL_Color color = {100, 50, 65, 255};

    eng_hud_add_background (&hud, color, dst);
    eng_hud_add_background (&hud, color, dst);

    /* Test when there is objects to remove. */
    assert (eng_hud_remove_component (&hud, 0));
    assert (hud.nb_components == 1);

    /* Test when there is no object to remove. */
    eng_hud_remove_component (&hud, 0);
    assert (!eng_hud_remove_component (&hud, 0));
    assert (hud.nb_components == 0);

    /* Test user inputted an index out of bounds. */
    assert (!eng_hud_remove_component (&hud, 6));
    assert (hud.nb_components == 0);

    eng_hud_destroy (&hud);
}

static void
test_hud_add_background (void)
{
    EngHud hud = eng_hud_create_hud (50, -50, 200, 200, 0);
    SDL_Rect dst = {50, 50, 100, 200};
    SDL_Color color = {100, 50, 65, 255};

    eng_hud_add_background (&hud, color, dst);

    assert (hud.nb_components == 1);
    assert (hud.component[0].type == ENG_BACKGROUND);
    assert (hud.component[0].color.r == color.r);
    assert (hud.component[0].color.g == color.g);
    assert (hud.component[0].color.b == color.b);
    assert (hud.component[0].color.a == color.a);
    assert (hud.component[0].dst.x == 100);
    assert (hud.component[0].dst.y == 0);
    assert (hud.component[0].dst.w == dst.w);
    assert (hud.component[0].dst.h == dst.h);

    eng_hud_destroy (&hud);
}

static void
test_hud_add_textbox (void)
{
    EngHud hud = eng_hud_create_hud (50, -50, 200, 200, 0);
    SDL_Rect dst = {50, 50, 100, 200};

    eng_hud_add_textbox (&hud, NULL, dst);

    /* TODO: Find a way to check if the texture is not NULL here. */
    assert (hud.nb_components == 1);
    assert (hud.component[0].type == ENG_TEXTBOX);
    assert (hud.component[0].dst.x == 100);
    assert (hud.component[0].dst.y == 0);
    assert (hud.component[0].dst.w == dst.w);
    assert (hud.component[0].dst.h == dst.h);

    eng_hud_destroy (&hud);
}

static void
test_hud_add_image (void)
{
    EngHud hud = eng_hud_create_hud (50, -50, 200, 200, 0);
    SDL_Rect dst = {50, 50, 100, 200};

    eng_hud_add_image (&hud, dst, dst);

    assert (hud.nb_components == 1);
    assert (hud.component[0].type == ENG_IMAGE);
    assert (hud.component[0].dst.x == 100);
    assert (hud.component[0].dst.y == 0);
    assert (hud.component[0].dst.w == dst.w);
    assert (hud.component[0].dst.h == dst.h);

    eng_hud_destroy (&hud);
}

static void
test_hud_move_hud( void)
{
    EngHud hud = eng_hud_create_hud (0, 0, 200, 200, 0);

    /* Test with positive displacement values. */
    eng_hud_move_hud (&hud, 12, 12);
    assert (hud.x == 12);
    assert (hud.y == 12);

    /* Test with negative and zero displacement values. */
    eng_hud_move_hud (&hud, -24, 0);
    assert (hud.x == -12);
    assert (hud.y == 12);

    eng_hud_destroy (&hud);
}

static void
test_hud_hide_borders (void)
{
    EngHud hud = eng_hud_create_hud (0, 0, 200, 200, 0);

    for (int i = 0; i < 4; i++)
        hud.border[i].is_visible = true;

    eng_hud_hide_borders (&hud);

    assert (!hud.border[0].is_visible);
    assert (!hud.border[1].is_visible);
    assert (!hud.border[2].is_visible);
    assert (!hud.border[3].is_visible);

    eng_hud_destroy (&hud);
}

static void
test_hud_show_borders (void)
{
    EngHud hud = eng_hud_create_hud (0, 0, 200, 200, 0);

    for (int i = 0; i < 4; i++)
        hud.border[i].is_visible = false;

    eng_hud_show_borders (&hud);

    assert (hud.border[0].is_visible);
    assert (hud.border[1].is_visible);
    assert (hud.border[2].is_visible);
    assert (hud.border[3].is_visible);

    eng_hud_destroy (&hud);
}
