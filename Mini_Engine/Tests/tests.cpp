#include <stdio.h>
#include "tests.h"
#include "test_window.h"
#include "test_file_utilities.h"
#include "test_character.h"
#include "test_pathfinding.h"
#include "test_chunk.h"

/*
 * TODO: Make a more elaborate unit testing system with warning messages
 *       and logs.
 */

/*
* This function calls all the other test functions
* Returns 1 if all tests work as expected
*/
int engineTestAll(void){
    printf("!---- Testing Begin ----!\n");

    testWindow();
    testFileUtilities();
    testCharacter();
    testChunk();
    testPathfinding();

    printf("!---- Testing End ----!\n");
}
