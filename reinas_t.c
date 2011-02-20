#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include "8reinas.c"
#include <pthread.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
struct Entrada
{
int fila;
int columna;
int num; 
int *reinas;
int *Soluciones;

};

int crearEntrada(){

  struct Entrada *E=(struct Entrada *) malloc(sizeof(struct Entrada));
  // Verificar que dio el espacio
  if(E ==NULL){
    printf("no hay suficiente memoria");
    return -1;
  }
  E->fila=0;
  E->columna=0;
  E->num=8;
  E->reinas=(int *)malloc(9*sizeof(int));
  E->Soluciones=(int *)malloc(8*9*sizeof(int));
  return 0;
} 

//#include "estructuras.h"
int* trabajo(pasaje){
  
  int sol;
  int i;
  int *reinas;
  //reinas=pasaje->reinas;
  //i=(pasaje->fila);

  // sol=sol_reinas(i%8,i/8,reinas,8);
  printf("%d",pasaje->fila);
  
  
  printf("hola %d \n",pasaje);
  //printf("hola \n",pthread_self());
  return;
}  


void help(int x){printf("Error: %d",x); exit(1);}
 

main(int argc, char *argv[]){
 
  int n,print;
  print=0;
  n=8;
  int Soluciones[n][9];
 

  //Comprobar los argumentos
  if(argc==3|| argc==5){
    int arg1,arg2;
    if((arg1=strcmp("-n",argv[1])!=0) && strcmp("-i",argv[1])!=0)help(1);

    if(arg1==0){

      if((n=atoi(argv[2]))<=0 || n>64)help(2);
      if(argc==5 && 
	 (strcmp(argv[3],"-i")!=0 ||(print=atoi(argv[4])!=0 && print!=1) ))help(3);
    }else{
      if((print=atoi(argv[2]))!=0 && print!=1)help(4);
      if(argc==5 && 
	 (strcmp(argv[3],"-n")!=0 || (n=atoi(argv[4]))<=0 || n>64))help(5);
    }

  }else{ 
    if(argc!=1)help(6);
  }

  int j;
  pthread_t hilo;
  for(j=0;j<n;j++){
    struct Entrada *pasaje=NULL;
    pasaje=(struct Entrada*)crearEntrada();
    pasaje->fila=j%8;
    pasaje->columna=j/8;
    pasaje->num=n;
    pasaje->Soluciones=*Soluciones;
    pthread_create(&hilo,NULL,(void *)trabajo,(void *)pasaje);

    pthread_join(hilo,NULL);
    
  }
}
    
    
    
 
