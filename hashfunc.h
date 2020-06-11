#ifndef HASHFUNC_H
#define HASHFUNC_H

#include <stdint.h>
#include "lista.h"    // en headerfil för en modifierad dubbellänkad lista p3

uint32_t tilpro_hash(const char * s) ;

void put(Nod ** hashtable, char * key, char * value);

char * get(Nod ** hashtable, char * key);

void init(Nod ** vek);

void printTable(Nod **hashtable);

void freemem(Nod **hashtable);

#endif
