#include <stdio.h>
#include <iostream>
#include <limits>
#include <string>

int mem[10000000] = {};
int op[10000000] = {}; //memória para definir operadores

int countDown(int n)
{
    if(n <= 0) return std::numeric_limits<int>::max(); 
    if(n == 1) return 1;
    if(n == 2) return 1;
    if(n == 3) return 1;
    
    int r1 = std::numeric_limits<int>::max(); 
    int r2 = std::numeric_limits<int>::max();
    int r3 = std::numeric_limits<int>::max();
    
    if(n % 3 == 0) r1 = countDown(n/3);
    if(n % 2 == 0) r2 = countDown(n/2);
    if(!(n % 3 == 0 && n % 2 == 0))r3 = countDown(n-1);

    
    if( r2 < r1 ) {r1 = r2;}
    if( r3 < r1 ) {r1 = r3;}
    
    return r1 + 1;
}

int countDownDin(int n)
{
    if(n <= 0) return std::numeric_limits<int>::max();
    if(n == 1) return 1;
    if(n == 2) return 1;
    if(n == 3) return 1;
    if(mem[n] > 0) return mem[n];


    int r1 = std::numeric_limits<int>::max(); 
    int r2 = std::numeric_limits<int>::max();
    int r3 = std::numeric_limits<int>::max();
    
    if(n % 3 == 0) r1 = countDownDin(n/3);
    if(n % 2 == 0) r2 = countDownDin(n/2);
    if(!(n % 3 == 0 && n % 2 == 0))r3 = countDownDin(n-1);

    if( r2 < r1 ) {r1 = r2;}
    if( r3 < r1 ) {r1 = r3;}
    mem[n] = r1 + 1;
    

    return mem[n];
}

int countDownSeq(int n)
{
    mem[0] = 0;
    mem[1] = 1;
    mem[2] = 1;
    mem[3] = 1;
    
    for(int i = 1; i < n; i++)
    {
        if( i*2 <= n && (mem[i*2] > mem[i] + 1 || mem[i * 2] == 0))
        {
            mem[i*2] = mem[i] + 1;     
            op[i*2] = 2;
        }
        if( i*3 <= n && (mem[i*3] > mem[i] + 1 || mem[i * 3] == 0))
        {
            mem[i*3] = mem[i] + 1;
            op[i*3] = 3;
        }
        if( i+1 <= n && (mem[i+1] > mem[i] + 1 || mem[i + 1] == 0))
        {
            mem[i+1] = mem[i] + 1;
            op[i+1] = 1;
        }
    }
    return mem[n];
}

void geraString(int n)
{
    std::string str;
    int i = n;
    while(i > 1)
    {
        if(op[i] == 3) 
        { 
            str = str + " /3"; 
            i/=3;
        }
        else if(op[i] == 2)
        { 
            str = str + " /2"; 
            i/=2;
        }
        else if(op[i] == 1)
        { 
            str = str + " -1"; 
            i-=1;
        }
    }
    std::cout << str << std::endl;
}

void imprimeMemoria(int n)
{ 
    for(int i = 0; i < n+1; i++){ std::cout << i << "| ";}
    std::cout << std::endl;
    for(int i = 0; i < n+1; i++){ std::cout << mem[i] << "| ";}
    std::cout << std::endl;
}

void imprimeOp(int n)
{ 
    for(int i = 0; i < n+1; i++){ std::cout << i << "| ";}
    std::cout << std::endl;
    for(int i = 0; i < n+1; i++){ std::cout << op[i] << "| ";}
    std::cout << std::endl;
}

void limpaMemoria(int n){for(int i = 0; i <= n; i++){ mem[i] = 0; }}
void limpaOp(int n)
{
    for(int i = 0; i <= n; i++){ op[i] = 0; }
    op[0] = 0;
    op[1] = 1;
    op[2] = 2;
    op[3] = 3;
}

int main()
{
    int n;
    std::cin >> n; 
    

    
    //std::cout << "COUNTDOWN: " << countDown(n) << std::endl;

    //necessário para executar countDownDin
    limpaMemoria(n);
    std::cout << "COUNTDOWN dinâmico: " << countDownDin(n) << std::endl;

    //necessário para executar countDownSeq
    limpaMemoria(n);
    limpaOp(n);
    std::cout << "COUNTDOWN sequencial: " << countDownSeq(n) << std::endl;
    geraString(n); //só pode ser executado com countDownSeq  
    

    


}