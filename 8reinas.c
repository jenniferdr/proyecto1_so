// Problema de las n reinas. 

# include<stdio.h>
# include<stdlib.h>

# define FALSE 0
# define TRUE 1

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
        if(fila!=x || reinas[fila]!=y) reinas[fila] = -1;
	return ok;
     } 
  
  } else {

     // No quedan reinas por colocar (caso base)

     ok = TRUE;
  }

  return ok;
}



main(int argc, char *argv[]){
  int nreinas=8;
  int *reinas;  // Vector con las posiciones de las reinas de cada fila
  int sol;
  int i,j;
  int nsol=0;
  reinas = (int*) malloc ( nreinas*sizeof(int) );

  // for(i=0; i<nreinas;i++){
  // for(j=0; j<nreinas; j++){
      sol= sol_reinas(3,3,reinas,nreinas);
      if(sol){
	mostrarTablero(reinas,nreinas);
	nsol++;
      }    
      // }
      // }
  printf("%d\n",nsol);
  free(reinas);
}

