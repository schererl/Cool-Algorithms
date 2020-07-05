#include <iostream>
/*
Programação Dinâmica
enunciado: Quantas formas podemos distribuir ovos de páscoa para um turma sendo que existe um número menor ou igual de ovos para cada aluno
*/


//abordagem sequencial
int f(int alunos, int ovinhos)
{
    int m[ovinhos][alunos];

    for(int i = 0; i < ovinhos; i++)
    {
        for(int j = 0; j < alunos; j++)
        {
            m[i][j] = 1;
        }
    }


    for(int i = 1; i < ovinhos; i++)
    {
        for(int j = i+1; j < alunos; j++)
        {
            std::cout << m[i-1][j-1] << " + " << m[i][j-1] << std::endl;
            m[i][j] = m[i-1][j-1] + m[i][j-1];
        }
    }

    /*
        for i in range(1, len(mat)):
        for j in range(i+1, len(mat[i])):
            mat[i][j] = mat[i][j-1] + mat[i-1][j-1]

    return mat[ov][al]
    */


    for(int i = 0; i < ovinhos; i++)
    {
        for(int j = 0; j < alunos; j++)
        {
            std::cout << m[i][j] << "   ";
        }
        std::cout << "" << std::endl;
    }

    return m[ovinhos-1][alunos-1];
}

//abordagem recursiva simples
int DistRec(int alunos, int ovinhos)
{
    if(ovinhos == 0 || alunos == ovinhos) return 1;
    return DistRec(alunos - 1, ovinhos - 1) + DistRec(alunos - 1, ovinhos); //para cada aluno descontado existem 2 possibilidades, entregar ou não um ovo
}
int main()
{
    int x = 6;
    int y = 4;
    std::cout <<  "\n\n" << f(x,y) << std::endl;
    
    std::cout <<  "\n\n" << DistRec(x,y) << std::endl;
    
}