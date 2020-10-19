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
eng_get_real_time (void)
{
    return (double) clock () / CLOCKS_PER_SEC;
}

/*
 * Returns the real clock time in seconds since start of program, affected by
 * a time ratio (game time ratio).
 */
double
eng_get_game_time (void)
{
    return (double) clock () / CLOCKS_PER_SEC * ENG_TIME_RATIO;
}

/* Returns a Time structure with current real time information. */
EngTime
eng_get_real_time_struct (void)
{
    EngTime real_time;
    double current_time = eng_get_real_time ();

    real_time.day = (int) current_time / 86400;
    real_time.hour = (int) (current_time / 3600) % 24;
    real_time.minute = (int) (current_time / 60) % 60;
    real_time.second = (int) current_time % 60;
    real_time.millisecond = (int) (current_time * 1000) % 1000;

    return real_time;
}

/* Returns a Time structure with the current game time information. */
EngTime
eng_get_game_time_struct (void)
{
    EngTime game_time;
    double current_game_time = eng_get_real_time () * ENG_TIME_RATIO;

    game_time.day = (int) current_game_time / 86400;
    game_time.hour = (int) (current_game_time / 3600) % 24;
    game_time.minute = (int) (current_game_time / 60) % 60;
    game_time.second = (int) current_game_time % 60;
    game_time.millisecond = (int) (current_game_time * 1000) % 1000;

    return game_time;
}

/*
 * Tests if a certain amount of time has passed since last checking the
 * timer and returns a boolean (true if time has elapsed, false otherwise).
 */
bool
eng_has_time_elapsed (double *timer, bool real_time, EngTimeType type,
                      double amount)
{
    bool result = false;
    double time = 0;

    /*
     * Check if the time is based on real or game time and give value to time
     * accordingly.
     */
    if (real_time)
        time = eng_get_real_time ();
    else
        time = eng_get_game_time ();

    /* Test if time has elapsed. */
    switch (type) {
    case ENG_DAY:
        if (time > *timer + amount * 86400)
            result = true;
        break;
    case ENG_HOUR:
        if (time > *timer + amount * 3600)
            result = true;
        break;
    case ENG_MINUTE:
        if (time > *timer + amount * 60)
            result = true;
        break;
    case ENG_SECOND:
        if (time > *timer + amount)
            result = true;
        break;
    case ENG_MILLISECOND:
        if (time > *timer + amount / 1000)
            result = true;
        break;
    }

    /*
     * Update the value of the timer to the current time according to whether
     * the time was based on real or game time.
     */
    if (real_time && result)
        *timer = eng_get_real_time ();
    else if (!real_time && result)
        *timer = eng_get_game_time ();

    return result;
}
