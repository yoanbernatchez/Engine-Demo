#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED

#include <stdbool.h>
#include <SDL.h>
#include <SDL_ttf.h>

/** Window object types. */
enum winObjType {NONE, TEXTBOX, IMAGE, BACKGROUND};

typedef struct
{
    bool visible;

    SDL_Rect src;
    SDL_Rect dst;
} WinBorder;
/**< Window border structure containing coordinates and visibility toggle. */

typedef struct
{
    int savedLength;
    int savedHeight;
    winObjType type;
    bool visible;
    bool interactive;
    bool outline;
    int outlineSize;

    SDL_Color color;
    SDL_Color outlineColor;

    SDL_Texture* text;

    SDL_Rect src;
    SDL_Rect dst;
    SDL_Rect outlineDst;
} WinObject;
/**< Window object structure containing size, color and other info. */

typedef struct
{
    int x;    /* Position of window (relative to game window). */
    int y;
    int w;    /* Width and Length of the window (inside the borders). */
    int h;

    int borderSize;
    int nbObjects;
    int selectedObject;    /* Currently selected interactive object's index. */
    bool visible;

    WinBorder border[4];
    WinObject *object;
} Window;
/**< Window structure containing coordinates, window object and border info. */

/**
 * @brief Initializes all the elements in a window structure. Use this function
 *        to safely create a HUD window.
 *
 * @param x:          Position in x of the window.
 * @param y:          Position in y of the window.
 * @param w:          Width of the window.
 * @param h:          Height of the window.
 * @param borderSize: Border size of the window.
 *
 * @return An initialized window structure.
 */
Window windowCreateWindow(int x, int y, int w, int h, int borderSize);

/**
 * @brief Removes an object from a window (reallocates memory
 *        & decreases count).
 *
 * @param window: The window containing the array of objects.
 * @param position: The index of the object to remove.
 *
 * @return False if object could not be removed or if there was no objects,
 *         true if execution was successful.
 */
bool windowRemoveObject(Window* window, int position);

/**
 * @brief Makes an object in a window invisible.
 *
 * @param window: The window containing the object to hide.
 * @param index:  Index that determines which object to hide from the
 *                array of objects.
 *
 * @return False if index is out of bounds, true if execution was successful.
 *
 * @sa windowShowObject()
 */
bool windowHideObject(Window* window, int index);

/**
 * @brief Makes an object in a window visible.
 *
 * @param window: The window containing the object to make visible.
 * @param index:  Index that determines which object to make visible from
 *                the array of objects.
 *
 * @return False if index is out of bounds, true if execution was successful.
 *
 * @sa windowHideObject()
 */
bool windowShowObject(Window* window, int index);

/**
 * @brief Modifies the size of an object by a factor.
 *
 * @param window: Window containing the object to resize.
 * @param index: Index of the object to resize in the window's object array.
 * @param factor: Determines how much to multiply the size of the object by.
 *
 * @return False if index out of bounds, true if execution was successful.
 */
bool windowResizeObject(Window *window, int index, double factor);

/**
 * @brief Sets the size of an object in a window to its previously saved size.
 *
 * @param window: Window containing the object to resize.
 * @param index: Index of the object to resize in the window's object array.
 *
 * @return False if index out of bounds, true if execution was successful.
 */
bool windowResetObjectSize(Window *window, int index);

/**
 * @brief Makes the window's borders invisible.
 *
 * @param window: The window containing the borders to hide.
 *
 * @sa windowShowBorders()
 */
void windowHideBorders(Window* window);

/**
 * @brief Makes the window's borders visible.
 *
 * @param window: The window containing the borders to make visible.
 *
 * @sa windowHideBorders()
 */
void windowShowBorders(Window* window);

/**
 * @brief Adds a rectangular background as an object to the window
 *        in parameters.
 *
 * @param window: The window we are adding the object to.
 * @param color:  The color of the rectangle.
 * @param dst:    The destination of the object (relative to the window).
 */
void windowAddBackground(Window* window, SDL_Color color, SDL_Rect dst);

/**
 * @brief Adds an image as an object to the window in parameters.
 *
 * @param window: The window we are adding the object to.
 * @param src:    The source coordinates of the object on the HUD sprite sheet.
 * @param dst:    The destination coordinates of the object
 *                (relative to the window).
 */
void windowAddImage(Window* window, SDL_Rect src, SDL_Rect dst);

