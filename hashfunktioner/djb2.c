#include <stdint.h>
#include <stdlib.h>

extern const int HASHVEKSIZE;
const char * HASHNAME = "djb2";

uint32_t tilpro_hash(const char * s) {
	uint32_t hash = 5381;
	int c;

	while (c = *s++) {
		hash = ((hash << 5) + hash) + c;
	}

	return hash & (HASHVEKSIZE - 1);
}