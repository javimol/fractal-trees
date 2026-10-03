# Requires: sudo apt install build-essential freeglut3-dev libglu1-mesa-dev
CC      = gcc
CFLAGS  = -O2 -w
LDLIBS  = -lglut -lGLU -lGL -lm
SRC     = main.c Visualizador.c Fichero.c Mem.c Def.c

visualizador: $(SRC) *.h
	$(CC) $(CFLAGS) -o $@ $(SRC) $(LDLIBS)

run: visualizador
	./visualizador arboles

clean:
	rm -f visualizador
