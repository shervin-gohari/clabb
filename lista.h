#ifndef LISTA_H
#define LISTA_H

struct nod {
    char name[512];
    char key[512];
    struct nod * next;
    struct nod * prev;
};
typedef struct nod Nod;

void insertnod(Nod ** padr, Nod * tobeadded);
void removenod(Nod ** padr, Nod * toberemoved);
void printnod(Nod * p);
void printlist(Nod * p);
Nod * search(Nod * p, char * key);
Nod * buildNod(char * key, char * name);
void removelist(Nod * p);


#endif
