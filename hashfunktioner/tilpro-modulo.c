#include <stdint.h>
#include <stdlib.h>

extern const int HASHVEKSIZE;
const char * HASHNAME = "tilpro-modulo";

uint32_t tilpro_hash(const char * s) {
	uint32_t hash = 0;
	size_t i = 0;
	
	while (s[i] != '\0') {
		hash += s[i++];
		hash += hash << 10;
		hash ^= hash >> 6;
	}
	
	hash += hash << 3;
	hash ^= hash >> 11;
	hash += hash << 13;

	hash = hash % (HASHVEKSIZE - 1);
	
	return hash;
}