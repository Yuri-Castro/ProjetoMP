NAME = main
NAME2 = TESTE
IDIR =../include
CC = gcc
CFLAGS =-I$(IDIR)

ODIR =obj
LDIR =../lib
LIBS = -lSDL -lSDL_ttf -lncurses

_DEPS = GUI.h leitor.h
DEPS = $(patsubst %, $(IDIR)/%,$(_DEPS))

_OBJ = main.o GUI.o leitor.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -g -c -o $@ $< $(CFLAGS) $(LIBS)

main: $(OBJ)
	$(CC) -o $(NAME) $^ $(CFLAGS) $(LIBS)
run:
	./$(NAME)
# install_libraries:
#	sudo apt-get install ???
clean:
		rm -f $(ODIR)/*.o ~* core $(INCDIR)/~*