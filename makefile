all:  estructuras.o reinas_t.o reinas_p.o
	gcc estructuras.o reinas_t.o -pthread -ggdb -lm -o reinas_t
	gcc reinas_p.o estructuras.o -o reinas_p

reinas_t.o: estructuras.h
	gcc -ggdb -c reinas_t.c -o reinas_t.o
reinas_p.o: reinas_p.c estructuras.h
	gcc -c reinas_p.c -o reinas_p.o

estructuras.o: estructuras.c estructuras.h
	gcc -ggdb -c estructuras.c -o estructuras.o

clean:
	rm *.o reinas_t TI_*
