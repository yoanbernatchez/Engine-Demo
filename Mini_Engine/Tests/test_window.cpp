#include <assert.h>
#include <SDL.h>
#include "test_window.h"
#include "../HUD/window.h"

static void testWindowCreateWindow(void);
static void testWindowHideObject(void);
static void testWindowShowObject(void);
static void testWindowRecolorObjectOutline(void);
static void testWindowResizeObjectOutline(void);
static void testWindowHideObjectOutline(void);
static void testWindowShowObjectOutline(void);
static void testWindowObjectIndex(void);
static void testWindowGetNbObjectType(void);
static void testWindowResizeObject(void);
static void testWindowResetObjectSize(void);
static void testWindowRemoveObject(void);
static void testWindowAddBackground(void);
static void testWindowAddTextbox(void);
static void testWindowAddImage(void);
static void testWindowMoveWindow(void);
static void testWindowHideBorders(void);
static void testWindowShowBorders(void);

/* All the unit tests for windows functions. */
void
testWindow(void)
{
    testWindowCreateWindow();
    testWindowHideObject();
    testWindowShowObject();
    testWindowRecolorObjectOutline();
    testWindowResizeObjectOutline();
    testWindowHideObjectOutline();
    testWindowShowObjectOutline();
    testWindowObjectIndex();
    testWindowGetNbObjectType();
    testWindowResizeObject();
    testWindowResetObjectSize();
    testWindowRemoveObject();
    testWindowAddBackground();
    testWindowAddTextbox();
    testWindowAddImage();
    testWindowMoveWindow();
    testWindowHideBorders();
    testWindowShowBorders();
}

static void
testWindowCreateWindow(void)
{
    /* Case 1: User inputs positive sizes. */
    Window window = windowCreateWindow(2, 4, 6, 8, 10);

    /* Test for basic member initialization. */
    assert(window.x == 2);
    assert(window.y == 4);
    assert(window.w == 6);
    assert(window.h == 8);
    assert(window.borderSize == 10);

    /*
     * Could use a for loop here to check all four borders, but then we would
     * not know which border failed the test.
     */

    /* Test for 1st border initialization. */
    assert(window.border[0].visible);
    assert(window.border[0].src.x == 0);
    assert(window.border[0].src.y == 0);
    assert(window.border[0].src.w == 0);
    assert(window.border[0].src.h == 0);
    assert(window.border[0].dst.x == 0);
    assert(window.border[0].dst.y == 0);
    assert(window.border[0].dst.w == 0);
    assert(window.border[0].dst.h == 0);

    /* Test for 2nd border initialization. */
    assert(window.border[1].visible);
    assert(window.border[1].src.x == 0);
    assert(window.border[1].src.y == 0);
    assert(window.border[1].src.w == 0);
    assert(window.border[1].src.h == 0);
    assert(window.border[1].dst.x == 0);
    assert(window.border[1].dst.y == 0);
    assert(window.border[1].dst.w == 0);
    assert(window.border[1].dst.h == 0);

    /* Test for 3rd border initialization. */
    assert(window.border[2].visible);
    assert(window.border[2].src.x == 0);
    assert(window.border[2].src.y == 0);
    assert(window.border[2].src.w == 0);
    assert(window.border[2].src.h == 0);
    assert(window.border[2].dst.x == 0);
    assert(window.border[2].dst.y == 0);
    assert(window.border[2].dst.w == 0);
    assert(window.border[2].dst.h == 0);

    /* Test for 4th border initialization. */
    assert(window.border[3].visible);
    assert(window.border[3].src.x == 0);
    assert(window.border[3].src.y == 0);
    assert(window.border[3].src.w == 0);
    assert(window.border[3].src.h == 0);
    assert(window.border[3].dst.x == 0);
    assert(window.border[3].dst.y == 0);
    assert(window.border[3].dst.w == 0);
    assert(window.border[3].dst.h == 0);

    windowDestroy(&window);

    /* Case 2: User inputs negative sizes. */
    window = windowCreateWindow(-2, -4, -6, -8, -10);

    assert(window.x == -2);
    assert(window.y == -4);
    assert(window.w == 0);
    assert(window.h == 0);
    assert(window.borderSize == 0);

    windowDestroy(&window);
}

