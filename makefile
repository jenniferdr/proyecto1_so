all: reinas_p.o estructuras.o
	gcc reinas_p.o estructuras.o -o reinas_p
reinas_p.o: reinas_p.c estructuras.h
	gcc -c reinas_p.c -o reinas_p.o
estructuras.o: estructuras.c estructuras.h
	gcc -c estructuras.c -o estructuras.o

clean:
	rm *.o reinas_p TI_*
