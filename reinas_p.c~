#include "estructuras.h"
FILE *arch;


main(){
  
  int n=8;
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


