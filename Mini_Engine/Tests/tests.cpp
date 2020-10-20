/*===========================================================================*/
/* File: tests.cpp                                                           */
/* Author: YOAN BERNATCHEZ                                                   */
/* Created On: 2020-07-29                                                    */
/* Developed Using: SDL2                                                     */
/* Function: This file manages all the unit tests for the functions used by  */
/*           the engine.                                                     */
/*===========================================================================*/

#include <stdio.h>
#include "tests.h"
#include "test_hud.h"
#include "test_file_utilities.h"
#include "test_character.h"
#include "test_pathfinding.h"
#include "test_chunk.h"
#include "test_objects.h"
#include "test_tile.h"

/*
 * TODO: Make a more elaborate unit testing system with warning messages
 *       and logs.
 */

/*
 * This function calls all the other test functions
 * Returns 1 if all tests work as expected
 */
void
eng_test_all (void)
{
    printf ("!---- ENGINE FUNCTION UNIT TESTING BEGIN ----!\n");

    test_hud ();
    test_file_utilities ();
    test_character ();
    test_chunk ();
    test_pathfinding ();
    test_objects ();
    test_tile ();

    printf ("\n!---- ENGINE FUNCTION UNIT TESTING END ----!\n\n"
            "The error messages above are normal and generated by function "
            "testing.\nFunction testing affects the initial loading time of "
            "the engine.\nFunction testing can be turned off by commenting "
            "the test function in main.\nThe true error messages during "
            "execution will be shown bellow.\n"
            "\n!------------------------------------------!\n\n");
}
