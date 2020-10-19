#ifndef TIME_H_INCLUDED
#define TIME_H_INCLUDED

/** Affects how fast the game's time is relative to the real world. */
#define ENG_TIME_RATIO 2

#include <stdbool.h>

/** Time types. */
enum EngTimeType{ENG_DAY, ENG_HOUR, ENG_MINUTE, ENG_SECOND, ENG_MILLISECOND};

typedef struct _EngTime {
    int day;
    int hour;
    int minute;
    int second;
    int millisecond;
} EngTime;
/**< Time structure containing time information in hours, minutes, etc. */

/**
 * @return The current real clock time in seconds since the start of the
 *         program.
 *
 * @sa eng_get_game_time ()
 */
double eng_get_real_time (void);

/**
 * @return The real clock time in seconds since start of program, affected by
 *         a time ratio (game time ratio).
 *
 * @sa eng_get_real_time ()
 */
double eng_get_game_time (void);

/**
 * @brief Returns a Time structure that contains current real time information.
 *
 * @return Time structure that contains real time data in the form of days,
 *         hours, minutes, seconds and milliseconds.
 *
 * @sa eng_get_game_time_struct ()
 */
EngTime eng_get_real_time_struct (void);

/**
 * @brief Returns a Time structure that contains current game time information.
 *
 * @return Time structure that contains game time data in the form of days,
 *         hours, minutes, seconds and milliseconds.
 *
 * @sa eng_get_real_time_struct()
 */
EngTime eng_get_game_time_struct (void);

/**
 * @brief Tests if a certain amount of time has passed since last checking the
 *        timer in parameters.
 *
 * @param timer:     Pointer to a double representing a timer with which we
 *                   will test if a certain amount of time has elapsed and
 *                   update if so.
 * @param real_time: Boolean deciding if we check for real time or game time.
 * @param type:      The time type to check for, SECONDS, MILLISECONDS, etc.
 * @param amount:    Amount of (type: SECONDS, MILLISECONDS, etc) to test for.
 *
 * @return True if the amount of (type: SECONDS, MILLISECONDS, etc) has passed
 *         since last calling timer, false otherwise.
 */
bool eng_has_time_elapsed (double *timer, bool real_time,
                           EngTimeType type, double amount);

#endif /* TIME_H_INCLUDED */
