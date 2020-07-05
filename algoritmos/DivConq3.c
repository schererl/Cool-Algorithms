#include <stdio.h>

int cont = 0;

int f( int a, int b ) {
  int r = 0;
  while ( b > 0 ) {
    if ( b % 2 == 1 ) r += a;
    a *= 2;
    b /= 2;
  }
  return r;
}

void main() {
  int a, b;

  printf( "Entre com a e b: " );
  scanf( "%d %d", &a, &b );
  printf( "f( %d, %d ) : %d\n", a, b, f( a, b ) );
}
