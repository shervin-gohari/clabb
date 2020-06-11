#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <assert.h>

#include "hashfunc.h"

extern const int HASHVEKSIZE;
extern const char * HASHNAME;

int main() {
	Nod ** myhashvek = malloc(sizeof(Nod *) * HASHVEKSIZE);
	
	init(myhashvek);

    char * filename = "tab_tracks.txt";
	FILE * fh = fopen(filename, "r");
	
	if (fh == NULL) {
		fprintf(stderr, "kunde inte öppna %s\n", filename);
		return 1;
	}
	
	// skapa en katalog för resultatfilerna om den inte redan finns
	struct stat statcheck = {0};
	if (stat("resultat", &statcheck) == -1) {
		mkdir("resultat", 0700);
	}
	
	char name_get[80] = "resultat/";
	strcat(name_get, HASHNAME);
	strcat(name_get, "-uppslagning.dat");
	FILE * fh_get = fopen(name_get, "w");
	fprintf(fh_get, "%s\n", HASHNAME);

    ////////////////////////////////////////////////////////////////////////////////
    //
	// fyll upp hashtabellen med låtar
    //
	char buffer[1024];
	long k = 0;
	
	while (fgets(buffer, sizeof(buffer), fh)) {
		int sep = 0;
		
		while (buffer[sep] != '\t') {
			sep++;
		}
		
		char artist[512];
		char title[512];
		
		memset(artist, '\0', 512);
		strncpy(artist, buffer, sep);
		
		strncpy(title, buffer + sep + 1, 512);
		
		for (unsigned int i = 0; i < sizeof(title); i++) {
			if (title[i] == '\n') {
				title[i] = '\0';
				break;
			}
		}
		
		//printf("spårutskrift i while: artist = '%s'\n", artist);
		//printf("spårutskrift i while: title = '%s'\n\n", title);
		
		put(myhashvek, artist, title);
		
		k++;
		
		if (k % 50000 == 0) {
            // En spårutskrift för att se att låtar läses in
			//printf("satt in %ld låtar\n", k);  
		}
		
		if (k % 1000 == 0) {
			// gör en uppslagning
			clock_t start = clock();
			
			for (int i = 0; i < 100; i++) {
				get(myhashvek, "Pet Shop Boys");
			}
			
			clock_t end = clock();
			double time = (((double) end) - ((double) start)) / CLOCKS_PER_SEC;
			
			fprintf(fh_get, "%ld\t%lf\n", k, time);
		}
	}
	
	fclose(fh);
	fclose(fh_get);
	
    ////////////////////////////////////////////////////////////////////////////////
    //
	// Kollisionsräkning
    //

	// troliggör att hashtabellen fungerar
	char * expected = "Miserablism (2001 Digital Remaster)";
	char * found = get(myhashvek, "Pet Shop Boys");
	assert(strcmp(expected, found) == 0);           // Det bör finnas en nyckel i krocklistan
	
	// räkna antalet kollisioner och spara ned i en textfil
	char name_collisions[80] = "resultat/";
	strcat(name_collisions, HASHNAME);
	strcat(name_collisions, "-kollisioner.dat");
	fh = fopen(name_collisions, "w");
	fprintf(fh, "%s\n", HASHNAME);
	
	long collisions_total = 0;
	long unique_keys = 0;
	
	for (long i = 0; i < HASHVEKSIZE; i++) {
		if (myhashvek[i] == NULL) {
			continue;
		}
		
		unique_keys++;
		
		long collisions_bucket = 0;
		
		Nod * current = myhashvek[i];
		
		while (current->next != NULL) {
			unique_keys++;
			collisions_bucket++;
			current = current->next;
		}
		
		// spara hashtabellens indexvärde och antalet kollisioner till kollisioner.txt
		fprintf(fh, "%ld\t%ld\n", i, collisions_bucket);
		
		collisions_total += collisions_bucket;
	}
	
	fclose(fh);

    ////////////////////////////////////////////////////////////////////////////////
    //
	// Testar uppslaggning av Pet Shop Boys
    char * s = get(myhashvek, "Pet Shop Boys");
 	printf("Pet Shop Boys song is %s\n", s);

	// skriv ut kollisionslistan för Pet Shop Boys
	Nod * list_root = myhashvek[tilpro_hash("Pet Shop Boys")];
	printlist(list_root);
	
	// mät tiden det tar att slå upp ett visst element och spara ned i en textfil
	char name_gets[80] = "resultat/";
	strcat(name_gets, HASHNAME);
	strcat(name_gets, "-uppslagningar.dat");
	fh = fopen(name_gets, "w");
	fprintf(fh, "%s\n", HASHNAME);
	
	// for (long n = 1; n < 500; n++) {                // Slinga med färre uppslagningar
	for (long n = 10000; n < 1000000; n += 10000) {

		printf("kör och mäter get(...) n = %ld gånger\n", n);
		
		clock_t start = clock();
	
		for (int i = 0; i < n; i++) {
			get(myhashvek, "Pet Shop Boys");
		}
	
		clock_t end = clock();
		double time = (((double) end) - ((double) start)) / CLOCKS_PER_SEC;
		
		//spara n och hur lång tid det tog att göra n hämtningar till uppslagning.txt
		fprintf(fh, "%ld\t%lf\n", n, time);
	}
	fclose(fh);
	
	printf("totalt %ld unika nycklar och %ld kollisioner\n", unique_keys, collisions_total);
    return 0;
    
    
}