/**
 * @brief Adds a text box as an object to the window in parameters.
 *
 * @param window: The window we are adding the object to.
 * @param text:   The texture containing the words.
 * @param dst:    The destination coordinates of the object
 *                (relative to the window).
 */
void windowAddTextbox(Window* window, SDL_Texture* text, SDL_Rect dst);

/**
 * @brief Creates a TTF texture from text.
 *
 * @param renderer: Renderer
 * @param text:     Text to make a texture of.
 * @param font:     Font of the text.
 * @param color:    Color of the font.
 * @param length:   Length of the wrapper for the text.
 *
 * @return The texture created.
 */
SDL_Texture* createTextboxTexture(SDL_Renderer* renderer, char text[],
                                  TTF_Font* font, SDL_Color color, int length);

/**
 * @brief Changes the texture of a text box.
 *
 * @param window: The window we are modifying objects from.
 * @param index:  The index of the object to modify.
 * @param text:   The new texture containing the new words.
 */
void windowChangeTextboxText(Window* window, int index, SDL_Texture* text);

/**
 * @brief Adds an outline to an object in a window.
 *
 * @param window:      The window containing the object to add an outline to.
 * @param index:       Index that determines which object to add an outline to.
 * @param color:       Color of the outline.
 * @param outlineSize: Size in pixels of the outline.
 *
 * @return False if the index is out of bounds, true if execution was
 *         successful.
 */
bool windowAddObjectOutline(Window* window, int index, SDL_Color color,
                            int outlineSize);

/**
 * @brief Hides the outline of an object in a window.
 *
 * @param window: The window containing the object's outline to hide.
 * @param index:  Index that determines which object's outline to hide.
 *
 * @return False if index if out of bounds, true otherwise.
 *
 * @sa windowShowObjectOutline()
 */
bool windowHideObjectOutline(Window* window, int index);

/**
 * @brief Makes the outline of an object in a window visible.
 *
 * @param window: The window containing the object's outline to make visible.
 * @param index:  Index that determines which object's outline to make visible.
 *
 * @return False if index if out of bounds, true if execution was successful.
 *
 * @sa windowHideObjectOutline()
 */
bool windowShowObjectOutline(Window* window, int index);

/**
 * @brief Recolors an object's outline in a window.
 *
 * @param window: The window containing the object's outline to recolor.
 * @param index:  Index that determines which object's outline to recolor.
 * @param color:  New color of the outline.
 *
 * @return False if index if out of bounds, true if execution was successful.
 */
bool windowRecolorObjectOutline(Window* window, int index, SDL_Color color);

/**
 * @brief Gives a new size to the outline an object has in a window.
 *
 * @param window:      The window containing the object's outline to resize.
 * @param index:       Index that determines which object's outline to resize.
 * @param outlineSize: New outline size.
 *
 * @return False if index if out of bounds, true if execution was successful.
 */
bool windowResizeObjectOutline(Window* window, int index, int outlineSize);

/**
 * @brief Finds how many objects of a specified type there is in a window.
 *
 * @param window: The window containing the objects to scan.
 * @param type:   Type of the object.
 *
 * @return The number of objects associated with a specified type in a window.
 */
int windowGetNbObjectType(Window window, winObjType type);

/**
 * @brief Finds the nth object of the specified type and returns its index.
 *
 * @param window:   The window containing the objects.
 * @param type:     Type of the object to find.
 * @param position: Position of the object to find (example: if position was
 *                  equal to 2, then we'd be searching for the 3rd object of
 *                  the specified type since position starts at 0).
 *
 * @return The index of the nth object of the specified type.
 */
int windowGetObjectIndex(Window window, winObjType type, int position);

/**
 * @brief Moves the specified window by a specific amount.
 *
 * @param window:  The window we are moving.
 * @param xAmount: The amount to move the window horizontally.
 * @param yAmount: The amount to move the window vertically.
 */
void windowMoveWindow(Window* window, int xAmount, int yAmount);

/**
 * @brief Pastes the window and its objects to the renderer.
 *
 * @param renderer: Renderer receiving the graphic information.
 * @param hudText:  Texture that contains the HUD graphic elements.
 * @param window:   Window to render.
 */
void windowToRenderer(SDL_Renderer* renderer, SDL_Texture* hudText,
                      Window window);

/**
 * @brief Frees all memory associated with a window.
 *
 * @param window: The window to destroy.
 */
void windowDestroy(Window* window);

#endif /* WINDOW_H_INCLUDED */
