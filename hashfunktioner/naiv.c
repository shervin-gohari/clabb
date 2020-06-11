#include <stdint.h>
#include <stdlib.h>

extern const int HASHVEKSIZE;
const char * HASHNAME = "naiv";

uint32_t tilpro_hash(const char * s) {
	uint32_t hash = 0;
	int c;

	while (c = *s++) {         //  se föreläsning F7 om hashning 
		hash = hash << 5;  //  for c in s:
		hash += c;         //      result = result*32 + ord(c) 
	}
	
	return hash & (HASHVEKSIZE - 1);
}