#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "hashfunc.h"


const int HASHVEKSIZE2 = 2097152;

struct artist {
  char artistid[20];
  char artistname[400];
  char songtitle[300];
  double length;
  int year;
};

typedef struct artist Artist;


//  Läser artister från filename och lägger dem i artistarray
//  returnerar antalet inlästa artister
int readartists(char * filename, Artist * artistarray) {
  char linebuffer[425];

  FILE * fil = fopen(filename, "r");

  int currentartist = 0;

  while (fgets (linebuffer, 425, fil) != NULL) {

    Artist * artist = artistarray + currentartist;

    int i = 0;
    int j = 0;
    // kolumner är TAB-separerade
    while (linebuffer[i] != '\t')
      i++;

    strncpy(artist -> artistid, linebuffer, j);

    i += 1;
    j = i;
    while (linebuffer[i] != '\t')
      i++;

    strncpy(artist -> artistname, linebuffer + j, i - j);

    i += 1;
    j = i;
    while (linebuffer[i] != '\t')
      i++;

    strncpy(artist -> songtitle, linebuffer + j, i - j);

    i += 1;
    // atof - array to float
    artist -> length = atof(linebuffer + i);

    while (linebuffer[i] != '\t')
      i++;

    i += 1;
    // atoi - array to integer
    artist -> year = atoi(linebuffer + i);

    currentartist += 1;
  }
  return currentartist;
}

int main() {
  Artist * artister = malloc(sizeof(Artist) * 1000000);

  int antalartister = readartists("sang-artist-data.txt", artister);

  Nod ** myhashvek = malloc(sizeof(Nod *) * HASHVEKSIZE2);
  init(myhashvek);

  int i = 0;
  for (i = 0; i < antalartister; i += 1) {
    put(myhashvek, artister[i].artistname, artister[i].songtitle);
  }

  printTable(myhashvek);

  char * s = get(myhashvek, "Sean Cronin");
  printf("Sean Cronin song is %s\n", s);

  free(artister);
  freemem(myhashvek);
  free(myhashvek);


  //printTable(myhashvek);
  return 0;
}
