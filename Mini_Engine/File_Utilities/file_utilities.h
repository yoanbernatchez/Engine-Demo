#ifndef FILE_UTILITIES_H_INCLUDED
#define FILE_UTILITIES_H_INCLUDED

#include <stdio.h>
#include <stdbool.h>

/**
 * @brief Tries to find a word in a file and returns the position of the cursor
 *        at the end of it.
 *
 * @param file_name: A string containing the location of the file to be
 *                   scanned.
 * @param word:      The word to search in the file.
 *
 * @return The position of the cursor directly after the word in the file
 *         or -1 if the word was not found.
 */
int eng_file_get_index_after_string (const char *file_name, const char *word);

/**
 * @brief Removes all characters in a file between start_index and end_index
 *        and inserts text where the data was removed.
 *
 * @param file_name:   A string containing the location of the file.
 * @param text:        A string containing text to include between the cut.
 * @param start_index: The index in the file where the cut begins (included).
 * @param end_index:   The index in the file where the cut ends (excluded).
 *
 * @return False on failure, true on success.
 */
bool eng_file_replace_with_string (const char *file_name, const char *text,
                                   int start_index, int end_index);

/**
 * @brief Safely closes a file if it was open.
 *
 * @param file: File to close.
 *
 * @return Closed file's pointer.
 */
FILE * eng_file_close_file (FILE *file);

#endif /* FILE_UTILITIES_H_INCLUDED */
