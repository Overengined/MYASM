#include <string.h>
#include "sds.h"
#include <stdbool.h>
#include <stdlib.h>

/**
 * Looks for the end of a comment.
 * @param indexStart : Index of the start of the comment.
 * @param str : String containing the comment.
 * @return : the index of the next LF or -1 if there is no LF
 */
int findEndComment(int indexStart, char *str) {
    int index = indexStart;
    while (str[index]  != '\0') {
        if (str[index] == '\n') {
            return index;
        }
        index++;
    }

    return -1;
}

/**
 * Is character passed a white space.
 * @pram c : Char that we want to qualify.
 * @return : true if c is a white space and false otherwhise.
 */
bool isWhiteSpace(char c) {
    return c == '\n'
        || c == ' ';
}

/**
     * This function collapses multiple consecutive spaces in the string s and all lines beginning with # (comments)
     * @param s input string to process
     * @return otp : processed string with collapsed spaces an removed comments
     */
char* prepare(char *s, bool verbose) {
    sds content = sdsnew(s);
    long long int len = strlen(content);

    if (verbose) {
        printf("[CLEANER]>[INFO]: preparing string of length %lld\n", len);
        printf("[CLEANER]>[INFO]: original string:\n%s\n", content);
    }

    long long int writeIndex = 0;
    bool previousIsSpace = false;
    
    // Removes extra white spaces and comments
    for (long long int readIndex = 0; readIndex < len; readIndex++) {
        char c = content[readIndex];

        // reduces the white spaces
        if (isWhiteSpace(c)) {
            if (verbose) {
                printf("[CLEANER]>[INFO]: found white space at %lld\n", readIndex);
            }
            if (previousIsSpace) {
                if (verbose) {
                    printf("[CLEANER]>[INFO]: skipping white space\n>>>%lld\n", readIndex);
                }

                // Removes spaces at the end
                if (c == '\n' && content[readIndex - 1] != '\n') {
                    content[readIndex - 1] = '\n';
                }
                continue;
            }
            previousIsSpace = true;
        } else {
            previousIsSpace = false;
        }

        // Skips the comments
        if (c == '#') {
            if (verbose) {
                printf("[CLEANER]>[INFO]: found comment at %lld\n", readIndex);
            }

            readIndex = findEndComment(readIndex, content);

            if (verbose) {
                printf("[CLEANER]>[INFO]: end of comment at %lld\n", readIndex);
            }

            if (readIndex == -1) {
                if (verbose) {
                    printf("[CLEANER]>[INFO]: end of string found before LF of comment\n");
                }
                break;
            }

            if (content[writeIndex - 1] != '\n' && writeIndex - 1 >= 0) {
                if (verbose) {
                    printf("[CLEANER]>[INFO]: adding LF instead of comment\n");
                }

                if (isWhiteSpace(content[writeIndex - 1])) {
                    if (verbose) {
                        printf("[CLEANER]>[INFO]: clearing space before comment\n");
                    }

                    content[writeIndex - 1] = '\n';
                }
                else {
                    content[writeIndex++] = '\n';
                }
            }
            previousIsSpace = true;
            continue;
        }

        content[writeIndex++] = c;
    }
    content[writeIndex] = '\0';
    sdsupdatelen(content);
    if (verbose){
        printf("[CLEANER]>[INFO]: modified string:\n%s\n", content);
    }
    return content;
}
    
