/*Programa 8 reinas (version procesos).
 * Reporta soluciones existentes para cada posicion
 * del tablero. 
 * Se asigna una tarea a cada proceso hijo para encontrar 
 * una solucion para dado tablero con una reina colocada.
 */   

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

  for (j=1;j-1<n/8;++j){
    i=0;
    for(i=1;i-1<n;++i){ // quizas con lo que ellos te dan de la posicion de la fila se pueda eliminar un for pero ahora no lo veo 
      hijo=fork();
      if (hijo<0){
	perror("en el fork");
	//exit(1);
      }

      else if(hijo==0){
	

	trabajo(i,j);
	//printf("Hijo: i:%d my pid:%ld mi padre es:%ld\n", i, (long)getpid(), (long)getppid());
	exit(0);// falta considerar el error de exit
      }
    
      else{

	int estado;

	//printf("Hijo: i:%d my pid:%ld mi padre es:%ld\n", i, (long)getpid(), (long)getppid());
	wait(&estado);
	//printf("Termino:i:%d pid:%ld\n", i, (long)getpid());
	if (WEXITSTATUS(estado)!=0){
	  perror("termino mal un hijo");
	  exit(1);
       	}
      }
    }
  }
  for(i=0;i<n;i++){
    char cadena[10];
    sprintf(cadena,"TI_%d",i+1);
    strcat(cadena,"_");
    //int solu[10];
    
    arch=fopen(cadena,"r");
    j=0;
    int end=0;
    while(j<=8){//poner comdicion de parar al terminar el archivo
      end=fscanf(arch,"%d",&Soluciones[j][i]);
      //printf("%d\n",Soluciones[j][i]);
      
      j++;
    }
  }
}


