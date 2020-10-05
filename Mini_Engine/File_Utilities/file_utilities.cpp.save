/*
 * Author: YOAN BERNATCHEZ
 * Date: 2020-09-23
 *
 * This file provides the user with functions to manipulate files. For
 * example, it provides a safer and customized way to close files. It
 * also contain a basic word finding function and a file modification
 * function.
 */

#include <string.h>
#include "file_utilities.h"

/*
 * Tries to find a word in a file and if successful, returns the position of
 * the cursor after the word.
 */
int
fileGetIndexAfterString(const char *fileName, const char *word)
{
    char c = '+';
    int index = 0;
    int wordLength = strlen(word);

    FILE *file = fopen(fileName, "r");

    if (file != NULL) {
        /*
         * Essentially, until the end of file, we search for the
         * first letter in word. Once that letter is found, we get the
         * next letter in the file and compare it to the next letter in
         * the word. If they correspond, we keep going with the next
         * letters, if it does not correspond, we go back to searching
         * for the first letter in word.
         */
        for (int i = 0; i < wordLength && !feof(file); /* Empty. */ ) {

            c = fgetc(file);

            (word[i] == c) ? i++ : i = 0;
        }

        index = ftell(file);

        /* Return -1 if the word wasn't found. */
        if (feof(file)) index = -1;

        file = fileCloseFile(file);
    }
    else {
        index = -1;
        printf("Error: Could not open file %s\n", fileName);
    }

    if (index < 0) {
        printf("Error: Could not locate \"%s\" in %s\n", word, fileName);
    }

    return index;
}

/*
 * Removes all characters in a file between startIndex and endIndex and
 * inserts text where the data was removed.
 */
bool
fileReplaceWithString(const char *fileName, const char *text,
                           int startIndex, int endIndex)
{
    bool result = false;
    bool textIsInserted = false;
    const char *tempFileName = "temp.txt";
    char c = '!';

    /* Open files. */
    FILE *file = fopen(fileName, "r");
    FILE *tempFile = fopen(tempFileName, "w");

    /* Cut and replace the file characters. */
    if (file != NULL && tempFile != NULL) {
        while (!feof(file)) {
            c = fgetc(file);

            if (ftell(file) <= startIndex && !feof(file)) {
                fputc(c, tempFile);
            }
            else if (!textIsInserted) {
                fputs(text, tempFile);
                textIsInserted = true;
            }

            if (ftell(file) > endIndex && !feof(file)) {
                fputc(c, tempFile);
            }
        }

        result = true;
    }

    /* Close files if they were opened. */
    file = fileCloseFile(file);
    tempFile = fileCloseFile(tempFile);

    /* Temp file becomes the new file. */
    if (!file && !tempFile) {
        remove(fileName);
        rename(tempFileName, fileName);
    }

    return result;
}

/*
 * Safely closes a file if it was open.
 * This function can be called back to back safely, which is why it was
 * created.
 */
FILE *
fileCloseFile(FILE *file)
{
    if (file != NULL) {
        fclose(file);
        file = NULL;
    }

    return file;
}
