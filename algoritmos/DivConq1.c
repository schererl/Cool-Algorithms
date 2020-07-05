#include <stdio.h>

int cont1 = 0;
int cont2 = 0;
int cont3 = 0;

int f1( int x, int n ) {
  if ( n == 0 ) return 1;
  return x * f1( x, n - 1 );
}

int f2( int x, int n ) {
  if ( n == 0 ) return 1;
  if ( n % 2 == 0 )
       return f2( x, n / 2 ) * f2( x, n / 2 );
  else return f2( x, n / 2 ) * f2( x, n / 2 ) * x;
}

int f3( int x, int n ) {
  if ( n == 0 ) return 1;
  int aux = f3( x, n / 2 );
  if ( n % 2 == 0 )
       return aux * aux;
  else return aux * aux * x;
}

void main() {
  int a, b;

  printf( "Entre com a e b: " );
  scanf( "%d %d", &a, &b );
  printf( "f1( %d, %d ) : %d\n", a, b, f1( a, b ) );
  printf( "f2( %d, %d ) : %d\n", a, b, f2( a, b ) );
  printf( "f3( %d, %d ) : %d\n", a, b, f3( a, b ) );
}
