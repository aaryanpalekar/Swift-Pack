CC ?= cc
CFLAGS ?= -std=c11 -O2 -Wall -Wextra -Wpedantic
CPPFLAGS ?= -Iinclude

.PHONY: all clean
all: build/swiftpack

build/swiftpack: src/main.c src/swiftpack.c include/swiftpack.h
	mkdir -p build
	$(CC) $(CPPFLAGS) $(CFLAGS) src/main.c src/swiftpack.c -o $@

clean:
	rm -rf build
