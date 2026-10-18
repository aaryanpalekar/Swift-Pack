# SwiftPack

**A high-performance, LZ4-inspired lossless compression library and CLI written in C.**

SwiftPack is a systems programming project focused on building a fast, lightweight compression engine from scratch. It explores hash-based match finding, efficient memory handling, parallel processing, and performance optimization.

The project aims to investigate the trade-offs between compression speed, decompression speed, and compression ratio by benchmarking against the reference LZ4 implementation.

> 🚧 **Status:** Under development

## Features

- [ ] Lossless compression and decompression
- [ ] Hash-based match finding
- [ ] Command-line interface (CLI)
- [ ] Round-trip correctness tests
- [ ] Fuzz testing and malformed-input validation
- [ ] SIMD-based optimizations
- [ ] Multithreaded block compression
- [ ] Checksums for data integrity
- [ ] Performance benchmarks against LZ4

## Goals

- Build a compression engine from scratch using C.
- Understand LZ77-style matching and back-reference encoding.
- Explore low-level memory management and CPU-bound optimization.
- Investigate SIMD and parallel processing techniques.
- Measure compression throughput, decompression throughput, and compression ratio.
- Develop a maintainable library with a simple CLI.

## Tech Stack

- **Language:** C
- **Build System:** Make
- **Version Control:** Git and GitHub
- **Testing:** Automated round-trip tests, fuzzing, and sanitizers
- **Benchmarking:** Custom benchmarks against LZ4

## Project Structure

```text
SwiftPack/
├── include/       # Public library headers
├── src/           # Compression and decompression implementation
├── tests/         # Correctness and fuzz tests
├── benchmarks/    # Benchmarking tools and results
├── examples/      # Example usage
├── Makefile
├── README.md
└── LICENSE
