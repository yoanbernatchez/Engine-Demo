/*
 * Author: YOAN BERNATCHEZ
 * Date: 2020-08-01
 *
 * This file provides the user with functions to create hud and add components
 * to them. It also allows the user to update and copy hud to the renderer.
 * The main goal was to make the code portable to other SDL projects.
 */

/*
 * TODO: Create an error message system with __LINE__ and __FILE__ to remove
 *       the repetitive error checks.
 */

#include <stdio.h>
#include <stdlib.h>
#include <SDL_image.h>
#include "hud.h"

/*---------------------------------------------------------------------------*/
/* Local function prototypes                                                 */
/*---------------------------------------------------------------------------*/

/**
 * @brief Adds a component to a hud (allocates memory & increases count).
 *
 * @param hud: The hud containing the array of components.
 *
 * @sa eng_hud_remove_component ()
 */
static void add_component (EngHud *hud);

/**
 * @brief Updates the positions and size of the borders according to the size
 *        of the hud.
 *
 * @param hud: The hud containing the borders to update.
 */
static void update_borders (EngHud *hud);

/**
 * @brief Saves the size of a component before modification.
 *
 * @param hud:   The hud containing the component.
 * @param index: The index of the component we want to save the size of.
 */
static void save_component_size (EngHud *hud, int index);

/**
 * @brief Sets the coordinates of a hud's component (relative to the hud).
 *
 * @param hud:   The hud containing the component.
 * @param dst:   The destination coordinates of the component (relative to the
 *               hud).
 * @param index: The index of the component we want to modify.
 */
static void assign_component_position (EngHud *hud, int index, SDL_Rect dst);

/*---------------------------------------------------------------------------*/
/* HUD function implementations                                              */
/*---------------------------------------------------------------------------*/

/* Safe way to create a hud. */
EngHud
eng_hud_create_hud (int x, int y, int w, int h, int border_size)
{
    EngHud hud;
    SDL_Rect null_rect = {0, 0, 0, 0};

    hud.x = x;
    hud.y = y;
    hud.w = w;
    hud.h = h;

    hud.border_size = border_size;
    hud.nb_components = 0;
    hud.selected_component = 0;
    hud.is_visible = true;

    /* Initialize the four borders. */
    for (int i = 0; i < 4; i++) {
        hud.border[i].is_visible = true;
        hud.border[i].opacity = 255;
        hud.border[i].src = null_rect;
    }

    /* Protection against negative sizes. */
    if (hud.w < 0)
        hud.w = 0;
    if (hud.h < 0)
        hud.h = 0;
    if (hud.border_size < 0)
        hud.border_size = 0;

    update_borders (&hud);

    return hud;
}

/* Makes a component in a hud invisible. */
bool
eng_hud_hide_component (EngHud *hud, int index)
{
    bool result;

    if (index < hud->nb_components && index >= 0) {
        hud->component[index].is_visible = false;
        result = true;
    }
    else {
        printf ("Index out of bounds in %s %d\n", __FILE__, __LINE__);
        result = false;
    }

    return result;
}

/* Makes a component in a hud visible. */
bool
eng_hud_show_component (EngHud *hud, int index)
{
    bool result;

    if (index < hud->nb_components && index >= 0) {
        hud->component[index].is_visible = true;
        result = true;
    }
    else {
        printf ("Index out of bounds in %s %d\n", __FILE__, __LINE__);
        result = false;
    }

    return result;
}

/* Changes the opacity of a hud component (0-255). */
bool
eng_hud_set_component_opacity (EngHud *hud, int index, int opacity)
{
    bool result;

    if (index < hud->nb_components && index >= 0) {
        if (opacity < 0)
            hud->component[index].opacity = 0;
        else if (opacity > 255)
            hud->component[index].opacity = 255;
        else
            hud->component[index].opacity = opacity;
        result = true;
    }
    else {
        printf ("Index out of bounds in %s %d\n", __FILE__, __LINE__);
        result = false;
    }

    return result;
}

/* Adds an outline to a component in a hud. */
bool
eng_hud_add_component_outline (EngHud *hud, int index, SDL_Color color,
                               int outline_size)
{
    bool result;

    if (index < hud->nb_components && index >= 0) {
        eng_hud_show_component_outline (hud, index);
        eng_hud_recolor_component_outline (hud, index, color);
        eng_hud_resize_component_outline (hud, index, outline_size);
        result = true;
    }
    else {
        printf ("Index out of bounds in %s %d\n", __FILE__, __LINE__);
        result = false;
    }

    return result;
}

