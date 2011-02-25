#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
//#include "8reinas.c"
#include <pthread.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
 
struct Entrada
{
int print;
int fila;
int num; 
int *reinas;
};

extern void help(int x);
extern void mostrarSolucion (int reinas[], int n,int sol, long int tiempo,int x,int y);
extern int colocarReina(int x,int y,int fila,int reinas[],int n);
extern int comprobar (int fila, int reinas[], int n); 
extern int sol_reinas(int i,int j,int reinas[],int n);

extern struct Entrada *crearEntrada();
extern int* trabajo(struct Entrada *j);
extern void realizarReporte(int Soluciones[][9],int n);
