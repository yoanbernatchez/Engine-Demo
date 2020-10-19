#ifndef WHEAT_H_INCLUDED
#define WHEAT_H_INCLUDED

#include "../../Mini_Engine/Engine/globals.h"
#include "../../Mini_Engine/Time/time.h"

/**
 * @brief Changes the frame of the wheat object after some time to animate it.
 *
 * @param chunk: Array of chunks containing object data.
 * @param timer: Timer used to change the frame of the wheat.
 */
void wheat_next_frame (EngChunk chunk[], double *timer);

#endif /* WHEAT_H_INCLUDED */
