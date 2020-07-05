#include <iostream>
#include <string>
#include <cstring>
using namespace std;


#define max(a,b) ((a) > (b) ? (a) : (b))


string soma(string a, string b)
{
    string c;
    bool vaiUm = false;
    //se um for maior que outro -> shift
    
    int size = max(a.size(), b.size());
    while(a.size() < size) a.insert(0, "0");
    while(b.size() < size) b.insert(0, "0");

    for(int i = a.size() - 1; i >= 0; i--)
    {
        int tmpA = (int)(a[i]) - 48; //cast de char para inteiro
        int tmpB = (int)(b[i]) - 48; //cast de char para inteiro
        int tmp = tmpA + tmpB;
        
        if(vaiUm) tmp++;
        
        if(tmp > 9)
        {
            vaiUm = true;
            c = to_string(tmp - 10) + c;
        }
        else
        {
            vaiUm = false;
            c = to_string(tmp) + c;
        }
    }

    if(vaiUm) c = "1" + c;


    return c;
}


//a - b
string subtrai(string a, string b)
{
    string c;
    bool tiraUm = false;
    
    //se um for maior que outro -> shift
    int size = max(a.size(), b.size());
    while(a.size() < size) a.insert(0, "0");
    while(b.size() < size) b.insert(0, "0");
   


    for(int i = a.size() - 1; i >= 0; i--)
    {
        int tmpA = (int)(a[i]) - 48; //cast de char para inteiro
        int tmpB = (int)(b[i]) - 48; //cast de char para inteiro
        if(tiraUm) tmpA--;

        if(tmpA >= tmpB)
        { 
            tiraUm = false;
            c = to_string(tmpA - tmpB) + c;
            
        }
        else
        {
            tiraUm = true;
            int tmp = 10 - tmpB;
            tmp += tmpA;
            c = to_string(tmp) + c;
        }
    }
    return c;

}

string multiplica(string a, string b)
{
    
    return to_string(stoi(a) * stoi(b));

}

string shift(string a, int potencia)
{
    for(int n = 0; n < potencia; n++)
    {
        a =  a + "0";
    }
    return a;
}


string Karatsuba(string x, string y)
{
    int size = max(x.size(), y.size());
    while(x.size() < size) x.insert(0, "0");
    while(y.size() < size) y.insert(0, "0");
    
    //caso de parada
    if(size == 1)
    {
        return multiplica(x, y);
    }
    

    // ajuster divisão impar size-size/2
    string a  = x.substr(0, size/2);
    string a2 = x.substr(size/2, size- size/2);
    string b  = y.substr(0, size/2);
    string b2 = y.substr(size/2, size- size/2);
    
    string p0 = Karatsuba(a, b);
    string p1 = Karatsuba(a2, b2);
    string p2 = Karatsuba(soma(a, a2), soma(b, b2));
    
    
    // po + (p2 - p0 - p1) + p1
    return soma(soma(shift(p0, 2*(size - size/2)), p1), shift(subtrai(p2, soma(p0,p1)), size-size/2));


    
    
    //**********PARA TESTES**********//
    /*
    string p0p1 = soma(p0, p1);
    string p3 = subtrai(p2, p0p1);
    string shiftp0 = shift(p0, 2*(size - size/2));
    string shiftp3 = shift(p3, (size - size/2));
    cout << "\np0: " << shiftp0 << "\np2: " << shiftp3 << "\np1: " << p1 << endl;
    */
    //*********************************//


}

string limparZeros(string k)
{
    return k.erase(0, min(k.find_first_not_of('0'), k.size()-1));
}

int main()
{
    
   cout << "\n------------KARATSUBA para adultos-----------" << endl;
   string a,b,k;
   cout << "Valor de A: ";
   cin >> a ;
   cout << "Valor de B: ";
   cin >> b ;
   k = Karatsuba(a , b);
   cout << "\n" << a << "*" << b << " = " << limparZeros(k) << endl;
}