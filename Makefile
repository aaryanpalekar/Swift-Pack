CC ?= cc
CFLAGS ?= -std=c11 -O2 -Wall -Wextra -Wpedantic
CPPFLAGS ?= -Iinclude

.PHONY: all test fuzz clean
all: swiftpack.exe

test: test_swiftpack.exe
	./test_swiftpack.exe

fuzz: fuzz_swiftpack.exe
	./fuzz_swiftpack.exe

swiftpack.exe: src/main.c src/swiftpack.c include/swiftpack.h
	$(CC) $(CPPFLAGS) $(CFLAGS) src/main.c src/swiftpack.c -o $@

test_swiftpack.exe: tests/test_swiftpack.c src/swiftpack.c include/swiftpack.h
	$(CC) $(CPPFLAGS) $(CFLAGS) tests/test_swiftpack.c src/swiftpack.c -o $@

fuzz_swiftpack.exe: tests/fuzz_swiftpack.c src/swiftpack.c include/swiftpack.h
	$(CC) $(CPPFLAGS) $(CFLAGS) tests/fuzz_swiftpack.c src/swiftpack.c -o $@

clean:
	$(RM) swiftpack.exe test_swiftpack.exe fuzz_swiftpack.exe
