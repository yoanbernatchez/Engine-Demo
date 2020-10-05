/*
 * Author: YOAN BERNATCHEZ
 * Date: 2020-08-01
 *
 * This file provides the user with functions to create windows and add objects
 * to them. It also allows the user to update and copy windows to the renderer.
 * The main goal was to make the code portable to other SDL projects.
 */

/*
 * TODO: Create an error message system with __LINE__ and __FILE__ to remove
 *       the repetitive error checks.
 */

#include <stdio.h>
#include <stdlib.h>
#include <SDL_image.h>
#include "window.h"

/*--------------------------------------------------------------------------*/
/* Local function prototypes                                                */
/*--------------------------------------------------------------------------*/

/**
 * @brief Adds an object to a window (allocates memory & increases count).
 *
 * @param window: The window containing the array of objects.
 *
 * @sa windowRemoveObject()
 */
static void addObject(Window *window);

/**
 * @brief Updates the positions and size of the borders
 * according to the size of the window.
 *
 * @param window: The window containing the borders to update.
 */
static void updateBorders(Window *window);

/**
 * @brief Saves the size of an object before modification.
 *
 * @param window: The window containing the object.
 * @param index:  The index of the object we want to save the size of.
 */
static void saveObjectSize(Window *window, int index);

/**
 * @brief Sets the coordinates of a window's object (relative to the window).
 *
 * @param window: The window containing the object.
 * @param dst:    The destination coordinates of the object
 *                (relative to window).
 * @param index:  The index of the object we want to modify.
 */
static void assignObjectPosition(Window *window, int index, SDL_Rect dst);

/*--------------------------------------------------------------------------*/
/* Window function implementations                                          */
/*--------------------------------------------------------------------------*/

/* Safe way to create a window or HUD element. */
Window
windowCreateWindow(int x, int y, int w, int h, int borderSize)
{
    Window window;
    SDL_Rect nullRect = {0, 0, 0, 0};

    window.x = x;
    window.y = y;
    window.w = w;
    window.h = h;

    window.borderSize = borderSize;
    window.nbObjects = 0;
    window.selectedObject = 0;
    window.visible = true;

    for (int i = 0; i < 4; i++) {
        window.border[i].visible = true;
        window.border[i].src = nullRect;
        window.border[i].dst = nullRect;
    }

    /* Protection against negative sizes. */
    if (window.w < 0) window.w = 0;
    if (window.h < 0) window.h = 0;
    if (window.borderSize < 0) window.borderSize = 0;

    return window;
}

/* Makes an object in a window invisible. */
bool
windowHideObject(Window *window, int index)
{
    bool result;

    if (index < window->nbObjects && index >= 0) {
        window->object[index].visible = false;
        result = true;
    }
    else {
        printf("Index out of bounds in %s %d\n", __FILE__, __LINE__);
        result = false;
    }

    return result;
}

/* Makes an object in a window visible. */
bool
windowShowObject(Window *window, int index)
{
    bool result;

    if (index < window->nbObjects && index >= 0) {
        window->object[index].visible = true;
        result = true;
    }
    else {
        printf("Index out of bounds in %s %d\n", __FILE__, __LINE__);
        result = false;
    }

    return result;
}

/* Adds an outline to an object in a window. */
bool
windowAddObjectOutline(Window *window, int index, SDL_Color color,
                            int outlineSize)
{
    bool result;

    if (index < window->nbObjects && index >= 0) {
        windowShowObjectOutline(window, index);
        windowRecolorObjectOutline(window, index, color);
        windowResizeObjectOutline(window, index, outlineSize);
        result = true;
    }
    else {
        printf("Index out of bounds in %s %d\n", __FILE__, __LINE__);
        result = false;
    }

    return result;
}

/* Recolors an object's outline in a window. */
bool
windowRecolorObjectOutline(Window *window, int index, SDL_Color color)
{
    bool result;

    if (index < window->nbObjects && index >= 0) {
        window->object[index].outlineColor = color;
        result = true;
    }
    else {
        printf("Index out of bounds in %s %d\n", __FILE__, __LINE__);
        result = false;
    }

    return result;
}

