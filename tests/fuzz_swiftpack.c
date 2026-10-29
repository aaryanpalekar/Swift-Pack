#include "swiftpack.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FUZZ_ROUNDS 10000u
#define MAX_INPUT 4096u

static uint32_t state = 0x91e10da5u;

static uint32_t next_random(void) {
    state ^= state << 13;
    state ^= state >> 17;
    state ^= state << 5;
    return state;
}

static int exercise(const unsigned char *data, size_t size, unsigned round) {
    unsigned char *packed = NULL, *restored = NULL, *mutated = NULL, *discard = NULL;
    size_t packed_size = 0, restored_size = 0, discard_size = 0;
    if (!swiftpack_compress(data, size, &packed, &packed_size) ||
        !swiftpack_decompress(packed, packed_size, &restored, &restored_size) ||
        restored_size != size || (size && memcmp(data, restored, size))) {
        fprintf(stderr, "round-trip failure at fuzz case %u\n", round);
        free(packed); free(restored); return 0;
    }
    free(restored); restored = NULL;

    mutated = (unsigned char *)malloc(packed_size ? packed_size : 1);
    if (!mutated) { free(packed); return 0; }
    for (unsigned trial = 0; trial < 3; ++trial) {
        size_t mutated_size = packed_size;
        if (packed_size) {
            memcpy(mutated, packed, packed_size);
            if ((next_random() & 3u) == 0) mutated_size = next_random() % (packed_size + 1);
            else mutated[next_random() % packed_size] ^= (unsigned char)(1u << (next_random() & 7u));
        }
        /* Any mutated input may be rejected or decoded; it must remain safe. */
        if (swiftpack_decompress(mutated, mutated_size, &discard, &discard_size)) free(discard);
        discard = NULL;
    }
    free(mutated); free(packed);
    return 1;
}

int main(void) {
    unsigned char data[MAX_INPUT];
    for (unsigned round = 0; round < FUZZ_ROUNDS; ++round) {
        size_t size = next_random() % (MAX_INPUT + 1u);
        unsigned mode = next_random() % 4u;
        for (size_t i = 0; i < size; ++i) {
            if (mode == 0) data[i] = (unsigned char)next_random();
            else if (mode == 1) data[i] = (unsigned char)(i % 7u);
            else if (mode == 2) data[i] = (unsigned char)(next_random() % 8u);
            else data[i] = (unsigned char)(i < 32 ? next_random() : data[i - 32]);
        }
        if (!exercise(data, size, round)) return 1;
    }
    printf("Fuzz smoke test passed (%u cases)\n", FUZZ_ROUNDS);
    return 0;
}
