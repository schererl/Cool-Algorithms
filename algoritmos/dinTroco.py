
Mem = [0] * 1000
Esc = [0] * 1000

def moedas(n):
    global Mem
    if n < 0 :
      return float('inf')
    if n == 0 :
      return 0
    if Mem[n] > 0:
      return Mem[n]
    r1 = moedas(n-11)
    r2 = moedas(n-5)
    r3 = moedas(n-1)
    Esc[n] = 11
    if r2 < r1 :
        r1 = r2
        Esc[n] = 5
    if r3 < r1 :
        r1 = r3
        Esc[n] = 1
    Mem[n] = r1 + 1
    return Mem[n]
    
def escolha( n ): 
    if n == 0 :
      return ""
    return str(Esc[n]) + " " + escolha( n - Esc[n] )
    
for i in range(20):
    print(i, moedas(i), "(" + str(Esc[i]) + ") : ", escolha(i))
    