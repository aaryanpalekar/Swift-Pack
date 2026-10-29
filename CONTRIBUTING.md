# Contributing

SwiftPack is under active development. Keep changes focused and document the
format or command-line behavior they introduce. Compression and decompression
must be lossless: every supported input must round-trip byte-for-byte.

## Build

Install a C11 compiler and GNU Make, then run `make`. The executable is written
to `build/swiftpack`. Run `make clean` to remove build output.

## Pull requests

Include a concise description of the change, the platform/compiler used, and
the commands used to validate it. For codec changes, include round-trip cases
for empty input, repetitive input, and arbitrary binary data.
