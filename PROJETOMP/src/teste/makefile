all:
	gcc -c ./*.cpp
	g++ ./testes.cpp operaGrafo.o /usr/lib/libgtest.a -o testes.bin -fPIC -O2 -g -Wall -lpthread

clean:
	rm operaGrafo.o testes.o
