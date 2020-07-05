#include <stdio.h>

int cont = 0;
int Vet[] = {1, 2, 3, 4, 5, 6};
int nVet = sizeof( Vet ) / sizeof( Vet[0] );

int Stk[50] = {};

void f( int *V, int n, int max, int *S, int stk ) {

  if ( n == max ) {
    int ax;
    printf("{ ");
    for( ax = 0; ax < stk; ax++ )
      printf("%d ", S[ax]);
    printf("}\n");
    return;
  }

  S[stk] = V[n];
  f( V, n + 1, max, S, stk + 1 );
  f( V, n + 1, max, S, stk );
}

void main() {
  f( Vet, 0, nVet, Stk, 0 );
}
