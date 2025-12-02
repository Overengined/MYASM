#ifndef CLEANER_H
#define CLEANER_H
#include "sds.h"
sds sdsnew(const char *init);
extern bool verbose;
char *collapse_spaces(char *s,bool verbose);

#endif