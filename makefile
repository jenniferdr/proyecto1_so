all:  estructuras.o reinas_t.o
	gcc estructuras.o reinas_t.o -pthread -ggdb -lm -o reinas_t
reinas_t.o: estructuras.h
	gcc -ggdb -c reinas_t.c -o reinas_t.o

estructuras.o: estructuras.h
	gcc -ggdb -c estructuras.c -o estructuras.o

clean:
	rm *.o reinas_t