/* Gives a new size to the outline an object has in a window. */
bool
windowResizeObjectOutline(Window *window, int index, int outlineSize)
{
    bool result;

    if (index < window->nbObjects && index >= 0) {
        window->object[index].outlineSize = outlineSize;

        window->object[index].outlineDst.x =
        window->object[index].dst.x - window->object[index].outlineSize;

        window->object[index].outlineDst.y =
        window->object[index].dst.y - window->object[index].outlineSize;

        window->object[index].outlineDst.w =
        window->object[index].dst.w + 2 * window->object[index].outlineSize;

        window->object[index].outlineDst.h =
        window->object[index].dst.h + 2 * window->object[index].outlineSize;

        if (window->object[index].outlineDst.w < 0) {
            window->object[index].outlineDst.w = 0;
        }

        if (window->object[index].outlineDst.h < 0) {
            window->object[index].outlineDst.h = 0;
        }

        result = true;
    }
    else {
        printf("Index out of bounds in %s %d\n", __FILE__, __LINE__);
        result = false;
    }

    return result;
}

/* Hides the outline of an object in a window. */
bool
windowHideObjectOutline(Window *window, int index)
{
    bool result;

    if (index < window->nbObjects && index >= 0) {
        window->object[index].outline = false;
        result = true;
    }
    else {
        printf("Index out of bounds in %s %d\n", __FILE__, __LINE__);
        result = false;
    }

    return result;
}

/* Makes the outline of an object in a window visible. */
bool
windowShowObjectOutline(Window *window, int index)
{
    bool result;

    if (index < window->nbObjects && index >= 0) {
        window->object[index].outline = true;
        result = true;
    }
    else {
        printf("Index out of bounds in %s %d\n", __FILE__, __LINE__);
        result = false;
    }

    return result;
}

/* Finds the nth object of the specified type and returns its index. */
int
windowGetObjectIndex(Window window, winObjType type, int position)
{
    int index = -1;
    int counter = 0;

    for (int i = 0; i < window.nbObjects; i++) {
        if (window.object[i].type == type && position == counter) {
            index = i;
            break;
        }
        else if (window.object[i].type == type && position != counter) {
            counter++;
        }
    }

    return index;
}

/*
 * Finds all the objects of a specified type in a window, counts them and
 * returns how many there are.
 */
int
windowGetNbObjectType(Window window, winObjType type)
{
    int counter = 0;

    for (int i = 0; i < window.nbObjects; i++) {
        if (window.object[i].type == type) {
            counter++;
        }
    }

    return counter;
}

/*
 * Modifies the size of an object by a factor, for instance, a factor of 2
 * doubles the size of the object.
 *
 * The reason why we pass the window instead of the object itself is to
 * check if the object at the specified index exists. Not checking if the
 * object exists might cause crashes if the index is out of bounds (there
 * might be a better way to check this?).
 */
bool
windowResizeObject(Window *window, int index, double factor)
{
    int wFactor;
    int hFactor;
    bool result;

    if (index < window->nbObjects && index >= 0) {
        wFactor = window->object[index].dst.w * factor;
        hFactor = window->object[index].dst.h * factor;

        window->object[index].dst.x -= (wFactor
                                        - window->object[index].dst.w) / 2;
        window->object[index].dst.y -= (hFactor
                                        - window->object[index].dst.h) / 2;

        window->object[index].dst.w = wFactor;
        window->object[index].dst.h = hFactor;

        /*
         * This is protection against negative width or height.
         * If wFactor or hFactor is zero, then the object becomes invisible
         * and any subsequent call of this function won't restore the width
         * or height value of the object to more than 0, no matter what the
         * factor is. At this point, you need to call windowResetObjectSize().
         */
        if (wFactor < 0 || hFactor < 0) {
            window->object[index].dst.x = 0;
            window->object[index].dst.y = 0;
            window->object[index].dst.w = 0;
            window->object[index].dst.h = 0;
        }

        result = true;
    }
    else {
        printf("Index out of bounds in %s %d\n", __FILE__, __LINE__);
        result = false;
    }

    return result;
}

/*
 * Sets the size of an object in a window to its previously saved size.
 *
 * The reason why we pass the window instead of the object itself is to
 * check if the object at the specified index exists. Not checking if the
 * object exists might cause crashes if the index is out of bounds (there
 * might be a better way to check this?).
 */
bool
windowResetObjectSize(Window *window, int index)
{
    int wDiff;
    int hDiff;
    bool result;

    if (index < window->nbObjects && index >= 0) {
        wDiff = window->object[index].dst.w
                - window->object[index].savedLength;
        hDiff = window->object[index].dst.h
                - window->object[index].savedHeight;

        window->object[index].dst.x += wDiff/2;
        window->object[index].dst.y += hDiff/2;

        window->object[index].dst.w = window->object[index].savedLength;
        window->object[index].dst.h = window->object[index].savedHeight;

        result = true;
    }
    else {
        printf("Index out of bounds in %s %d\n", __FILE__, __LINE__);
        result = false;
    }

    return result;
}

