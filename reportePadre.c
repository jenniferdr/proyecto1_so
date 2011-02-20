#define TRUE 1
#define FALSE 0
#include <stdlib.h>
#include <stdio.h>

void realizarReporte(int Soluciones[][9],int n){
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
    if(Soluciones[i][0]==-1 || solFinales[i]==0){
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
	  for(k=1;k<8;k++){
	    if(diferentes=(Soluciones[i][k]!=Soluciones[j][k]))
	      break;
	  }
	  if(!diferentes){
	    //Como son iguales, descartar la de mayor tiempo
	    if(Soluciones[i][8]<=Soluciones[j][8]){
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

int nsol=1;
  //Imprimir soluciones
  for(i=0; i<n;i++){ 
    if(solFinales[i]){
      printf("\tSolucion %d: ",nsol++); 
k=0;
      for(j=0;j<n;j++){
	printf("(%d,%d) ",k++,Soluciones[i][k]);
      }
      printf("\n\t\tTiempo minimo: %d mseg.\n",Soluciones[i][8]);
      printf("\t\tNro. de veces encontrada: %d \n",numSol[i]);
    }
  }
  
}

main(){
  int n=8,i,j,k=0;
int Sol[n][9];

for(i=0; i<n;i++){
for(j=0;j<9;j++){
Sol[i][j]=2;
}
}
Sol[3][8]=1;
Sol[0][4]=9696969;

realizarReporte(Sol,n);

}