static void
testWindowHideObject(void)
{
    Window window = windowCreateWindow(0, 0, 0, 0, 0);
    SDL_Rect dst = {0, 0, 0, 0};
    SDL_Color color = {0, 0, 0, 0};

    windowAddBackground(&window, color, dst);
    window.object[0].visible = true;

    /* Test index within bounds. */
    windowHideObject(&window, 0);
    assert(!window.object[0].visible);

    /* Test index out of bounds. */
    assert(!windowHideObject(&window, 1));

    windowDestroy(&window);
}

static void
testWindowShowObject(void)
{
    Window window = windowCreateWindow(0, 0, 0, 0, 0);
    SDL_Rect dst = {0, 0, 0, 0};
    SDL_Color color = {0, 0, 0, 0};

    windowAddBackground(&window, color, dst);
    window.object[0].visible = false;

    /* Test index within bounds. */
    windowShowObject(&window, 0);
    assert(window.object[0].visible);

    /* Test index out of bounds. */
    assert(!windowShowObject(&window, 1));

    windowDestroy(&window);
}

static void
testWindowRecolorObjectOutline(void)
{
    Window window = windowCreateWindow(0, 0, 0, 0, 0);
    SDL_Rect dst = {0, 0, 0, 0};
    SDL_Color color = {100, 50, 65, 255};

    windowAddBackground(&window, color, dst);

    /* Test with index within bounds. */
    windowRecolorObjectOutline(&window, 0, color);
    assert(window.object[0].outlineColor.r == 100);
    assert(window.object[0].outlineColor.g == 50);
    assert(window.object[0].outlineColor.b == 65);
    assert(window.object[0].outlineColor.a == 255);

    /* Test with index out of bounds. */
    assert(!windowRecolorObjectOutline(&window, 1, color));

    windowDestroy(&window);
}

static void
testWindowResizeObjectOutline(void)
{
    Window window = windowCreateWindow(0, 0, 0, 0, 0);
    SDL_Rect dst = {50, -40, 100, 200};
    SDL_Color color = {100, 50, 65, 255};

    windowAddBackground(&window, color, dst);

    /* Case where the outline size is positive. */
    windowResizeObjectOutline(&window, 0, 12);
    assert(window.object[0].outlineDst.x == 38);
    assert(window.object[0].outlineDst.y == -52);
    assert(window.object[0].outlineDst.w == 124);
    assert(window.object[0].outlineDst.h == 224);
    assert(window.object[0].outlineSize == 12);

    /* Case where the outline size is negative. */
    windowResizeObjectOutline(&window, 0, -12);
    assert(window.object[0].outlineDst.x == 62);
    assert(window.object[0].outlineDst.y == -28);
    assert(window.object[0].outlineDst.w == 76);
    assert(window.object[0].outlineDst.h == 176);
    assert(window.object[0].outlineSize == -12);

    /* Case where w and h would be negative. */
    windowResizeObjectOutline(&window, 0, -500);
    assert(window.object[0].outlineDst.x == 550);
    assert(window.object[0].outlineDst.y == 460);
    assert(window.object[0].outlineDst.w == 0);
    assert(window.object[0].outlineDst.h == 0);
    assert(window.object[0].outlineSize == -500);

    /* Case where index if out of bounds. */
    assert(!windowResizeObjectOutline(&window, 1, 0));

    windowDestroy(&window);
}

static void
testWindowHideObjectOutline(void)
{
    Window window = windowCreateWindow(0, 0, 0, 0, 0);
    SDL_Rect dst = {0, 0, 0, 0};
    SDL_Color color = {100, 50, 65, 255};

    windowAddBackground(&window, color, dst);
    window.object[0].outline = true;

    /* Test case where index is valid. */
    windowHideObjectOutline(&window, 0);
    assert(!window.object[0].outline);

    /* Test case where index is out of bounds. */
    assert(!windowHideObjectOutline(&window, 2));

    windowDestroy(&window);
}

