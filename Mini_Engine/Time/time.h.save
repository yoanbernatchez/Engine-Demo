#ifndef TIME_H_INCLUDED
#define TIME_H_INCLUDED

/** @def Affects how fast the game's time is relative to the real world. */
#define TIMERATIO 2

#include <stdbool.h>

/** Time types. */
enum timeType{DAY, HOUR, MINUTE, SECOND, MILLISECOND};

typedef struct _time
{
    int day;
    int hour;
    int minute;
    int second;
    int millisecond;
} Time;
/**< Time structure containing time information in days, hours, minutes. */

/**
 * @return The current real clock time in seconds since the start of the
 *         program.
 *
 * @sa getGameTime()
 */
double timeGetRealTime(void);

/**
 * @return The real clock time in seconds since start of program, affected by
 *         a time ratio (game time ratio).
 *
 * @sa getRealTime()
 */
double timeGetGameTime(void);

/**
 * @brief Updates a Time structure to the current real time.
 *
 * @param realTime:  Time structure in which we store real time in the form of
 *                   days, hours, minutes, seconds and milliseconds.
 *
 * @sa timeUpdateIngameTime()
 */
void timeUpdateRealTime(Time *realTime);

/**
 * @brief Updates a Time structure to the current game time.
 *
 * @param gameTime:  Time structure in which we store game time in the form of
 *                   days, hours, minutes, seconds and milliseconds.
 *
 * @sa timeUpdateRealTime()
 */
void timeUpdateIngameTime(Time *gameTime);

/**
 * @brief Tests if a certain amount of time has passed since last checking the
 *        timer in parameters.
 *
 * @param timer:     Pointer to a double representing a timer with which we
 *                   will test if a certain amount of time has elapsed and
 *                   update if so.
 * @param realTime:  Boolean deciding if we work with real time or game time.
 * @param type:      The time type to check for, SECONDS, MILLISECONDS, etc.
 * @param amount:    Amount of (type: SECONDS, MILLISECONDS, etc) to test for.
 *
 * @return True if the amount of (type: SECONDS, MILLISECONDS, etc) has passed
 *         since last calling timer, false otherwise.
 */
bool timeHasElapsed(double *timer, bool realTime, timeType type,
                    double amount);

#endif /* TIME_H_INCLUDED */
