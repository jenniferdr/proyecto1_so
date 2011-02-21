/*Programa 8 reinas (version procesos).
 * Reporta una solucion existente para cada posicion
 * del tablero. 
 * Se asigna una tarea a cada proceso hijo para encontrar 
 * una solucion dado un tablero con una reina colocada.
 */   
#include "8reinas.c"
#include "estructuras.h"
#include <string.h>
FILE *arch;
void help(int x){
  printf("Error: Sintaxis de lainstruccion:\n");
  printf("\n");
  printf(" ./reinas_p -n<numero trabajadores>  -i{0|1} \n");
  printf("\n");
  exit(1);
}
#define TRUE 1
#define FALSE 0
void realizarReporte(int Soluciones[][],int n){
  int i,j,k;
  //Soluciones diferentes: solFinales[i]=1 
  // identifica la solucion con el menor tiempo.
  int solFinales[n];
  //Numero de soluciones
  int numSol[n];
  for(i=0; i<n;i++){
    solFinales[i]=1;
    numSol[i]=1;
  }

  /* Identificar soluciones con menor tiempo
   * y la cantidad de veces encontrada
   */ 
  for(i=0;i<n;i++){
    if(Soluciones[i][0]==-1 || solFin[i]==0){
      //Solucion repetida o no encontrada 
      solFinales[i]=0;
      numSol[i]=0;
    }else{
      //Ver si para la primera fila de cada solucion 
      //coincide alguna reina.Si es asi, terminar de 
      //comparar todas las filas restantes.
      for(j=i+1; j<n;j++){
	if(Soluciones[i][0]==Soluciones[j][0]){
	  int diferentes=FALSE;
	  for(k=1;k<=8;k++){
	    if(diferentes=Soluciones[i][k]!=Soluciones[j][k])
	      break;
	  }
	  if(!diferentes){
	    //Como son iguales, descartar la de mayor tiempo
	    if(Soluciones[i][9]<=Soluciones[j][9]){
	      solFinales[j]=0;
	      numSol[i]++;
	    }else{
	      solFinales[i]=0;
	      numSol[j]=numSol[i]+1;
	    }
	  }
	}
      }
    }
  }

  int total=0; 
  // Nro de soluciones diferentes encontradas
  for(i=0;i<n;i++) total=total + solFinales[i];
  printf("Nro. Total de soluciones diferentes: %d\n",total);

  //Imprimir soluciones
  for(i=0; i<n;i++){ 
    if(solFinales[i]){
      printf(" Solucion %d: ",i+1); 
      for(j=0;i<n;j++){
	printf("(%d,%d) ",i,Soluciones[i][j]);
      }
      printf("  Tiempo minimo: %d mseg.\n",Soluciones[i][9]);
      printf("  Nro. de veces encontrada: %d \n",numSol[i]);
    }
  }
  
}
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

      // Vector que contendra la ubicacion de las reinas
      reinas = (int*) malloc ( nreinas*sizeof(int) );

      sol=sol_reinas(i%8,i/8,reinas,8);

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