static void
testWindowShowObjectOutline(void)
{
    Window window = windowCreateWindow(0, 0, 0, 0, 0);
    SDL_Rect dst = {0, 0, 0, 0};
    SDL_Color color = {100, 50, 65, 255};

    windowAddBackground(&window, color, dst);
    window.object[0].outline = false;

    /* Test case where index is valid. */
    windowShowObjectOutline(&window, 0);
    assert(window.object[0].outline);

    /* Test case where index is out of bounds. */
    assert(!windowShowObjectOutline(&window, 2));

    windowDestroy(&window);
}

static void
testWindowObjectIndex(void)
{
    int index = 0;

    Window window = windowCreateWindow(0, 0, 0, 0, 0);
    SDL_Rect dst = {0, 0, 0, 0};
    SDL_Color color = {100, 50, 65, 255};

    /* Case where we do not find requested object. */
    index = windowGetObjectIndex(window, BACKGROUND, 4);
    assert(index == -1);

    /* Case where there is more than one of the same object. */
    windowAddBackground(&window, color, dst);
    windowAddImage(&window, dst, dst);
    windowAddBackground(&window, color, dst);
    index = windowGetObjectIndex(window, BACKGROUND, 1);
    assert(index == 2);

    /* Case where there is only one of a specified object. */
    index = windowGetObjectIndex(window, IMAGE, 0);
    assert(index == 1);

    windowDestroy(&window);
}

static void
testWindowGetNbObjectType(void)
{
    int nbObjects = 0;

    Window window = windowCreateWindow(0, 0, 0, 0, 0);
    SDL_Rect dst = {0, 0, 0, 0};
    SDL_Color color = {100, 50, 65, 255};

    nbObjects = windowGetNbObjectType(window, BACKGROUND);

    /* Testing case where there is no object of the specified type. */
    assert(nbObjects == 0);

    /* Add three window background objects. */
    for (int i = 0; i < 3; i++) {
        windowAddBackground(&window, color, dst);
    }

    nbObjects = windowGetNbObjectType(window, BACKGROUND);

    /* Test case where there is objects of the specified type. */
    assert(nbObjects == 3);

    windowDestroy(&window);
}

static void
testWindowResizeObject(void)
{
    Window window = windowCreateWindow(0, 0, 0, 0, 0);
    SDL_Rect dst = {50, 50, 100, 200};
    SDL_Color color = {100, 50, 65, 255};

    windowAddBackground(&window, color, dst);

    /* Positive case. */
    windowResizeObject(&window, 0, 2);
    assert(window.object[0].dst.x == 0);
    assert(window.object[0].dst.y == -50);
    assert(window.object[0].dst.w == 200);
    assert(window.object[0].dst.h == 400);

    /* Negative case. */
    windowResizeObject(&window, 0, -1);
    assert(window.object[0].dst.x == 0);
    assert(window.object[0].dst.y == 0);
    assert(window.object[0].dst.w == 0);
    assert(window.object[0].dst.h == 0);

    /* Zero case. */
    window.object[0].dst = dst;
    windowResizeObject(&window, 0, 0);
    assert(window.object[0].dst.x == 100);
    assert(window.object[0].dst.y == 150);
    assert(window.object[0].dst.w == 0);
    assert(window.object[0].dst.h == 0);

    windowDestroy(&window);
}

static void
testWindowResetObjectSize(void)
{
    Window window = windowCreateWindow(0, 0, 0, 0, 0);
    SDL_Rect dst = {50, 50, 100, 200};
    SDL_Color color = {100, 50, 65, 255};

    windowAddBackground(&window, color, dst);

    /* Test index is within bounds. */
    assert(windowResizeObject(&window, 0, 2));

    windowResetObjectSize(&window, 0);

    assert(window.object[0].dst.x == 50);
    assert(window.object[0].dst.y == 50);
    assert(window.object[0].dst.w == 100);
    assert(window.object[0].dst.h == 200);

    /* Test index is out of bounds. */
    assert(!windowResizeObject(&window, 1, 0));

    windowDestroy(&window);
}

