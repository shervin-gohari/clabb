#include "hashfunc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

#include <inttypes.h>

//const int HASHVEKSIZE = 1048576;  // 2^20 - Run 1
//const int HASHVEKSIZE = 2097152;  // 2^21 - Run 2
//const int HASHVEKSIZE = 4194304;  // 2^22 - Run 3
//const int HASHVEKSIZE = 8388608;  // 2^23 - Run 4
const int HASHVEKSIZE = 145310;
//const int HASHVEKSIZE= 16777216;    // 2^24 - Run 5


void put(Nod ** hashtable, char * key, char * value) {
  uint32_t hashedKey = tilpro_hash(key);

  if (* (hashtable+hashedKey) == NULL){                                //Kollar om det finns ngt på idx 
    * (hashtable+hashedKey) = buildNod(key, value);                    //Om inte, lägger till en nod med angivna värden
  }

  else{           
    Nod * tmp = search(* (hashtable+hashedKey), key);                  //Om det finns hämtar vi noden, för nyckeln
    if (!tmp){                                                         //Om x = 0 kommer den ret 1 (dvs tvärtom)
      insertnod(&*(hashtable+hashedKey), buildNod(key, value));        //Dvs om vi hinnar den, lägger vi till ett en nod på adressen
    }
    else{
      strcpy(tmp -> name, value);                                      //Om vi redan har ett värde på adressen, skriver vi över det gamla värdet. 
    }
  }
}

/*get tar hashtabellen och en sträng key som parametrar och returnerar NULL om key inte finns, 
annars returneras värdet associerat med key. 
get räknar ut hashindex för key med tilpro_hash och 
söker där i den dubbellänkade listan efter key.*/


char * get(Nod ** hashtable, char * key) {
  uint32_t hashedKey = tilpro_hash(key);

  if (* (hashtable+hashedKey)){                                        //Om det finnns ngt på den pekade adressen, hämter vi det och retunerar värdet 
    Nod * tmp = search(* (hashtable+hashedKey), key);
    return tmp->name;
  }
  else{
    return NULL;                  
  }
}

/* init itererar genom hashtabellen och sätter alla index till NULL. 
Det går att lösa med en for-loop som går från 0 till HASHVEKSIZE 
men det finns även en funktion memset som kan användas.*/

void init(Nod ** vek) {
  for(int counter = 0; counter < ((HASHVEKSIZE)); counter++){
    *(vek+counter) = NULL;
  }
}

// Printar varje plats i hashtabellen
// Hashtabellen består av pekare som i sin tur pekar på pekare till noderna
void printTable(Nod **hashtable){
  for(int counter = 0; counter < ((HASHVEKSIZE)); counter++){
    if(*(hashtable+counter) != NULL && (*(hashtable+counter))->next){
      printlist(*(hashtable+counter));
      printf("\n");
    }
  }
}

void freemem(Nod **hashtable){
  for(int counter = 0; counter < ((HASHVEKSIZE)); counter++){
    if (*(hashtable+counter) != NULL){
        removelist(*(hashtable+counter));
      }
    }
  }





