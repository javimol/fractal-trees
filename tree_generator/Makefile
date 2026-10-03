# Builds the tree generator. Needs only a C99 compiler and make.

CC      ?= cc
CFLAGS  ?= -O2
CFLAGS  += -std=c99 -D_DEFAULT_SOURCE -Wall -Wextra
LDLIBS  += -lm

SRC := src/main.c src/generator.c src/params.c src/output.c src/rng.c
OBJ := $(SRC:.c=.o)
BIN := tree-generator

$(BIN): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

src/%.o: src/%.c src/*.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ) $(BIN)

.PHONY: clean
