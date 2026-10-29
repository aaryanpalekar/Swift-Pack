#ifndef SWIFTPACK_H
#define SWIFTPACK_H

#include <stddef.h>

/* Allocate a compressed buffer. The caller owns *output and must free it. */
int swiftpack_compress(const unsigned char *input, size_t input_size,
                       unsigned char **output, size_t *output_size);

/* Decode a SwiftPack stream into a newly allocated buffer. */
int swiftpack_decompress(const unsigned char *input, size_t input_size,
                         unsigned char **output, size_t *output_size);

#endif
