/*
 * Author: YOAN BERNATCHEZ
 * Date: 2020-09-22
 *
 * This file provides the user simple time functionalities.
 */

#include <time.h>
#include "time.h"

/*
 * Returns the current real clock time in seconds since the start of the
 * program.
 */
double
timeGetRealTime(void)
{
    return (double) clock() / CLOCKS_PER_SEC;
}

/*
 * Returns the real clock time in seconds since start of program, affected by
 * a time ratio (game time ratio).
 */
double
timeGetGameTime(void)
{
    return (double) clock() / CLOCKS_PER_SEC * TIMERATIO;
}

/* Updates a Time structure to the current real time. */
void
timeUpdateRealTime(Time *realTime)
{
    double currentTime = timeGetRealTime();

    realTime->day = (int) currentTime / 86400;
    realTime->hour = (int) currentTime / 3600 % 24;
    realTime->minute = (int) currentTime / 60 % 60;
    realTime->second = (int) currentTime % 60;
    realTime->millisecond = (int) currentTime * 1000 % 1000;
}

/* Updates a Time structure to the current game time. */
void
timeUpdateIngameTime(Time *gameTime)
{
    double currentGameTime = timeGetRealTime() * TIMERATIO;

    gameTime->day = (int) currentGameTime / 86400;
    gameTime->hour = (int) currentGameTime / 3600 % 24;
    gameTime->minute = (int) currentGameTime / 60 % 60;
    gameTime->second = (int) currentGameTime % 60;
    gameTime->millisecond = (int) currentGameTime * 1000 % 1000;
}

/*
 * Tests if a certain amount of time has passed since last checking the
 * timer and returns a boolean (true if time has elapsed, false otherwise).
 */
bool
timeHasElapsed(double *timer, bool realTime, timeType type, double amount)
{
    bool result = false;
    double time = 0;

    /*
     * Check if the time is based on real or game time and give value to time
     * accordingly.
     */
    if (realTime) {
        time = timeGetRealTime();
    }
    else {
        time = timeGetGameTime();
    }

    /* Test if time has elapsed. */
    switch (type) {
        case DAY:
            if (time > *timer + amount * 86400) {
               result = true;
            }
            break;
        case HOUR:
            if (time > *timer + amount * 3600) {
               result = true;
            }
            break;
        case MINUTE:
            if (time > *timer + amount * 60) {
               result = true;
            }
            break;
        case SECOND:
            if (time > *timer + amount) {
                result = true;
            }
            break;
        case MILLISECOND:
            if (time > *timer + amount / 1000) {
                result = true;
            }
            break;
    }

    /*
     * Update the value of the timer to the current time according to whether
     * the time was based on real or game time.
     */
    if (realTime && result) {
        *timer = timeGetRealTime();
    }
    else if (!realTime && result) {
        *timer = timeGetGameTime();
    }

    return result;
}
