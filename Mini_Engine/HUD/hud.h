#ifndef HUD_H_INCLUDED
#define HUD_H_INCLUDED

#include <stdbool.h>
#include <SDL.h>
#include <SDL_ttf.h>

/** HUD component types. */
enum EngHudCompType {ENG_NONE, ENG_TEXTBOX, ENG_IMAGE, ENG_BACKGROUND};

typedef struct _EngHudBorder {
    bool is_visible;
    int opacity;

    SDL_Rect src;
    SDL_Rect dst;
} EngHudBorder;
/**< HUD border structure containing coordinates and members that define
 *   visibility.
 */

typedef struct _EngHudComponent {
    EngHudCompType type;
    int saved_length;
    int saved_height;
    bool is_visible;
    bool is_interactive;
    bool has_outline;
    int outline_size;
    int opacity;

    SDL_Color color;
    SDL_Color outline_color;

    SDL_Texture* text;

    SDL_Rect src;
    SDL_Rect dst;
    SDL_Rect outline_dst;
} EngHudComponent;
/**< HUD component structure containing size, color and other info. */

typedef struct _EngHud {
    int x;    /* Position of HUD (relative to game window). */
    int y;
    int w;    /* Width and length of the HUD (inside the borders). */
    int h;

    int border_size;
    int nb_components;
    int selected_component;
    bool is_visible;

    EngHudBorder border[4];
    EngHudComponent *component;
} EngHud;
/**< HUD structure containing coordinates, hud components and border info. */

/**
 * @brief Initializes all the elements in a hud structure. Use this function
 *        to safely create a hud.
 *
 * @param x:           Position in x of the hud.
 * @param y:           Position in y of the hud.
 * @param w:           Width of the hud.
 * @param h:           Height of the hud.
 * @param border_size: Border size of the hud.
 *
 * @return An initialized hud structure.
 *
 * @sa eng_hud_destroy ()
 */
EngHud eng_hud_create_hud (int x, int y, int w, int h, int border_size);

/**
 * @brief Removes a component from a hud (reallocates memory and decreases
 *        count).
 *
 * @param hud:      The hud containing the array of components.
 * @param position: The index of the component to remove.
 *
 * @return False if component could not be removed or if there was no
 *         components, true if execution was successful.
 */
bool eng_hud_remove_component (EngHud *hud, int position);

/**
 * @brief Makes a component in a hud invisible.
 *
 * @param hud:   The hud containing the component to hide.
 * @param index: Index that determines which component to hide from the
 *               array of components.
 *
 * @return False if index is out of bounds, true if execution was successful.
 *
 * @sa eng_hud_show_component ()
 */
bool eng_hud_hide_component (EngHud *hud, int index);

/**
 * @brief Makes a component in a hud visible.
 *
 * @param hud:   The hud containing the component to make visible.
 * @param index: Index that determines which component to make visible from
 *               the array of components.
 *
 * @return False if index is out of bounds, true if execution was successful.
 *
 * @sa eng_hud_hide_component ()
 */
bool eng_hud_show_component (EngHud *hud, int index);

/**
 * @brief Changes the opacity of a hud component (0-255).
 *
 * @param hud:     Hud containing the component.
 * @param index:   Index of the component.
 * @param opacity: New opacity value for the component (0-255).
 *
 * @return False if index is out of bounds, true if execution was successful.
 */
bool eng_hud_set_component_opacity (EngHud *hud, int index, int opacity);

/**
 * @brief Modifies the size of a component by a factor.
 *
 * @param hud:    Hud containing the component to resize.
 * @param index:  Index of the component to resize in the hud's component
 *                array.
 * @param factor: Determines how much to multiply the size of the component by.
 *
 * @return False if index out of bounds, true if execution was successful.
 *
 * @sa eng_hud_reset_component_size ()
 */
bool eng_hud_resize_component (EngHud *hud, int index, double factor);

