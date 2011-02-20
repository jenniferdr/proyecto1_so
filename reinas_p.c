/*Programa 8 reinas (version procesos).
 * Reporta una solucion existente para cada posicion
 * del tablero. 
 * Se asigna una tarea  cada proceso hijo para encontrar 
 * una solucion dado un tablero con una reina colocada.
 */   

#include "estructuras.h"

FILE *arch;

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
  int i;// sera las filas
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

      // Vector que contendra la ubicacion de las reinas
      reinas = (int*) malloc ( nreinas*sizeof(int) );

      sol=sol_reinas(i%8,i/8,reinas,nreinas);

      if(sol){
	for(j=0;j<8;j++){
	  fprintf(arch ,"%d\n",reinas[j]);
	}
      }else{
	for(j=0;j<9;j++){
	  fprintf(arch ,"%d\n",-1);
	}
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

  // Leer resultados de cada hijo y
  // colocarlos en las filas de Soluciones[] 
  for(i=0;i<n;++i){
    char cadena[20];
    sprintf(cadena,"TI_%d_%d",i%8,i/8);
    arch=fopen(cadena,"r");
    if(arch==NULL)perror("No se puede abrir el archivo");
    for(j=0;j<8;j++){
      fscanf(arch,"%d",&Soluciones[i][j]);
    }
    fclose(arch);
  }
 

  realizarReporte(Soluciones,n);

}