/* Recolors a component's outline in a hud. */
bool
eng_hud_recolor_component_outline (EngHud *hud, int index, SDL_Color color)
{
    bool result;

    if (index < hud->nb_components && index >= 0) {
        hud->component[index].outline_color.r = color.r;
        hud->component[index].outline_color.g = color.g;
        hud->component[index].outline_color.b = color.b;
        hud->component[index].outline_color.a = color.a;
        result = true;
    }
    else {
        printf ("Index out of bounds in %s %d\n", __FILE__, __LINE__);
        result = false;
    }

    return result;
}

/* Gives a new size to the outline a component has in a hud. */
bool
eng_hud_resize_component_outline (EngHud *hud, int index, int outline_size)
{
    bool result;

    if (index < hud->nb_components && index >= 0) {
        hud->component[index].outline_size = outline_size;

        hud->component[index].outline_dst.x = hud->component[index].dst.x -
                                            hud->component[index].outline_size;

        hud->component[index].outline_dst.y = hud->component[index].dst.y -
                                            hud->component[index].outline_size;

        hud->component[index].outline_dst.w = hud->component[index].dst.w + 2 *
                                            hud->component[index].outline_size;

        hud->component[index].outline_dst.h = hud->component[index].dst.h + 2 *
                                            hud->component[index].outline_size;

        if (hud->component[index].outline_dst.w < 0)
            hud->component[index].outline_dst.w = 0;

        if (hud->component[index].outline_dst.h < 0)
            hud->component[index].outline_dst.h = 0;

        result = true;
    }
    else {
        printf ("Index out of bounds in %s %d\n", __FILE__, __LINE__);
        result = false;
    }

    return result;
}

/* Hides the outline of a component in a hud. */
bool
eng_hud_hide_component_outline (EngHud *hud, int index)
{
    bool result;

    if (index < hud->nb_components && index >= 0) {
        hud->component[index].has_outline = false;
        result = true;
    }
    else {
        printf ("Index out of bounds in %s %d\n", __FILE__, __LINE__);
        result = false;
    }

    return result;
}

/* Makes the outline of a component in a hud visible. */
bool
eng_hud_show_component_outline (EngHud *hud, int index)
{
    bool result;

    if (index < hud->nb_components && index >= 0) {
        hud->component[index].has_outline = true;
        result = true;
    }
    else {
        printf ("Index out of bounds in %s %d\n", __FILE__, __LINE__);
        result = false;
    }

    return result;
}

/* Finds the nth component of the specified type and returns its index. */
int
eng_hud_get_component_index (EngHud hud, EngHudCompType type, int position)
{
    int index = -1;
    int counter = 0;

    for (int i = 0; i < hud.nb_components; i++) {
        if (hud.component[i].type == type && position == counter) {
            index = i;
            break;
        }
        else if (hud.component[i].type == type && position != counter)
            counter++;
    }

    return index;
}

/*
 * Finds all the components of a specified type in a hud, counts them and
 * returns how many there are.
 */
int
eng_hud_get_nb_component_type (EngHud hud, EngHudCompType type)
{
    int counter = 0;

    for (int i = 0; i < hud.nb_components; i++) {
        if (hud.component[i].type == type)
            counter++;
    }

    return counter;
}

/*
 * Modifies the size of a component by a factor, for instance, a factor of 2
 * doubles the size of the component.
 *
 * The reason why we pass the hud instead of the component itself is to
 * check if the component at the specified index exists. Not checking if the
 * component exists might cause crashes if the index is out of bounds (there
 * might be a better way to check this?).
 */
