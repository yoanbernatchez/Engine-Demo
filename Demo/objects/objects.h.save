#ifndef OBJECTS_H_INCLUDED
#define OBJECTS_H_INCLUDED

/**
 * @brief Returns a sprite sheet texture that contains the graphics of all the
 *        objects.
 *
 * @param renderer: Renderer allowing us to create textures.
 *
 * @return A sprite sheet texture for objects to use.
 */
SDL_Texture * object_get_texture(SDL_Renderer *renderer);

/**
 * @brief Returns a sprite sheet texture that contains the graphics of all the
 *        tiles.
 *
 * @param renderer: Renderer allowing us to create textures.
 *
 * @return A sprite sheet texture for tiles to use.
 */
SDL_Texture * tile_get_texture (SDL_Renderer *renderer);

/**
 * @brief Assigns properties to all the objects that have defined properties
 *        linked to their id in the array of chunks.
 *
 * @param chunk: Array of chunks containing object data.
 */
void object_assign_properties (EngChunk chunk[]);

/**
 * @brief Handles changes and updates objects on the map.
 *
 * @param chunk: Array of chunks containing object data.
 * @param timer: Timer(s) used to update objects.
 */
void object_handler (EngChunk chunk[], double *timer);

#endif /* OBJECTS_H_INCLUDED */
