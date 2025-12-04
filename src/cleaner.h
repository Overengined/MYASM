#ifndef CLEANER_H
#define CLEANER_H
#include "sds.h"
sds sdsnew(const char *init);
extern int verbose;
char* prepare(char *s);

#endif