#include "estructuras.h"

void trabajo(i,j){
  FILE *arch;
  char cadena[100];
  sprintf(cadena,"TI_%d",i);
  strcat(cadena,"_");
  //printf("%d",j);
  //strcat(cadena,j);

  arch=fopen(cadena,"a+");
  fprintf(arch,"1 2 3 4 5 6 7 8 \n");
  fclose(arch); 
 
  // debo hacer un exit para el hijo y con las condfiones se fue exitoso o no 
}  

