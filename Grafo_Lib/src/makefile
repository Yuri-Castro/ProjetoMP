IDIR=../include
LIB_DIR=../lib
CXX=g++

CXXFLAGS=-g -W -Wall -I$(IDIR) -L$(LIB_DIR) -pthread

ODIR=obj

LIBS=-lm -lgtest -lgtest_main

_DEPS1 = grafo.h lista_dupla.h lista_simples.h
DEPS1 = $(patsubst %,$(IDIR)/%,$(_DEPS1))

_DEPS2 = gtest/gtest.h
DEPS2 = $(patsubst %,$(IDIR)/%,$(_DEPS2))

DEPS = $(DEPS1) $(DEPS2)

_OBJ = main.o grafo.o lista_dupla.o lista_simples.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

all: lista_dupla_teste lista_simples_teste grafo_teste main

$(ODIR)/%.o: %.c $(DEPS)
	$(CXX) -g -c -o $@ $< $(CXXFLAGS) $(LIBS)

main: $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

lista_dupla_teste: lista_dupla_teste.c lista_dupla.c ../include/lista_dupla.h
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

grafo_teste: grafo_teste.c grafo.c lista_simples.c lista_dupla.c ../include/grafo.h ../include/lista_simples.h ../include/lista_dupla.h
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

lista_simples_teste: lista_simples_teste.c lista_simples.c ../include/lista_simples.h
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

# Escrever aqui a compilacao dos outros testes;

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o ~* core $(INCDIR)/~*