/**
 * @brief Sets the size of a component in a hud to its previously saved size.
 *
 * @param hud:   Hud containing the component to resize.
 * @param index: Index of the component to resize in the hud's component array.
 *
 * @return False if index out of bounds, true if execution was successful.
 *
 * @sa eng_hud_resize_component ()
 */
bool eng_hud_reset_component_size (EngHud *hud, int index);

/**
 * @brief Makes the hud's borders invisible.
 *
 * @param hud: The hud containing the borders to hide.
 *
 * @sa eng_hud_show_borders ()
 */
void eng_hud_hide_borders (EngHud *hud);

/**
 * @brief Makes the hud's borders visible.
 *
 * @param hud: The hud containing the borders to make visible.
 *
 * @sa eng_hud_hide_borders ()
 */
void eng_hud_show_borders (EngHud *hud);

/**
 * @brief Changes the opacity of a hud border (0-255).
 *
 * @param hud:     Hud containing the border.
 * @param index:   Index of the border.
 * @param opacity: New opacity value for the border (0-255).
 *
 * @return False if index is out of bounds, true if execution was successful.
 */
bool eng_hud_set_border_opacity (EngHud *hud, int index, int opacity);

/**
 * @brief Sets the source coordinates for a border in a hud.
 *
 * @param hud:         Hud containing the border.
 * @param borderIndex: The index of the border to modify.
 * @param src:         The source coordinates to give to the border.
 */
void eng_hud_set_border_src (EngHud *hud, int border_index, SDL_Rect src);

/**
 * @brief Adds a rectangular background as a component to the hud
 *        in parameters.
 *
 * @param hud:   The hud we are adding the component to.
 * @param color: The color of the rectangle.
 * @param dst:   The destination of the component (relative to the hud).
 *
 * @sa eng_hud_add_image () eng_hud_add_textbox ()
 */
void eng_hud_add_background (EngHud *hud, SDL_Color color, SDL_Rect dst);

/**
 * @brief Adds an image as a component to the hud in parameters.
 *
 * @param hud: The hud we are adding the component to.
 * @param src: The source coordinates of the component on the hud sprite sheet.
 * @param dst: The destination coordinates of the component (relative to the
 *             hud).
 *
 * @sa eng_hud_add_background () eng_hud_add_textbox ()
 */
void eng_hud_add_image (EngHud *hud, SDL_Rect src, SDL_Rect dst);

/**
 * @brief Adds a text box as a component to the hud in parameters.
 *
 * @param hud:  The hud we are adding the component to.
 * @param text: The texture containing the words.
 * @param dst:  The destination coordinates of the component (relative to
 *              the hud).
 *
 * @sa eng_create_textbox_texture () eng_hud_add_background ()
 *     eng_hud_add_image ()
 */
void eng_hud_add_textbox (EngHud *hud, SDL_Texture *text, SDL_Rect dst);

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
SDL_Texture * eng_create_textbox_texture (SDL_Renderer *renderer, char text[],
                                          TTF_Font *font, SDL_Color color,
                                          int length);

/**
 * @brief Changes the texture of a text box.
 *
 * @param hud:   The hud we are modifying component from.
 * @param index: The index of the component to modify.
 * @param text:  The new texture containing the new words.
 *
 * @return False if index is out of bounds, true is execution was successful.
 *
 * @sa eng_create_textbox_texture ()
 */
bool eng_hud_change_textbox_text (EngHud *hud, int index, SDL_Texture *text);

/**
 * @brief Adds an outline to a component in a hud.
 *
 * @param hud:          The hud containing the component to add an outline to.
 * @param index:        Index that determines which component to add an
 *                      outline to.
 * @param color:        Color of the outline.
 * @param outline_size: Size in pixels of the outline.
 *
 * @return False if the index is out of bounds, true if execution was
 *         successful.
 */
bool eng_hud_add_component_outline (EngHud *hud, int index, SDL_Color color,
                                    int outline_size);

/**
 * @brief Hides the outline of a component in a hud.
 *
 * @param hud:   The hud containing the component's outline to hide.
 * @param index: Index that determines which component's outline to hide.
 *
 * @return False if index if out of bounds, true otherwise.
 *
 * @sa eng_hud_show_component_outline ()
 */
