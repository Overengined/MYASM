#ifndef MEMGER_H
#define MEMGER_H

extern bool verbose;
int getmem(struct memger *m,long long int index);
struct memger *newmem(long long int size);
int setmem(struct memger *m,long long int index,int value);

#endif