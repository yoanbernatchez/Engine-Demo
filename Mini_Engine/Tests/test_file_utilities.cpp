#include <assert.h>
#include <string.h>
#include "test_file_utilities.h"
#include "../File_Utilities/file_utilities.h"

static void testFileGetIndexAfterString(void);
static void testFileReplaceWithString(void);

void
testFileUtilities(void)
{
    testFileGetIndexAfterString();
    testFileReplaceWithString();
}

static void
testFileGetIndexAfterString(void)
{
    int index = 0;
    char *fileName = "Mini_Engine/Tests/indexTest.txt";

    /* Simple test. */
    index = fileGetIndexAfterString(fileName, "test{");
    assert(index == 5);

    /* Testing with line feed (OS dependent). */
#ifdef _WIN32
    index = fileGetIndexAfterString(fileName, "line feed");
    assert(index == 26);
#elif __APPLE__ || __linux__ || __unix__
    index = fileGetIndexAfterString(fileName, "line feed");
    assert(index == 25);
#endif

    /* Word not found. */
    index = fileGetIndexAfterString(fileName, "qwerty");
    assert(index == -1);
}

static void
testFileReplaceWithString(void)
{
    FILE *file;
    int bufferSize = 80;
    char buffer[bufferSize];
    char c = '!';
    char *fileName = "Mini_Engine/Tests/replaceTest.txt";

    /* Simple pasting test including line feed with indexes being 0 and 0. */
    fileReplaceWithString(fileName, "line\nfeed", 0, 0);

    file = fopen(fileName, "r");

    for (int i = 0; i < bufferSize - 1; i++) {
        c = fgetc(file);
        if (!feof(file)) {
            buffer[i] = c;
        }
        else {
            buffer[i] = '\0';
            break;
        }
    }

    assert(strcmp(buffer, "line\nfeed") == 0);

    file = fileCloseFile(file);
    buffer[0] = '\0';

    /* Test with beginning index out of bounds. */
    fileReplaceWithString(fileName, "new text", -10, 5);

    file = fopen(fileName, "r");

    for (int i = 0; i < bufferSize - 1; i++) {
        c = fgetc(file);
        if (!feof(file)) {
            buffer[i] = c;
        }
        else {
            buffer[i] = '\0';
            break;
        }
    }

    assert(strcmp(buffer, "new text\nfeed") == 0);

    file = fileCloseFile(file);
    buffer[0] = '\0';

    /* Test with end index out of bounds. */
    fileReplaceWithString(fileName, "only text", 0, 50);

    file = fopen(fileName, "r");

    for (int i = 0; i < bufferSize - 1; i++) {
        c = fgetc(file);
        if (!feof(file)) {
            buffer[i] = c;
        }
        else {
            buffer[i] = '\0';
            break;
        }
    }

    assert(strcmp(buffer, "only text") == 0);

    file = fileCloseFile(file);
    buffer[0] = '\0';

    /* Test for deleting the contents of a file. */
    fileReplaceWithString(fileName, "", 0, 50);

    file = fopen(fileName, "r");

    for (int i = 0; i < bufferSize - 1; i++) {
        c = fgetc(file);
        if (!feof(file)) {
            buffer[i] = c;
        }
        else {
            buffer[i] = '\0';
            break;
        }
    }

    assert(strcmp(buffer, "") == 0);

    file = fileCloseFile(file);
    buffer[0] = '\0';
}
