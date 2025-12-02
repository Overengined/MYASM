#include <string.h>
#include "sds.h"
#include <stdbool.h>

/**
     * This function collapses multiple consecutive spaces in the string s and all lines beginning with #
     * @param s input string to process
     * @return otp : processed string with collapsed spaces an removed comments
     */
char* collapse_spaces(char *s, bool verbose) {
    
    char *read = s;
    
    char *otp = (char*)malloc(strlen(s) + 1); // allocate memory for output string
    char *write = otp;

    sds content = sdsnew(s);

    // fsm avec goto ??
}
    
