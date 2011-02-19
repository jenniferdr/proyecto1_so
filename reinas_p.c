/*Programa 8 reinas (version procesos).
 * Reporta soluciones existentes para cada posicion
 * del tablero. 
 * Se asigna una tarea a cada proceso hijo para encontrar 
 * una solucion para dado tablero con una reina colocada.
 */   
#include "8reinas.c"
#include "estructuras.h"
#include <string.h>
FILE *arch;
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
 
  int Soluciones [n][9]; 
  int i;//i sera las filas
  int j;// las columnas 
  int hijo;
  int padre= getpid();

  for(i=0;i<n;++i){
    hijo=fork();
    if (hijo<0){
      perror("fork");
      exit(1);
    }

    else if( hijo==0){
     
     char cadena[20];
     sprintf(cadena,"TI_%d_%d",i%8,i/8);
      arch=fopen(cadena,"a+");
      int nreinas=8;
      int *reinas;
      int sol;
      reinas = (int*) malloc ( nreinas*sizeof(int) );
      sol=sol_reinas(i%8,i/8,reinas,8);
      for(j=0;j<8;j++){
	fprintf(arch ,"%d\n",reinas[j]);
      }
      fclose(arch); 
      exit(0);

    }
    else {
      int estado;
      wait(&estado);
      	if (WEXITSTATUS(estado)!=0){
	  perror("termino mal un hijo");
	  exit(1);
       	}
    }
  }
  for(i=0;i<n;++i){
    char cadena[20];
    sprintf(cadena,"TI_%d_%d",i%8,i/8);
    arch=fopen(cadena,"r");
    for(j=0;j<8;j++){
      fscanf(arch,"%d",&Soluciones[i][j]);
    }
  }
}     


