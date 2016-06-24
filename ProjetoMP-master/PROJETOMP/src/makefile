NAME = main
NAME2 = TESTE
IDIR =../include
CC = gcc
CFLAGS =-I$(IDIR)

ODIR =obj
LDIR =../lib
LIBS = -lSDL -lSDL_ttf -lncurses

_DEPS = GUI.h operaGrafo.h
DEPS = $(patsubst %, $(IDIR)/%,$(_DEPS))

_OBJ = main.o GUI.o operaGrafo.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


main: $(OBJ)
	$(CC) -o $(NAME) $^ $(CFLAGS) $(LIBS)

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -g -c -o $@ $< $(CFLAGS) $(LIBS) -std=c99

run:
	./$(NAME)

install:
	sudo apt-get install libsdl1.2-dev libsdl-image1.2-dev libsdl-mixer1.2-dev libsdl-ttf2.0-dev libncurses-dev

clean:
		rm -f $(ODIR)/*.o ~* core $(INCDIR)/~*