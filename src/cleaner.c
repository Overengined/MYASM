#include <string.h>
#include "sds.h"
#include <stdbool.h>
#include <stdlib.h>

/**
     * This function collapses multiple consecutive spaces in the string s and all lines beginning with #
     * @param s input string to process
     * @return otp : processed string with collapsed spaces an removed comments
     */
char* prepare(char *s, bool verbose) {
    
    char *read = s;
    
    //char *otp = (char*)malloc(strlen(s) + 1); // allocate memory for output string
    sds otp = sdsempty(); // use sds for dynamic string handling
    char *write = otp;

    sds content = sdsnew(s);

    // fsm avec goto ??
    long long int len = strlen(content);
    if (verbose == true) {
        printf("[CLEANER]>[INFO]: preparing string of length %lld\n", len);
        printf("[CLEANER]>[INFO]: original string:\n%s\n", content);
    }

}
    