bool
eng_hud_resize_component (EngHud *hud, int index, double factor)
{
    bool result;
    int w_factored;
    int h_factored;

    if (index < hud->nb_components && index >= 0) {
        w_factored = hud->component[index].dst.w * factor;
        h_factored = hud->component[index].dst.h * factor;

        /* Adjusting the component's coordinates. */
        hud->component[index].dst.x -= (w_factored -
                                        hud->component[index].dst.w) / 2;
        hud->component[index].dst.y -= (h_factored -
                                        hud->component[index].dst.h) / 2;

        hud->component[index].dst.w = w_factored;
        hud->component[index].dst.h = h_factored;

        /*
         * This is protection against negative width or height.
         * If w_factored or h_factored is zero, then the component becomes
         * invisible and any subsequent call of this function won't
         * restore the width or height value of the component to more than 0,
         * no matter what the factor is. At this point, you need to call
         * eng_hud_reset_component_size ().
         */
        if (w_factored < 0 || h_factored < 0) {
            hud->component[index].dst.x = 0;
            hud->component[index].dst.y = 0;
            hud->component[index].dst.w = 0;
            hud->component[index].dst.h = 0;
        }

        result = true;
    }
    else {
        printf ("Index out of bounds in %s %d\n", __FILE__, __LINE__);
        result = false;
    }

    return result;
}

/*
 * Sets the size of a component in a hud to its previously saved size.
 *
 * The reason why we pass the hud instead of the component itself is to
 * check if the component at the specified index exists. Not checking if the
 * component exists might cause crashes if the index is out of bounds (there
 * might be a better way to check this?).
 */
bool
eng_hud_reset_component_size (EngHud *hud, int index)
{
    int w_diff;
    int h_diff;
    bool result;

    if (index < hud->nb_components && index >= 0) {
        w_diff = hud->component[index].dst.w -
                 hud->component[index].saved_length;
        h_diff = hud->component[index].dst.h -
                 hud->component[index].saved_height;

        hud->component[index].dst.x += w_diff / 2;
        hud->component[index].dst.y += h_diff / 2;

        hud->component[index].dst.w = hud->component[index].saved_length;
        hud->component[index].dst.h = hud->component[index].saved_height;

        result = true;
    }
    else {
        printf ("Index out of bounds in %s %d\n", __FILE__, __LINE__);
        result = false;
    }

    return result;
}

/*
 * Adds a component to a hud (allocates memory, initializes component
 * and increases count).
 */
static void
add_component (EngHud *hud)
{
    if (hud->nb_components == 0)
        hud->component = (EngHudComponent*) malloc (sizeof(EngHudComponent));
    else {
        hud->component = (EngHudComponent*) realloc (hud->component,
                                                     (hud->nb_components + 1) *
                                                     sizeof(EngHudComponent));
    }

    SDL_Color null_color = {0, 0, 0, 0};
    SDL_Rect null_rect = {0, 0, 0, 0};

    /* Initializing all members of component. */
    hud->component[hud->nb_components].saved_length = 0;
    hud->component[hud->nb_components].saved_height = 0;
    hud->component[hud->nb_components].type = ENG_NONE;
    hud->component[hud->nb_components].is_visible = true;
    hud->component[hud->nb_components].is_interactive = false;
    hud->component[hud->nb_components].has_outline = false;
    hud->component[hud->nb_components].outline_size = 0;
    hud->component[hud->nb_components].opacity = 255;
    hud->component[hud->nb_components].color = null_color;
    hud->component[hud->nb_components].outline_color = null_color;
    hud->component[hud->nb_components].text = NULL;
    hud->component[hud->nb_components].src = null_rect;
    hud->component[hud->nb_components].dst = null_rect;
    hud->component[hud->nb_components].outline_dst = null_rect;

    hud->nb_components += 1;
}

/* Removes a component from a hud (reallocates memory & decreases count). */
bool
eng_hud_remove_component (EngHud *hud, int position)
{
    bool result;

    if (hud->nb_components > 0 &&
        position < hud->nb_components &&
        position >= 0) {

        hud->nb_components -= 1;

        for (int j = position; j< hud->nb_components; j++)
            hud->component[j] = hud->component[j + 1];

        if (hud->nb_components == 0)
            free (hud->component);
        else {
            hud->component = (EngHudComponent*)
                              realloc (hud->component, (hud->nb_components) *
                                       sizeof(EngHudComponent));
        }

        result = true;
    }
    else {
        printf ("No component or index out of bounds in %s %d\n",
                __FILE__, __LINE__);
        result = false;
    }

    return result;
}

/* Takes a hud in parameter and frees all the memory associated to it. */
void
eng_hud_destroy (EngHud *hud)
{
    /* Free all textures assigned. */
    for (int i = 0; i < hud->nb_components; i++) {
        if (hud->component[i].text != NULL)
            SDL_DestroyTexture (hud->component[i].text);
    }

    /* Then free components. */
    if (hud->nb_components != 0) {
        hud->nb_components = 0;
        free (hud->component);
    }
}

