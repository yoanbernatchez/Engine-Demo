#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "test_file_utilities.h"
#include "../File_Utilities/file_utilities.h"

static void test_file_get_index_after_string (void);
static void test_file_replace_with_string (void);

void
test_file_utilities (void)
{
    printf("\n> Unit testing file utilities functions...\n\n");
    test_file_get_index_after_string ();
    test_file_replace_with_string ();
}

static void
test_file_get_index_after_string (void)
{
    int index = 0;
    char *file_name = "Mini_Engine/Tests/indexTest.txt";

    /* Simple test. */
    index = eng_file_get_index_after_string (file_name, "test{");
    assert (index == 5);

    /* Testing with line feed (OS dependent). */
#ifdef _WIN32
    index = eng_file_get_index_after_string (file_name, "line feed");
    assert (index == 26);
#elif __APPLE__ || __linux__ || __unix__
    index = eng_file_get_index_after_string (file_name, "line feed");
    assert (index == 25);
#endif

    /* Word not found. */
    index = eng_file_get_index_after_string (file_name, "qwerty");
    assert (index == -1);
}

static void
test_file_replace_with_string (void)
{
    FILE *file;
    int buffer_size = 80;
    char buffer[buffer_size];
    char c = '!';
    char *file_name = "Mini_Engine/Tests/replaceTest.txt";

    /* Simple pasting test including line feed with indexes being 0 and 0. */
    eng_file_replace_with_string (file_name, "line\nfeed", 0, 0);

    file = fopen (file_name, "r");

    for (int i = 0; i < buffer_size - 1; i++) {
        c = fgetc (file);
        if (!feof (file))
            buffer[i] = c;
        else {
            buffer[i] = '\0';
            break;
        }
    }

    assert (strcmp (buffer, "line\nfeed") == 0);

    file = eng_file_close_file (file);
    buffer[0] = '\0';

    /* Test with beginning index out of bounds. */
    eng_file_replace_with_string (file_name, "new text", -10, 5);

    file = fopen (file_name, "r");

    for (int i = 0; i < buffer_size - 1; i++) {
        c = fgetc (file);
        if (!feof (file))
            buffer[i] = c;
        else {
            buffer[i] = '\0';
            break;
        }
    }

    assert (strcmp (buffer, "new text\nfeed") == 0);

    file = eng_file_close_file (file);
    buffer[0] = '\0';

    /* Test with end index out of bounds. */
    eng_file_replace_with_string (file_name, "only text", 0, 50);

    file = fopen (file_name, "r");

    for (int i = 0; i < buffer_size - 1; i++) {
        c = fgetc (file);
        if (!feof (file))
            buffer[i] = c;
        else {
            buffer[i] = '\0';
            break;
        }
    }

    assert (strcmp (buffer, "only text") == 0);

    file = eng_file_close_file (file);
    buffer[0] = '\0';

    /* Test for deleting the contents of a file. */
    eng_file_replace_with_string (file_name, "", 0, 50);

    file = fopen (file_name, "r");

    for (int i = 0; i < buffer_size - 1; i++) {
        c = fgetc (file);
        if (!feof (file))
            buffer[i] = c;
        else {
            buffer[i] = '\0';
            break;
        }
    }

    assert (strcmp (buffer, "") == 0);

    free (file_name);
    file = eng_file_close_file(file);
    buffer[0] = '\0';
}
