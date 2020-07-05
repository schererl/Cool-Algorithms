#include <stdio.h>
#include <iostream>

int n = 35;
int static mem[100] = {};
int escadas(int n)
{
    if(n == 0) return 1;
    if(n == 1) return 1;
    if(n == 2) return 2;

    return escadas(n-1) + escadas(n-2) + escadas(n-3);
}

//não ta gravando nada em memória
int escadasDin(int n)
{
    
    if(n == 0) return 1;
    if(n == 1) return 1;
    if(n == 2) return 2;
    if(mem[n] > 0) 
    {
        std::cout << mem[n] << std::endl;
        return mem[n];
    }

    mem[n] = escadasDin(n-1) + escadasDin(n-2) + escadasDin(n-3);
    return mem[n];

}

int escadaSequencial(int n)
{
    int memLocal[100] = {};
    memLocal[0] = 1; memLocal[1] = 1; memLocal[2] = 2;
    for(int i = 3; i<n+1; i++)
    {
        memLocal[i] = memLocal[i-1] + memLocal[i-2] + memLocal[i-3];
    }
    return memLocal[n];
}

void printArray(int n)
{
    for(int i = 0;i < n;i++){std::cout << mem[i] ;}
    std::cout << std::endl;
}

int main()
{


    std::cout << escadaSequencial(n) << std::endl;
    std::cout << escadas(n) << std::endl;
    std::cout << escadasDin(n) << std::endl;
    std::cout << mem[n-1];
    
    return 0;
}
