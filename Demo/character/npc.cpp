#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "../../Mini_Engine/Time/time.h"
#include "npc.h"

/*---------------------------------------------------------------------------*/
/* Local function prototypes                                                 */
/*---------------------------------------------------------------------------*/

/**
 * @brief Changes the path of an entity to a new path, determined by a path id.
 *
 * @param chunk:   Array of chunks used for finding a path.
 * @param entity:  The entity where the path is stored.
 * @param path_id: The id of the path we want to retrieve.
 */
static void npc_get_path (EngChunk chunk[], Entity *entity, int path_id);

/**
 * @brief Makes an entity move by following a path.
 *
 * @param entity: The entity that will follow a path.
 */
static void npc_move_with_path (Entity *entity);

/**
 * @brief Changes the orientation of an array of entities, based on luck when
 *        their action_id is IDLE.
 *
 * @param entity:      Array of entities to change the orientation for.
 * @param nb_entities: Number of entities in the array.
 */
static void npc_idle_rotation (Entity entity[], int nb_entities);

/*---------------------------------------------------------------------------*/
/* NPC function implementations                                              */
/*---------------------------------------------------------------------------*/

/* Handles the updates and actions of all the NPCs. */
void
npc_handler (EngChunk chunk[], Entity entity[], int nb_entities)
{
    /* All npcs rotate in random intervals when idle. */
    npc_idle_rotation (entity, nb_entities);

    /* Get path for npc 1. */
    npc_get_path (chunk, &entity[1], entity[1].path_id);
    npc_move_with_path (&entity[1]);
}

/*
 * Changes the orientation of an array of entities, based on luck when
 * their action_id is IDLE.
 */
static void
npc_idle_rotation (Entity entity[], int nb_entities)
{
    int random_number = -1;

    for (int i = 1; i < nb_entities; i++) {
        if (entity[i].character.action_id == ENTITY_IDLE &&
            eng_has_time_elapsed (&entity[i].character.timer[1], true,
                                  ENG_SECOND, 1)) {
            random_number = rand() % 10;

            switch (random_number) {
            case 0:
                entity[i].character.direction = ENG_RIGHT;
                break;
            case 1:
                entity[i].character.direction = ENG_LEFT;
                break;
            default:
                entity[i].character.direction = ENG_DOWN;
                break;
            }

            entity_villager_update_src (&entity[i].character);
        }
    }
}

/* Makes an entity move by following a path. */
static void
npc_move_with_path (Entity *entity)
{
    if (entity->path != NULL) {
        int add_step = 0;

        /*
         * Here we check if the NPC has traveled the equivalent of a whole
         * step.
         */
        if (abs (entity->saved_x - entity->character.x) >= TILESIZE) {
            entity->saved_x = entity->character.x;
            add_step = 1;
        }
        if (abs (entity->saved_y - entity->character.y) >= TILESIZE) {
            entity->saved_y = entity->character.y;
            add_step = 1;
        }

        entity->step += add_step;

        /* We try to move the NPC towards the next step of the path. */
        if (eng_has_time_elapsed (&entity->character.timer[0], true,
                                  ENG_MILLISECOND, 17)) {
            int move_x = 0;
            int move_y = 0;

            /*
             * We determine how much the NPC will move and which direction it
             * should take if there are still steps until the destination is
             * reached.
             */
            if (entity->step < entity->path->nb_steps &&
                entity->path->direction != NULL) {
                if (entity->path->direction[entity->step] == ENG_LEFT) {
                    move_x = -entity->character.speed;
                    entity->character.direction = ENG_LEFT;
                }
                else if (entity->path->direction[entity->step] == ENG_RIGHT) {
                    move_x = entity->character.speed;
                    entity->character.direction = ENG_RIGHT;
                }
                else if (entity->path->direction[entity->step] == ENG_UP) {
                    move_y = -entity->character.speed;
                    entity->character.direction = ENG_UP;
                }
                else if (entity->path->direction[entity->step] == ENG_DOWN) {
                    move_y = entity->character.speed;
                    entity->character.direction = ENG_DOWN;
                }
            }
            /* If the destination is reached, we delete the path. */
            else {
                if (entity->path != NULL) {
                    eng_pathfind_destroy_path(&entity->path);
                    entity->step = 0;
                }
                if (entity->path_id == 0)
                    entity->path_id = 1;
                else
                    entity->path_id = 0;
            }

            /*
             * Update the action of the NPC, depending on if he moves or not.
             */
            if (move_x != 0 || move_y != 0)
                entity->character.action_id = 1;
            else
                entity->character.action_id = 0;

            /* Then we move and update the NPC. */
            eng_char_move_character (&entity->character, move_x, move_y);
            entity_villager_update_src (&entity->character);
        }
    }
}

/* Changes the path of an entity to a new path, determined by a path id. */
static void
npc_get_path (EngChunk chunk[], Entity *entity, int path_id)
{
    if (entity->path == NULL) {
        int offset_x = 0;
        int offset_y = 0;

        if (chunk[1].chunk_x == chunk[0].chunk_x - 1)
            offset_x = TILESX;

        if (chunk[2].chunk_y == chunk[0].chunk_y - 1)
            offset_y = TILESY;

        switch (path_id) {
        /* From bridge to village. */
        case 0:
            for (int i = 0; i < NBCHUNKS; i++) {
                if (chunk[i].chunk_x == 0 && chunk[i].chunk_y == 0) {
                    entity->path = eng_pathfind_get_path (chunk,
                                                          22 + offset_x,
                                                          4 + offset_y,
                                                          35 + offset_x,
                                                          10 + offset_y);
                    break;
                }
            }
            break;
        /* From village to bridge. */
        case 1:
            for (int i = 0; i < NBCHUNKS; i++) {
                if (chunk[i].chunk_x == 0 && chunk[i].chunk_y == 0) {
                    entity->path = eng_pathfind_get_path (chunk,
                                                          35 + offset_x,
                                                          10 + offset_y,
                                                          22 + offset_x,
                                                          4 + offset_y);
                    break;
                }
            }
            break;
        }
    }
}
