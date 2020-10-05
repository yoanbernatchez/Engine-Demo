#ifndef FILE_UTILITIES_H_INCLUDED
#define FILE_UTILITIES_H_INCLUDED

#include <stdio.h>
#include <stdbool.h>

/**
 * @brief Tries to find a word in a file and returns the position of the cursor
 *        at the end of it.
 *
 * @param fileName: A string containing the location of the file to be scanned.
 * @param word:     The word to be searched in the file.
 *
 * @return The position of the cursor directly after the word in the file
 *         or -1 if the word was not found.
 */
int fileGetIndexAfterString(const char *fileName, const char *word);

/**
 * @brief Removes all characters in a file between startIndex and endIndex and
 * inserts text where the data was removed.
 *
 * @param fileName:   A string containing the location of the file.
 * @param text:       A string containing text to include between the cut.
 * @param startIndex: The index in the file where the cut begins (included).
 * @param endIndex:   The index in the file where the cut ends (excluded).
 *
 * @return False on failure, true on success.
 */
bool fileReplaceWithString(const char *fileName, const char *text, int startIndex, int endIndex);

/**
 * @brief Safely closes a file if it was open.
 *
 * @param file: File pointer to close.
 *
 * @return Closed file's pointer.
 */
FILE * fileCloseFile(FILE *file);

#endif /* FILE_UTILITIES_H_INCLUDED */
