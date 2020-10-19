#include "wheat.h"
#include <stdio.h>

/*---------------------------------------------------------------------------*/
/* Local function prototypes                                                 */
/*---------------------------------------------------------------------------*/

/**
 * @brief Sets the source coordinates of the object on the sprite sheet.
 *
 * @param object: Object to set the source coordinates of.
 */
static void wheat_set_src (EngObject *object);

/*---------------------------------------------------------------------------*/
/* Wheat function implementations                                            */
/*---------------------------------------------------------------------------*/

/* Changes the frame of the wheat object after some time to animate it. */
void
wheat_next_frame (EngChunk chunk[], double *timer)
{
    if (eng_has_time_elapsed (timer, true, ENG_SECOND, 5)) {
        /* In every loaded chunk... */
        for (int i = 0; i < NBCHUNKS; i++) {
            /* All the objects that correspond to wheat (id: 5) get updated. */
            for (int j = 0; j < chunk[i].nb_objects; j++) {
                if (chunk[i].object[j].id == 5) {
                    if (chunk[i].object[j].frame == 0)
                        chunk[i].object[j].frame = 1;
                    else
                        chunk[i].object[j].frame = 0;

                    wheat_set_src (&chunk[i].object[j]);
                }
            }
        }
    }
}

/* Sets the source coordinates of the object on the sprite sheet. */
static void
wheat_set_src (EngObject *object)
{
    if (object->frame == 0)
        object->src.x = 494;
    else if (object->frame == 1)
        object->src.x = 560;
}