static void
testWindowRemoveObject(void)
{
    Window window = windowCreateWindow(0, 0, 0, 0, 0);
    SDL_Rect dst = {50, 50, 100, 200};
    SDL_Color color = {100, 50, 65, 255};

    windowAddBackground(&window, color, dst);
    windowAddBackground(&window, color, dst);

    /* Test when there is objects to remove. */
    assert(windowRemoveObject(&window, 0));
    assert(window.nbObjects == 1);

    /* Test when there is no object to remove. */
    windowRemoveObject(&window, 0);
    assert(!windowRemoveObject(&window, 0));
    assert(window.nbObjects == 0);

    /* Test user inputted an index out of bounds. */
    assert(!windowRemoveObject(&window, 6));
    assert(window.nbObjects == 0);

    windowDestroy(&window);
}

static void
testWindowAddBackground(void)
{
    Window window = windowCreateWindow(50, -50, 200, 200, 0);
    SDL_Rect dst = {50, 50, 100, 200};
    SDL_Color color = {100, 50, 65, 255};

    windowAddBackground(&window, color, dst);

    assert(window.nbObjects == 1);
    assert(window.object[0].type == BACKGROUND);
    assert(window.object[0].color.r == color.r);
    assert(window.object[0].color.g == color.g);
    assert(window.object[0].color.b == color.b);
    assert(window.object[0].color.a == color.a);
    assert(window.object[0].dst.x == 100);
    assert(window.object[0].dst.y == 0);
    assert(window.object[0].dst.w == dst.w);
    assert(window.object[0].dst.h == dst.h);

    windowDestroy(&window);
}

static void
testWindowAddTextbox(void)
{
    Window window = windowCreateWindow(50, -50, 200, 200, 0);
    SDL_Rect dst = {50, 50, 100, 200};

    windowAddTextbox(&window, NULL, dst);

    /* TODO: Find a way to check if the texture is not NULL here. */
    assert(window.nbObjects == 1);
    assert(window.object[0].type == TEXTBOX);
    assert(window.object[0].dst.x == 100);
    assert(window.object[0].dst.y == 0);
    assert(window.object[0].dst.w == dst.w);
    assert(window.object[0].dst.h == dst.h);

    windowDestroy(&window);
}

static void
testWindowAddImage(void)
{
    Window window = windowCreateWindow(50, -50, 200, 200, 0);
    SDL_Rect dst = {50, 50, 100, 200};

    windowAddImage(&window, dst, dst);

    assert(window.nbObjects == 1);
    assert(window.object[0].type == IMAGE);
    assert(window.object[0].dst.x == 100);
    assert(window.object[0].dst.y == 0);
    assert(window.object[0].dst.w == dst.w);
    assert(window.object[0].dst.h == dst.h);

    windowDestroy(&window);
}

static void
testWindowMoveWindow(void)
{
    Window window = windowCreateWindow(0, 0, 200, 200, 0);

    /* Test with positive displacement values. */
    windowMoveWindow(&window, 12, 12);
    assert(window.x == 12);
    assert(window.y == 12);

    /* Test with negative and zero displacement values. */
    windowMoveWindow(&window, -24, 0);
    assert(window.x == -12);
    assert(window.y == 12);

    windowDestroy(&window);
}

static void
testWindowHideBorders(void)
{
    Window window = windowCreateWindow(0, 0, 200, 200, 0);

    for (int i = 0; i < 4; i++) {
        window.border[i].visible = true;
    }

    windowHideBorders(&window);

    assert(!window.border[0].visible);
    assert(!window.border[1].visible);
    assert(!window.border[2].visible);
    assert(!window.border[3].visible);

    windowDestroy(&window);
}

static void
testWindowShowBorders(void)
{
    Window window = windowCreateWindow(0, 0, 200, 200, 0);

    for (int i = 0; i < 4; i++) {
        window.border[i].visible = false;
    }

    windowShowBorders(&window);

    assert(window.border[0].visible);
    assert(window.border[1].visible);
    assert(window.border[2].visible);
    assert(window.border[3].visible);

    windowDestroy(&window);
}