bool eng_hud_hide_component_outline (EngHud *hud, int index);

/**
 * @brief Makes the outline of an component in a hud visible.
 *
 * @param hud:   The hud containing the component's outline to make visible.
 * @param index: Index that determines which component's outline to make
 *               visible.
 *
 * @return False if index if out of bounds, true if execution was successful.
 *
 * @sa eng_hud_hide_component_outline ()
 */
bool eng_hud_show_component_outline (EngHud *hud, int index);

/**
 * @brief Recolors a component's outline in a hud.
 *
 * @param hud:   The hud containing the component's outline to recolor.
 * @param index: Index that determines which component's outline to recolor.
 * @param color: New color of the outline.
 *
 * @return False if index if out of bounds, true if execution was successful.
 *
 * @sa eng_hud_resize_component_outline ()
 */
bool eng_hud_recolor_component_outline (EngHud *hud, int index,
                                        SDL_Color color);

/**
 * @brief Gives a new size to the outline an component has in a hud.
 *
 * @param hud:          The hud containing the component's outline to resize.
 * @param index:        Index that determines which component's outline to
 *                      resize.
 * @param outline_size: New outline size.
 *
 * @return False if index if out of bounds, true if execution was successful.
 *
 * @sa eng_hud_recolor_component_outline ()
 */
bool eng_hud_resize_component_outline (EngHud *hud, int index,
                                       int outline_size);

/**
 * @brief Finds how many components of a specified type there is in a hud.
 *
 * @param hud:  The hud containing the components to scan.
 * @param type: Type of the component.
 *
 * @return The number of components associated with a specified type in a hud.
 *
 * @sa eng_hud_get_component_index ()
 */
int eng_hud_get_nb_component_type (EngHud hud, EngHudCompType type);

/**
 * @brief Finds the nth component of the specified type and returns its index.
 *
 * @param hud:      The hud containing the components.
 * @param type:     Type of the component to find.
 * @param position: Position of the component to find (example: if position was
 *                  equal to 2, then we'd be searching for the 3rd component of
 *                  the specified type since position starts at 0).
 *
 * @return The index of the nth component of the specified type.
 *
 * @sa eng_hud_get_nb_component_type ()
 */
int eng_hud_get_component_index (EngHud hud, EngHudCompType type,
                                 int position);

/**
 * @brief Moves a hud to specified absolute coordinates relative to the game
 *        screen.
 *
 * @param hud: Hud to move.
 * @param x:   Destination coordinates in x.
 * @param y:   Destination coordinates in y.
 *
 * @sa eng_hud_move_hud ()
 */
void eng_hud_move_hud_absolute (EngHud *hud, int x, int y);

/**
 * @brief Moves the specified hud by a specific amount.
 *
 * @param hud:      The hud we are moving.
 * @param x_amount: The amount to move the hud horizontally.
 * @param y_amount: The amount to move the hud vertically.
 *
 * @sa eng_hud_move_hud_absolute ()
 */
void eng_hud_move_hud (EngHud *hud, int x_amount, int y_amount);

/**
 * @brief Gives a new width and height to a hud.
 *
 * @param hud: Hud to resize.
 * @param w:   New width of the hud.
 * @param h:   New Height of the hud.
 */
void eng_hud_resize_hud (EngHud *hud, int w, int h);

/**
 * @brief Pastes the hud and its components to the renderer.
 *
 * @param renderer: Renderer receiving the graphic information.
 * @param hud_text: Texture that contains the hud graphic elements.
 * @param hud:      Hud to render.
 */
void eng_hud_to_renderer (SDL_Renderer *renderer, SDL_Texture *hud_text,
                          EngHud hud);

/**
 * @brief Frees all memory associated with a hud.
 *
 * @param hud: The hud to destroy.
 *
 * @sa eng_hud_create_hud ()
 */
void eng_hud_destroy (EngHud *hud);

#endif /* HUD_H_INCLUDED */
