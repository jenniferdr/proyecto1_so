#include "estructuras.h"
#define TRUE 1
#define FALSE 0

void trabajo(i,j){
  

}

void help(int x){
  printf("Error: Sintaxis de la instruccion:\n");
  printf("\n");
  printf(" ./reinas_p -n<numero trabajadores>  -i{0|1} \n");
  printf("\n *El numero de trabajadores debe estar entre 1 y 64 \n");
  exit(1);
}



void realizarReporte(int Soluciones[][9],int n){
  int i,j,k;
  //Soluciones diferentes: solFinales[i]=1 
  // identifica la solucion con el menor tiempo.
  int solFinales[n];
  //Numero de veces que se repite cada solucion
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
      //Ignorar solucion repetida o no encontrada 
      solFinales[i]=0;
      numSol[i]=0;
    }else{
      //Ver si para la primera fila de cada tablero 
      //coincide alguna reina.Si es asi, terminar de 
      //comparar el resto de las posiciones.
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
      for(j=0;j<8;j++){
	printf("(%d,%d) ",k++,Soluciones[i][k]);
      }
      printf("\n\t\tTiempo minimo: %d mseg.\n",Soluciones[i][8]);
      printf("\t\tNro. de veces encontrada: %d \n",numSol[i]);
    }
  }
  
}
 

// Mostrar el tablero con las reinas
// ---------------------------------
// Parámetros:
//   reinas - Vector con las posiciones de las distintas reinas
//   n      - Número de reinas

void mostrarTablero (int reinas[], int n)
{
  int i,j;

  for (i=0; i<n; i++) {

      for (j=0; j<n; j++) {

          if (reinas[i]==j)
             printf("#");
          else
             printf("-");
      }

      printf(" %d %d\n",i,reinas[i]);
  }
  printf("\n");
}

/*****************PROBLEMA N REINAS**********************/

// Comprobar si una reina está bien colocada
// -----------------------------------------
// La reina de la fila i está bien colocada si no está
// en la columna ni en la misma diagonal que cualquiera
// de las reinas de las filas anteriores
//
// Parámetros
//   fila   - Fila de la reina cuya posición queremos validar
//   reinas - Vector con las posiciones de las reinas
//   n      - Número de reinas


int comprobar (int fila, int reinas[], int n) 
{
  int i;

  for (i=0; i<n; i++){
    if(i!=fila && reinas[i]!=-1){
      if (  ( reinas[i]==reinas[fila] )                      // Misma columna
         || ( abs(fila-i) == abs(reinas[fila]-reinas[i]) ) ) // Misma diagonal
         return FALSE;
    }
  }

  return TRUE;
}

// int reinas[] apuntador a arreglo
// Devuelve TRUE si hay solucion, en caso contrario devuelve FALSE
int sol_reinas(int i,int j,int reinas[],int n){
  if(i>=n || j>=n)
    exit(1);

 // Inicializar vector:
 // (inicialmente, ninguna reina está colocada)
  int y;
 for (y=0; y<n; y++)
   reinas[y] = -1;

 // Colocar reina dada en el arreglo 
 reinas[i]= j;

 int ok= colocarReina(i,j,0,reinas,n);

 return ok;
 
}

int colocarReina(int x,int y,int fila,int reinas[],int n){
int ok = FALSE;

  if (fila<n) {

     // Quedan reinas por colocar
    if(reinas[fila]==-1){
     while ((reinas[fila]<n-1) && !ok) {

           // Colocamos la reina en la siguiente columna
           
           reinas[fila]++;

           // Comprobamos si la posición 
           // de la reina actual es válida

           if (comprobar(fila,reinas,n)) {

              // Si es así, intentamos colocar
              // las reinas restantes

	     ok = colocarReina (x,y,fila+1, reinas, n);
           }
     }
     }else{
      ok = colocarReina (x,y,fila+1, reinas, n);
      }

     if (!ok) {
        // Si no se han podido colocar las demás reinas
        // con la reina actual donde está, la quitamos
        if(fila!=x) reinas[fila] = -1;
	return ok;
     } 
  
  } else {

     // No quedan reinas por colocar (caso base)

     ok = TRUE;
  }

  return ok;
}
