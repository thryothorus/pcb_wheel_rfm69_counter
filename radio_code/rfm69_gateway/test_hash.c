#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>

uint32_t hash_me(const char* str) {
uint32_t hash = 0; // Start with a 32-bit hash (we'll constrain to 24 bits)

    while (*str) {
        hash = (hash * 31 + (uint8_t)(*str)) % 0xFFFFFF;
        str++;
    }
    return hash;
}

void main()
{
	uint32_t hash_result=	hash_me("Hello World");
	printf("%"PRIu32"\n", hash_result);
}

