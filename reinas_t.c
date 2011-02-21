/*Jennifer Dos Reis 08-10323
 *Juliana Leon 08-10608
 *Programa 8 reinas (version hilos)
 * Reporta una solucion existente para cada posicion
 * del tablero. 
 * Se asigna una tarea  cada hilo para encontrar 
 * una solucion dado un tablero con una reina colocada.
 */
#include "estructuras.h"
// Variable Global, matriz de soluciones  
int Soluciones[8][9];

//Funcion para Inicializar los valores la estructura
struct Entrada *crearEntrada(){

  struct Entrada *E=(struct Entrada *) malloc(sizeof(struct Entrada));
  // Verificar que dio el espacio
  if(E ==NULL){
    printf("no hay suficiente memoria");
    return ;
  };

  E->fila=0;
  E->num=8;
  E->reinas=(int *)malloc(8*sizeof(int));
  return E;
} 

// funcion que realizar cada hilo, 
int* trabajo(struct Entrada *j){
  int sol;
  int k;
 
  struct timeval start, end;
  gettimeofday(&start, NULL);
  sol=sol_reinas(j->fila%8,j->fila/8,j->reinas,8);
  gettimeofday(&end, NULL);

  int tiempo = ((end.tv_sec * 1000000 + end.tv_usec)
		- (start.tv_sec * 1000000 + start.tv_usec));

      if(sol){
	for(k=0;k<8;k++){
	  Soluciones[j->fila][k]=j->reinas[k];
	}
	Soluciones[j->fila][9]=tiempo;
      }else{
	  for(k=0;k<8;k++){
	    Soluciones[j->fila][k]=-1;
	      }
	}
free(j);

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
  //Creacion de los hilos
  int j;
  pthread_t hilo[n];
  for(j=0;j<n;j++){
    hilo[j]=(pthread_t)malloc(sizeof(pthread_t));
    struct Entrada *pasaje=NULL;
    pasaje=(struct Entrada*)crearEntrada();
    pasaje->fila=j;
    pasaje->num=n;
    //Asignacion de Tareas
    if(pthread_create(&hilo[j],NULL,(void *)trabajo,(void *)pasaje)!=0){
      perror("fallo un hilo");
      exit(1);
    }
    
  }
  // Espera Por los hilos
  int status;
  for(j=0;j<n;j++){
    if (pthread_join(hilo[j],(void*)&status)!=0){
       perror("fallo un hilo");
      exit(1);
    }
  }

 
  // llamada a la funcion para el Reporte del hilo principal
  realizarReporte(Soluciones,n);
}
  