/* Creates a TTF texture from text. */
SDL_Texture *
eng_create_textbox_texture (SDL_Renderer *renderer, char text[],
                            TTF_Font *font, SDL_Color color, int length)
{
    SDL_Surface *surf = TTF_RenderText_Blended_Wrapped (font, text, color,
                                                        length);

    SDL_Texture *texture = SDL_CreateTextureFromSurface (renderer, surf);

    SDL_FreeSurface (surf);

    return texture;
}

/*
 * Adds a rectangular background filled with a specified color as
 * a component to the hud in parameters.
 */
void
eng_hud_add_background (EngHud *hud, SDL_Color color, SDL_Rect dst)
{
    add_component (hud);
    int index = hud->nb_components - 1;

    hud->component[index].type = ENG_BACKGROUND;
    hud->component[index].color = color;

    assign_component_position (hud, index, dst);
    save_component_size (hud, index);
}

/* Adds a text box as a component to the hud in parameters. */
void
eng_hud_add_textbox (EngHud *hud, SDL_Texture *text, SDL_Rect dst)
{
    add_component (hud);
    int index = hud->nb_components - 1;

    hud->component[index].type = ENG_TEXTBOX;
    hud->component[index].text = text;

    assign_component_position (hud, index, dst);
    save_component_size (hud, index);
}

/*
 * Changes the texture of a text box, it is useful for changing
 * the text (words) on screen on an already defined text box texture.
 */
bool
eng_hud_change_textbox_text (EngHud *hud, int index, SDL_Texture *text)
{
    bool result;

    if (index < hud->nb_components && index >= 0) {
        SDL_DestroyTexture (hud->component[index].text);
        hud->component[index].text = text;
        result = true;
    }
    else {
        printf ("Index out of bounds in %s %d\n", __FILE__, __LINE__);
        result = false;
    }

    return result;
}

/* Adds an image as a component to the hud in parameters. */
void
eng_hud_add_image (EngHud *hud, SDL_Rect src, SDL_Rect dst)
{
    add_component (hud);
    int index = hud->nb_components - 1;

    hud->component[index].type = ENG_IMAGE;
    hud->component[index].src = src;

    assign_component_position (hud, index, dst);
    save_component_size (hud, index);
}

/* Moves the hud to absolute coordinates on screen. */
void
eng_hud_move_hud_absolute (EngHud *hud, int x, int y)
{
    int diff_x = x - hud->x;
    int diff_y = y - hud->y;

    eng_hud_move_hud (hud, diff_x, diff_y);
}

/* Resizes the hud with a new w and h. */
void
eng_hud_resize_hud (EngHud *hud, int w, int h)
{
    hud->w = w;
    hud->h = h;
    update_borders (hud);
}

/*
 * Moves the specified hud by a certain amount, also updates all the components
 * and borders to move along with the hud.
 */
void
eng_hud_move_hud (EngHud *hud, int x_amount, int y_amount)
{
    /* Move coordinates of the hud. */
    hud->x += x_amount;
    hud->y += y_amount;

    /* Adjust hud borders depending on coordinates and size of hud. */
    update_borders (hud);

    /* Move coordinates of the hud's components and their outlines. */
    for (int i = 0; i < hud->nb_components; i++) {
        hud->component[i].dst.x += x_amount;
        hud->component[i].dst.y += y_amount;

        if (hud->component[i].has_outline) {
            hud->component[i].outline_dst.x += x_amount;
            hud->component[i].outline_dst.y += y_amount;
        }
    }
}

/* Sets the coordinates of a hud's component (relative to the hud). */
static void
assign_component_position (EngHud *hud, int index, SDL_Rect dst)
{
    hud->component[index].dst.x = hud->x + hud->border_size + dst.x;
    hud->component[index].dst.y = hud->y + hud->border_size + dst.y;
    hud->component[index].dst.w = dst.w;
    hud->component[index].dst.h = dst.h;
}

/*
 * Saves the size of a component before modification so that we do not lose
 * its original size.
 */
static void
save_component_size (EngHud *hud, int index)
{
    hud->component[index].saved_length = hud->component[index].dst.w;
    hud->component[index].saved_height = hud->component[index].dst.h;
}

