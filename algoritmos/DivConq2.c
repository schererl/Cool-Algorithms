#include <stdio.h>

int cont = 0;

int f( int a, int b ) {
  while ( b > 0 ) {
    int tmp = a;
    a = b;
    b = tmp % b;
  }
  return a;
}

void main() {
  int a, b;

  printf( "Entre com a e b: " );
  scanf( "%d %d", &a, &b );
  printf( "f( %d, %d ) : %d\n", a, b, f( a, b ) );
}
