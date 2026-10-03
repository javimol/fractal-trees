# Builds the desktop visualizer. Dependencies:
#   Debian/Ubuntu: sudo apt install build-essential freeglut3-dev libglu1-mesa-dev
#   Fedora:        sudo dnf install gcc make freeglut-devel mesa-libGLU-devel
#   Arch:          sudo pacman -S base-devel freeglut glu
#   macOS:         Xcode command-line tools (uses the system GLUT framework; untested)

CC      ?= cc
CFLAGS  ?= -O2
CFLAGS  += -std=c99 -D_DEFAULT_SOURCE -Wall -Wextra
ifeq ($(shell uname -s),Darwin)
LDLIBS  += -framework GLUT -framework OpenGL -lm
else
LDLIBS  += -lglut -lGLU -lGL -lm
endif

SRC := src/main.c src/viewer.c src/tree.c src/bmp.c
OBJ := $(SRC:.c=.o)
BIN := fractal-trees

$(BIN): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

src/%.o: src/%.c src/*.h
	$(CC) $(CFLAGS) -c -o $@ $<

run: $(BIN)
	./$(BIN)

clean:
	rm -f $(OBJ) $(BIN)

.PHONY: run clean