/*
 * Adds an object to a window (allocates memory, initializes objects
 * and increases count).
 */
static void
addObject(Window *window)
{
    if (window->nbObjects == 0) {
        window->object = (WinObject*) malloc(sizeof(WinObject));
    }
    else {
        window->object = (WinObject*)
        realloc(window->object, (window->nbObjects+1) * sizeof(WinObject));
    }

    SDL_Color nullColor = {0};
    SDL_Rect nullRect = {0};

    /* Initializing all members of object. */
    window->object[window->nbObjects].savedLength = 0;
    window->object[window->nbObjects].savedHeight = 0;
    window->object[window->nbObjects].type = NONE;
    window->object[window->nbObjects].visible = true;
    window->object[window->nbObjects].interactive = false;
    window->object[window->nbObjects].outline = false;
    window->object[window->nbObjects].outlineSize = 0;
    window->object[window->nbObjects].color = nullColor;
    window->object[window->nbObjects].outlineColor = nullColor;
    window->object[window->nbObjects].text = NULL;
    window->object[window->nbObjects].src = nullRect;
    window->object[window->nbObjects].dst = nullRect;
    window->object[window->nbObjects].outlineDst = nullRect;

    window->nbObjects += 1;
}

/* Removes an object from a window (reallocates memory & decreases count). */
bool
windowRemoveObject(Window *window, int position)
{
    bool result;

    if (window->nbObjects > 0 &&
        position < window->nbObjects &&
        position >= 0) {

        window->nbObjects -= 1;

        for (int j = position; j<window->nbObjects; j++) {
            window->object[j] = window->object[j+1];
        }

        if (window->nbObjects == 0) {
            free(window->object);
        }
        else {
            window->object = (WinObject*)
            realloc(window->object, (window->nbObjects) * sizeof(WinObject));
        }

        result = true;
    }
    else {
        printf("No object or index out of bounds in %s %d\n",
               __FILE__, __LINE__);
        result = false;
    }

    return result;
}

/* Takes a window in parameter and frees all the memory associated to it. */
void
windowDestroy(Window *window)
{
    /* Free all textures assigned. */
    for (int i = 0; i < window->nbObjects; i++) {
        if (window->object[i].text != NULL) {
            SDL_DestroyTexture(window->object[i].text);
        }
    }

    /* Then free objects. */
    if (window->nbObjects != 0) {
        window->nbObjects = 0;
        free(window->object);
    }
}

/* Creates a TTF texture from text. */
SDL_Texture*
createTextboxTexture(SDL_Renderer *renderer, char text[],
                                  TTF_Font *font, SDL_Color color, int length)
{
    SDL_Surface* surf = TTF_RenderText_Blended_Wrapped(font, text,
                                                       color, length);

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surf);

    SDL_FreeSurface(surf);

    return texture;
}

/*
 * Adds a rectangular background filled with a specified color as
 * an object to the window in parameters.
 */
void
windowAddBackground(Window *window, SDL_Color color, SDL_Rect dst)
{
    addObject(window);
    int index = window->nbObjects - 1;

    window->object[index].type = BACKGROUND;
    window->object[index].color = color;

    assignObjectPosition(window, index, dst);
    saveObjectSize(window, index);
}

/* Adds a text box as an object to the window in parameters. */
void
windowAddTextbox(Window *window, SDL_Texture* text, SDL_Rect dst)
{
    addObject(window);
    int index = window->nbObjects - 1;

    window->object[index].type = TEXTBOX;
    window->object[index].text = text;

    assignObjectPosition(window, index, dst);
    saveObjectSize(window, index);
}

/*
 * Changes the texture of a text box, it is useful for changing
 * the text (words) on screen on an already defined text box object.
 */
void
windowChangeTextboxText(Window *window, int index, SDL_Texture *text)
{
    if (index < window->nbObjects && index >= 0) {
        window->object[index].text = text;
    }
}

/* Adds an image as an object to the window in parameters. */
void
windowAddImage(Window *window, SDL_Rect src, SDL_Rect dst)
{
    addObject(window);
    int index = window->nbObjects - 1;

    window->object[index].type = IMAGE;
    window->object[index].src = src;

    assignObjectPosition(window, index, dst);
    saveObjectSize(window, index);
}

