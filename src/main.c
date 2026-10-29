#include "swiftpack.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static unsigned char *read_file(const char *path, size_t *size) {
    FILE *f = fopen(path, "rb"); long n; unsigned char *p;
    if (!f || fseek(f, 0, SEEK_END) || (n = ftell(f)) < 0 || fseek(f, 0, SEEK_SET)) { if (f) fclose(f); return NULL; }
    p = (unsigned char *)malloc(n ? (size_t)n : 1);
    if (!p || fread(p, 1, (size_t)n, f) != (size_t)n) { free(p); fclose(f); return NULL; }
    fclose(f); *size = (size_t)n; return p;
}

int main(int argc, char **argv) {
    int decode; size_t n, out_n; unsigned char *in, *out; FILE *f;
    if (argc != 4 || (strcmp(argv[1], "-c") && strcmp(argv[1], "-d"))) {
        fprintf(stderr, "Usage: %s -c input output | -d input output\n", argv[0]); return 2;
    }
    decode = !strcmp(argv[1], "-d"); in = read_file(argv[2], &n);
    if (!in) { fprintf(stderr, "Cannot read input: %s\n", argv[2]); return 1; }
    if (!(decode ? swiftpack_decompress(in,n,&out,&out_n) : swiftpack_compress(in,n,&out,&out_n))) {
        fprintf(stderr, "Invalid input or allocation failure\n"); free(in); return 1;
    }
    f = fopen(argv[3], "wb");
    if (!f) { fprintf(stderr, "Cannot write output: %s\n", argv[3]); free(in); free(out); return 1; }
    if (fwrite(out,1,out_n,f) != out_n) { fprintf(stderr, "Cannot write output: %s\n", argv[3]); fclose(f); free(in); free(out); return 1; }
    if (fclose(f)) { fprintf(stderr, "Cannot close output: %s\n", argv[3]); free(in); free(out); return 1; }
    free(in); free(out); return 0;
}
