/*
 * Author: YOAN BERNATCHEZ
 * Date: 2020-09-23
 *
 * This file provides the user with functions to manipulate files. For
 * example, it provides a safer and customized way to close files. It
 * also contain a basic word finding function and a file modification
 * function.
 */

#include <stdlib.h>
#include <string.h>
#include "file_utilities.h"

/*
 * Tries to find a word in a file and if successful, returns the position of
 * the cursor after the word.
 */
int
eng_file_get_index_after_string (const char *file_name, const char *word)
{
    char c = '+';
    int index = 0;
    int word_length = strlen (word);

    FILE *file = fopen (file_name, "r");

    if (file != NULL) {
        /*
         * Essentially, until the end of file, we search for the
         * first letter in word. Once that letter is found, we get the
         * next letter in the file and compare it to the next letter in
         * the word. If they correspond, we keep going with the next
         * letters, if it does not correspond, we go back to searching
         * for the first letter in word.
         */
        for (int i = 0; i < word_length && !feof (file); /* Empty. */ ) {
            c = fgetc (file);
            (word[i] == c) ? i++ : i = 0;
        }

        index = ftell (file);

        /* Return -1 if the word wasn't found. */
        if (feof (file))
            index = -1;

        file = eng_file_close_file (file);
    }
    else {
        index = -1;
        printf("Error: Could not open file %s\n", file_name);
    }

    if (index < 0)
        printf("Error: Could not locate \"%s\" in %s\n", word, file_name);

    free ((char*) word);

    return index;
}

/*
 * Removes all characters in a file between startIndex and endIndex and
 * inserts text where the data was removed.
 */
bool
eng_file_replace_with_string (const char *file_name, const char *text,
                              int start_index, int end_index)
{
    bool result = false;
    bool is_text_inserted = false;
    const char *temp_file_name = "temp.txt";
    char c = '!';

    /* Open files. */
    FILE *file = fopen (file_name, "r");
    FILE *temp_file = fopen (temp_file_name, "w");

    /* Cut and replace the file characters. */
    if (file != NULL && temp_file != NULL) {
        while (!feof (file)) {
            c = fgetc (file);

            if (ftell (file) <= start_index && !feof (file))
                fputc (c, temp_file);
            else if (!is_text_inserted) {
                fputs (text, temp_file);
                is_text_inserted = true;
            }

            if (ftell (file) > end_index && !feof (file))
                fputc (c, temp_file);
        }

        result = true;
    }

    /* Close files if they were opened. */
    file = eng_file_close_file (file);
    temp_file = eng_file_close_file (temp_file);

    /* Temp file becomes the new file. */
    if (!file && !temp_file) {
        remove (file_name);
        rename (temp_file_name, file_name);
    }

    free ((char*) temp_file_name);
    free ((char*) text);

    return result;
}

/*
 * Safely closes a file if it was open.
 * This function can be called back to back safely, which is why it was
 * created.
 */
FILE *
eng_file_close_file (FILE *file)
{
    if (file != NULL) {
        fclose (file);
        file = NULL;
    }

    return file;
}
