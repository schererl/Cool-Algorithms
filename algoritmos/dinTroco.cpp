#include <iostream>
/*
Programação Dinâmica
enunciado: Quantas formas podemos distribuir ovos de páscoa para um turma sendo que existe um número menor ou igual de ovos para cada aluno
*/

mem int[100];
int troco(int n)
{
    if(n < 0) return 0;
    if(n == 0) return 1;
    
    return troco(n-11) || troco(n-5) || troco(n-1)
}
int main()
{
}