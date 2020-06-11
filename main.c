#include "hashfunc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern const int HASHVEKSIZE;

int main() {
  Nod ** myhashvek = malloc(sizeof(Nod *) * HASHVEKSIZE);
  init(myhashvek);

  put(myhashvek, "Adam", "123321");
  char * s = get(myhashvek, "Adam");
  printf("Adam -> value = %s expecting Adam\n", s);
  
  // ...
}