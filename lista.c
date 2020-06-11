#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// *padr is the node adress that **padr points to
void insertnod(Nod ** padr, Nod * tobeadded){
  if (padr && *padr){                   // Check if list is empty, if it is, then:
    Nod * tmp = *padr;

    while (tmp -> next){
      tmp = tmp -> next;
    }
    tmp -> next = tobeadded;           // Makes last added element's next-pointer point at the new node
    tobeadded -> prev = tmp;           // The new node's prev-pointer will point at the second last node
  }
  else{
    *padr = tobeadded;                 // Updating head-pointer to point at the new node
  }
}


// tar bort noden toberemoved och letar i listan med header *padr
void removenod(Nod ** padr, Nod * toberemoved){
  if (padr && *padr){
    Nod * tmp = *padr;

    while (tmp != toberemoved){
      tmp = tmp -> next;
      if (tmp == NULL){
        return;
      }
    }
    if (!(tmp -> next) && (!(tmp -> prev))){
      *padr = NULL;
    }
    else if (!(tmp -> next)){
      tmp -> prev -> next = NULL;
    }
    else if(!(tmp -> prev)){
      *padr = tmp -> next;
      tmp -> next -> prev = NULL;
    }
    else{
      tmp -> next -> prev = tmp -> prev;
      tmp -> prev -> next = tmp -> next;
    }
    free(tmp);
  }
}

//skriver ut en nod p (med pekare *p)
void printnod(Nod * p){
  printf("Artist: %s, Song: %s. \n", p->key, p->name);
  //printf("%s\t\t%s\n", p->name, p->key);

}

void printlist(Nod * p){
  Nod * tmp = p;
    while (tmp){
      printnod(tmp);
      tmp = tmp->next;
    }
}

//söker efter nod med nyckeln key i lista med header *p (??)
Nod * search(Nod * p, char * key){
  Nod * tmp = p;
  while (tmp){
    if (strcmp(tmp -> key, key) == 0){
      return tmp;
    }
    tmp = tmp -> next;
  }
  return NULL;
}

void removelist(Nod * p){
  Nod * tmp = p;
  while (tmp->prev != NULL){
    tmp = tmp -> next;
    free(tmp->prev);

  }
  free(tmp);
}

//bygger en nod med innehåll key och name, används
Nod * buildNod(char * key, char * name){
    Nod * p = malloc(sizeof(Nod));
    strcpy(p -> key , key );
    strcpy(p -> name, name);
    return p;
}