/*
 * Moves the specified window by a certain amount, also updates all the objects
 * and borders to move along with the window.
 */
void
windowMoveWindow(Window* window, int xAmount, int yAmount)
{
    /* Move coordinates of the window. */
    window->x += xAmount;
    window->y += yAmount;

    /* Adjust window borders depending on coordinates and size of window. */
    updateBorders(window);

    /* Move coordinates of the window's objects and their outlines. */
    for (int i = 0; i < window->nbObjects; i++) {
        window->object[i].dst.x += xAmount;
        window->object[i].dst.y += yAmount;

        if (window->object[i].outline) {
            window->object[i].outlineDst.x += xAmount;
            window->object[i].outlineDst.y += yAmount;
        }
    }
}

/* Sets the coordinates of a window's object (relative to the window). */
static void
assignObjectPosition(Window* window, int index, SDL_Rect dst)
{
    window->object[index].dst.x = window->x + window->borderSize + dst.x;
    window->object[index].dst.y = window->y + window->borderSize + dst.y;
    window->object[index].dst.w = dst.w;
    window->object[index].dst.h = dst.h;
}

/*
 * Saves the size of an object before modification so that we do not lose
 * its original size.
 */
static void
saveObjectSize(Window* window, int index)
{
    window->object[index].savedLength = window->object[index].dst.w;
    window->object[index].savedHeight = window->object[index].dst.h;
}

/*
 * Updates the positions and size of the borders
 * according to the size of the window.
 */
static void
updateBorders(Window* window)
{
    window->border[0].dst.x = window->x;
    window->border[0].dst.y = window->y;
    window->border[0].dst.w = window->borderSize;
    window->border[0].dst.h = window->h + window->borderSize*2;

    window->border[2].dst.x = window->x + window->w + window->border[0].dst.w;
    window->border[2].dst.y = window->y;
    window->border[2].dst.w = window->borderSize;
    window->border[2].dst.h = window->h + window->borderSize*2;

    window->border[1].dst.x = window->x + window->borderSize;
    window->border[1].dst.y = window->y;
    window->border[1].dst.w = window->w;
    window->border[1].dst.h = window->borderSize;

    window->border[3].dst.x = window->x + window->borderSize;
    window->border[3].dst.y = window->y + window->h + window->borderSize;
    window->border[3].dst.w = window->w;
    window->border[3].dst.h = window->borderSize;
}

/* Makes the window's borders invisible. */
void
windowHideBorders(Window* window)
{
    for (int i = 0; i < 4; i++) {
        window->border[i].visible = false;
    }
}

/* Makes the window's borders visible. */
void
windowShowBorders(Window* window)
{
    for (int i = 0; i < 4; i++) {
        window->border[i].visible = true;
    }
}

/* Pastes the window and its objects to the renderer. */
void
windowToRenderer(SDL_Renderer* renderer, SDL_Texture* hudText, Window window)
{
    for (int i = 0; i<window.nbObjects; i++) {
        /* Copy objects to renderer if they are set to be visible. */
        if (window.object[i].visible) {
            switch (window.object[i].type) {
                case TEXTBOX:
                    SDL_RenderCopy(renderer, window.object[i].text, NULL,
                                   &window.object[i].dst);
                    break;
                case IMAGE:
                    SDL_RenderCopy(renderer, hudText, &window.object[i].src,
                                   &window.object[i].dst);
                    break;
                case BACKGROUND:
                    SDL_SetRenderDrawColor(renderer,
                                           window.object[i].color.r,
                                           window.object[i].color.g,
                                           window.object[i].color.b,
                                           window.object[i].color.a);
                    SDL_RenderFillRect(renderer, &window.object[i].dst);
                    break;
                default:
                    break;
            }

            /* Copy object outlines to renderer. */
            if (window.object[i].outline) {
                SDL_SetRenderDrawColor(renderer,
                                       window.object[i].outlineColor.r,
                                       window.object[i].outlineColor.g,
                                       window.object[i].outlineColor.b,
                                       window.object[i].outlineColor.a);

                SDL_RenderFillRect(renderer, &window.object[i].outlineDst);
            }
        }
    }

    /* Copy borders to renderer. */
    for (int j = 0; j<4; j++) {
        if (window.border[j].visible == true) {
            SDL_RenderCopy(renderer, hudText, &window.border[j].src,
                           &window.border[j].dst);
        }
    }
}
