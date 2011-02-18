all: proceso.o estructuras.o
	gcc proceso.o estructuras.o -o proceso
proceso.o: proceso.c estructuras.h
	gcc -c proceso.c -o proceso.o
estructuras.o: estructuras.c estructuras.h
	gcc -c estructuras.c -o estructuras.o

clean:
	rm *.o proceso TI_*