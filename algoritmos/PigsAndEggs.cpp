#include <iostream>
#include <thread>
#include <chrono>
#include <iostream> 
using namespace std;


//cantinho do improviso
int **matriz;
int sizeMatriz;
//int cont = 0;
//****************//

void Imprime();

void AlocaMem()
{
    matriz = (int **)malloc( sizeMatriz * (sizeof(int *)));
    for(int i = 0; i < sizeMatriz; i++)
    {
        matriz[i] = (int *)malloc( sizeMatriz * (sizeof(int)));
    }
}

bool Seguro(int l, int c, int animal) //TODO: diagonal p = i - j diagonal s = ? 
{
    if(matriz[l][c] != 0) return false;
    //testa coluna
    for(int i = 0; i < sizeMatriz;i++) if( matriz[i][c] != 0 && matriz[i][c] != animal) return false; 
    
    // verifica se ocorre ataque na diagonal principal
	for(int i = l, j = c; i >= 0 && j >= 0; i--, j--) if(matriz[i][j] != 0 && matriz[i][j] != animal) return false;
	for(int i = l, j = c; i < sizeMatriz && j < sizeMatriz; i++, j++) if(matriz[i][j] != 0 && matriz[i][j] != animal) return false;
	

	// verifica se ocorre ataque na diagonal secundária
	for(int i = l, j = c; i >= 0 && j < sizeMatriz; i--, j++) if(matriz[i][j] != 0 && matriz[i][j] != animal) return false;
	for(int i = l, j = c; i < sizeMatriz && j >= 0; i++, j--) if(matriz[i][j] != 0 && matriz[i][j] != animal) return false;
	
 
    return true;
}

bool TestaLinha(int l, int animal)
{
    for(int i = 0; i < sizeMatriz;i++) if( matriz[l][i] != 0 && matriz[l][i] != animal) return false;
    return true;
}
/*
    flag = 1 posiciona porco
    flag = 2 posiciona galinha
    
    a busca pela posição da galinha começa a partir da posição da ultima galinha colocada na matriz (vice versa)
    
    se na linha testada já tiver um animal diferente, pula a linha
    
    se não encontrar posição para galinha, voltar para o ultimo porco posicionado e pega a proxima posição valida (vice versa)
    
    se já foi colocado todos animais de um tipo, a flag é alterada em tempo de execução para colocar o animal que falta
    
    observação: como cada rodada de posicionamento é determinada para colocar um animal para garantir que intercale entre porco e galinha
                na rodada 0 deve ser determinado qual animal começa o jogo (função setPigsNEggs())
*/
int Play(int porcos, int galinhas, int linha_p, int coluna_p, int linha_g, int coluna_g, int flag)
{
    if(porcos == 0 && galinhas == 0)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        Imprime();
        
        return 1; 
    }

    if(porcos > 0 && galinhas == 0) flag = 1;
    if(porcos == 0 && galinhas > 0) flag = 2;
    
    int sum = 0;
    int linha, coluna;
    if(flag == 1)  //porco
    {
        linha = linha_p;
        coluna = coluna_p;
    }else          //galinha
    {
        linha = linha_g;
        coluna = coluna_g;
    }
    
    while(linha < sizeMatriz)
    {
        //pula para próxima linha se necessário
        if(!TestaLinha(linha, flag)) 
        {
            coluna = 0;
            linha++;
            continue;
        }
        
        while(coluna < sizeMatriz)
        {
            if(flag == 1 && Seguro(linha, coluna, flag))
            {
                matriz[linha][coluna] = 1;
                sum += Play(porcos-1, galinhas, linha, coluna, linha_g, coluna_g, 2);
                matriz[linha][coluna] = 0;

            }
            else if(flag == 2 && Seguro(linha, coluna, flag))
            {
                matriz[linha][coluna] = 2;
                sum += Play(porcos, galinhas-1, linha_p, coluna_p, linha, coluna, 1);
                matriz[linha][coluna] = 0;

            }
            coluna++;
        }
        coluna = 0;
        linha++;
    }
    return sum;
    

}

void SetPigsNEggs(int nPigs, int nChickens)
{
    AlocaMem();
    int t = Play(nPigs, nChickens, 0, 0, 0, 0, 1);
    cout << "total de possibilidades: " << t << endl;
    
}

void Imprime()
{
    cout << "\033[2J\033[1;1H";
        
    cout << "Possíveis posições: " << endl;
    for(int i = 0; i < sizeMatriz;i++)
    {
        for(int j = 0; j < sizeMatriz; j++)
        {
           if(matriz[i][j] == 1)   std::cout << "\e[38:2:255:105:180m" << "P" << "\e[0m";
           else if (matriz[i][j] == 2) cout << "\e[38:2:65:105:225m" << "G" << "\e[0m";
           else cout << matriz[i][j];
           cout <<  "  " ;
        }
        cout << endl;
    }
}

int main(int argc, char *argv[ ])
{
    if(argc < 4) {
        cout << "fornecer valores para: tamanho da matriz, numero porcos, numero galinhas." << endl;
        return -1;
    }
    

    int nPigs, nChickens;
    sizeMatriz = atoi(argv[1]);
    nPigs = atoi(argv[2]);
    nChickens = atoi(argv[3]);
    SetPigsNEggs(nPigs, nChickens);
    
}