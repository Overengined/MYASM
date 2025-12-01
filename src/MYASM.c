#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <cleaner.c>

int main(int argc, char const *argv[])
{
    bool verbose = false;
    if (argc == 1 || argc > 3) {
        printf("TERM : usage is \n myasm <file name> -v");
        return 1;
    };

    printf(argv[2]);
    
    if (argc == 3 && strcmp(argv[2], "-v") == 0) {
        printf("MYASM : version 2.0 \n");
        verbose = true;
    }

    FILE* file;

    file = fopen(argv[1],"r");

    // Check if file opened successfully
    if (file == NULL) {
        printf("TERM : Could not open file %s\n", argv[1]);
        return 1;
    }

    // load the file content as a string
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    char* file_content = (char*)malloc(file_size + 1);
    fread(file_content, 1, file_size, file);
    file_content[file_size] = '\0';
    fclose(file);

    // prove that file_content is indeed a string
    if (verbose == true) {
    printf("File content:\n%s\n", file_content);
    };


    return 0;
}