/* Sets the source coordinates for a border in a hud. */
void
eng_hud_set_border_src (EngHud *hud, int border_index, SDL_Rect src)
{
    if (border_index >= 0 && border_index < 4) {
        hud->border[border_index].src.x = src.x;
        hud->border[border_index].src.y = src.y;
        hud->border[border_index].src.w = src.w;
        hud->border[border_index].src.h = src.h;
    }
}

/*
 * Updates the positions and size of the borders
 * according to the size of the hud.
 */
static void
update_borders (EngHud *hud)
{
    hud->border[0].dst.x = hud->x;
    hud->border[0].dst.y = hud->y;
    hud->border[0].dst.w = hud->border_size;
    hud->border[0].dst.h = hud->h + hud->border_size * 2;

    hud->border[2].dst.x = hud->x + hud->w + hud->border[0].dst.w;
    hud->border[2].dst.y = hud->y;
    hud->border[2].dst.w = hud->border_size;
    hud->border[2].dst.h = hud->h + hud->border_size * 2;

    hud->border[1].dst.x = hud->x + hud->border_size;
    hud->border[1].dst.y = hud->y;
    hud->border[1].dst.w = hud->w;
    hud->border[1].dst.h = hud->border_size;

    hud->border[3].dst.x = hud->x + hud->border_size;
    hud->border[3].dst.y = hud->y + hud->h + hud->border_size;
    hud->border[3].dst.w = hud->w;
    hud->border[3].dst.h = hud->border_size;
}

/* Makes the hud's borders invisible. */
void
eng_hud_hide_borders (EngHud *hud)
{
    for (int i = 0; i < 4; i++)
        hud->border[i].is_visible = false;
}

/* Makes the hud's borders visible. */
void
eng_hud_show_borders (EngHud *hud)
{
    for (int i = 0; i < 4; i++)
        hud->border[i].is_visible = true;
}

/* Changes the opacity of a hud border (0-255). */
bool
eng_hud_set_border_opacity (EngHud *hud, int index, int opacity)
{
    bool result;

    if (index < 4 && index >= 0) {
        if (opacity < 0)
            hud->border[index].opacity = 0;
        else if (opacity > 255)
            hud->border[index].opacity = 255;
        else
            hud->border[index].opacity = opacity;
        result = true;
    }
    else {
        printf ("Index out of bounds in %s %d\n", __FILE__, __LINE__);
        result = false;
    }

    return result;
}

/* Pastes the hud and its components to the renderer. */
void
eng_hud_to_renderer (SDL_Renderer *renderer, SDL_Texture *hud_text, EngHud hud)
{
    if (hud.is_visible) {
        for (int i = 0; i < hud.nb_components; i++) {
            /* Copy components to renderer if they are set to be visible. */
            if (hud.component[i].is_visible) {
                switch (hud.component[i].type) {
                case ENG_TEXTBOX:
                    SDL_SetTextureAlphaMod (hud.component[i].text,
                                            hud.component[i].opacity);
                    SDL_RenderCopy (renderer, hud.component[i].text, NULL,
                                    &hud.component[i].dst);
                    break;
                case ENG_IMAGE:
                    SDL_SetTextureAlphaMod (hud.component[i].text,
                                            hud.component[i].opacity);
                    SDL_RenderCopy (renderer, hud_text, &hud.component[i].src,
                                    &hud.component[i].dst);
                    break;
                case ENG_BACKGROUND:
                    SDL_SetRenderDrawColor (renderer,
                                            hud.component[i].color.r,
                                            hud.component[i].color.g,
                                            hud.component[i].color.b,
                                            hud.component[i].opacity);
                    SDL_RenderFillRect (renderer, &hud.component[i].dst);
                    break;
                case ENG_NONE:
                    break;
                }

                /* Copy component outlines to renderer. */
                if (hud.component[i].has_outline) {
                    SDL_SetRenderDrawColor (renderer,
                                            hud.component[i].outline_color.r,
                                            hud.component[i].outline_color.g,
                                            hud.component[i].outline_color.b,
                                            hud.component[i].opacity);

                    SDL_RenderFillRect (renderer,
                                        &hud.component[i].outline_dst);
                }
            }
        }

        /* Copy borders to renderer. */
        for (int j = 0; j < 4; j++) {
            if (hud.border[j].is_visible) {
                SDL_SetTextureAlphaMod (hud_text, hud.border[j].opacity);
                SDL_RenderCopy (renderer, hud_text, &hud.border[j].src,
                                &hud.border[j].dst);
            }
        }
    }
}
