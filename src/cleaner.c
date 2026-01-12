#include <string.h>
#include "sds.h"
#include <stdlib.h>
#include "MYASM.h"
#include <stdio.h>

/**
     * This function collapses multiple consecutive spaces in the string s and all lines beginning with #
     * @param s input string to process
     * @return otp : processed string with collapsed spaces an removed comments
     */
char* prepare(char *s) {
    
    char *read = s;
    
    //char *otp = (char*)malloc(strlen(s) + 1); // allocate memory for output string
    sds otp = sdsempty(); // use sds for dynamic string handling

    sds content = sdsnew(s);

    // fsm avec goto ??
    long long int len = strlen(content);
    if (verbose) {
        printf("[CLEANER]>[INFO]: preparing string of length %lld\n", len);
        printf("[CLEANER]>[INFO]: original string:\n%s\n", content);
    }

    // for loop for all the chars in the string
    long long i = 0;
    S0 :
    if (i >= len) goto END;
    if (i < len && content[i] == ' ') {
        sdscatlen(otp, " ", 1);
        i ++;
        goto E1;
    }
    if (i < len && content[i] == '#') {
        i ++;
        goto C1;
    }
    if (i < len && content[i] != ' ' && content[i] != '#') {
        sdscatlen(otp, &content[i], 1);   // bot insisted on using catlen instaed of cat, don't ask me why 
        i ++;
        goto S0;
    }
    E1 :
    if (i >= len) goto END;
    if (i < len && content[i] == ' ') {
        i ++;
        goto E1;
    }
    if (i < len && content[i] == '#') {
        i ++;
        goto C1;
    }  
    C1 :
    if (i >= len) goto END;
    if (i < len && content[i] != '\n') {
        i ++;
        goto C1;
    }
    if (i < len && content[i] == '\n') {
        sdscat(otp, "\n");
        i ++;
        goto S0;
    }
END:
    return otp;
}




    
