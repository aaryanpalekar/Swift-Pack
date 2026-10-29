#include "swiftpack.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int round_trip(const unsigned char *input, size_t size) {
    unsigned char *packed = NULL, *restored = NULL;
    size_t packed_size = 0, restored_size = 0;
    int ok = swiftpack_compress(input, size, &packed, &packed_size) &&
             swiftpack_decompress(packed, packed_size, &restored, &restored_size) &&
             restored_size == size && (!size || memcmp(input, restored, size) == 0);
    free(packed); free(restored);
    return ok;
}

int main(void) {
    unsigned char binary[4096], repeated[8192];
    unsigned char *out = NULL;
    size_t out_size = 0;
    for (size_t i = 0; i < sizeof(binary); ++i) binary[i] = (unsigned char)(i * 73u);
    memset(repeated, 'A', sizeof(repeated));

    if (!round_trip(NULL, 0) || !round_trip((const unsigned char *)"hello", 5) ||
        !round_trip(binary, sizeof(binary)) || !round_trip(repeated, sizeof(repeated))) {
        fputs("round-trip test failed\n", stderr); return 1;
    }

    /* Invalid magic and a back-reference before any output must be rejected. */
    {
        const unsigned char bad_magic[] = {'N','O','P','E',1,0,0,0,0,0,0,0};
        const unsigned char bad_offset[] = {'S','W','P','K',1,4,0,0,0,0,0,0,0x80,1,0};
        if (swiftpack_decompress(bad_magic, sizeof(bad_magic), &out, &out_size) ||
            swiftpack_decompress(bad_offset, sizeof(bad_offset), &out, &out_size)) {
            fputs("malformed input was accepted\n", stderr); return 1;
        }
    }
    puts("SwiftPack tests passed");
    return 0;
}
