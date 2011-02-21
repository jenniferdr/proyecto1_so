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
  int Soluciones[8][9];
struct Entrada
{
int fila;
int num; 
int *reinas;
int *Soluciones;

};

struct Entrada *crearEntrada(){

  struct Entrada *E=(struct Entrada *) malloc(sizeof(struct Entrada));
  // Verificar que dio el espacio
  if(E ==NULL){
    printf("no hay suficiente memoria");
    return ;
  }
  E->fila=0;
  E->num=8;
  E->reinas=(int *)malloc(8*sizeof(int));
  E->Soluciones=NULL;//(int *)malloc(8*9*sizeof(int));
  return E;
} 

//#include "estructuras.h"
int* trabajo(struct Entrada *j){
  Soluciones[j->num][9];
  int sol;
  int k;
  j->Soluciones=Soluciones;
  sol=sol_reinas(j->fila%8,j->fila/8,j->reinas,8);
  for(k=0;k<8;k++){
    
   Soluciones[j->fila][k]=j->reinas[k];  
   //printf("%d\n",Soluciones[j->fila][k]);  
}  
 
  printf("hola %d \n",j->reinas[1]);
  if (sol==0){
    return j->reinas;
  }
}  


void help(int x){printf("Error: %d",x); exit(1);}
 

main(int argc, char *argv[]){
 
  int n,print;
  print=0;
  n=8;

 

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
  pthread_t hilo[n];
  for(j=0;j<n;j++){
    hilo[j]=(pthread_t)malloc(sizeof(pthread_t));
    struct Entrada *pasaje=NULL;
    pasaje=(struct Entrada*)crearEntrada();
    pasaje->fila=j;
    pasaje->num=n;
   
    pasaje->Soluciones=*Soluciones;
     
    pthread_create(&hilo[j],NULL,(void *)trabajo,(void *)pasaje);
  }
 
  int status;
  for(j=0;j<n;j++){
    printf("%d\n",Soluciones[j][1]);  
    pthread_join(hilo[j],(void*)&status);
   
  }
}
    
    

 
