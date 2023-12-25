from math import (
    log,
    sin,
)

def task_1(num1, num2):
    if num1 == num2:
        print("Liczby są równe")
    elif num1 % num2 == 0:
        print(num1, "jest wielokrotnością liczby", num2)
    elif num2 % num1 == 0:
        print(num2, "jest wielokrotnością liczby", num1)
    else:
        print("Liczby nie są swoimi wielokrotnościami")


def sequence0(n: int):
    if n == 1:
        return 2
    elif n == 2:
        return 3
    elif n > 2:
        return 2 * sequence0(n-1) + sequence0(n-2)
    
def sequence1(n: int):
    if n == 1: return 2
    elif n == 2: return 3
    
    res = 0
    for i in range(1, n+1):
        if i == 1: res += 2
        elif i == 2: res += 3
        elif i > 2: res += 2 * (i-1) + (i-2)

    return res



def equation(x, k=2, p=4):
    return -2 * log(x, k) + sin(x)**p 



task_1(2, 5) # 2 nie jest wielokrotnością liczby 5
task_1(4, 2) # 4 jest wielokrotnością liczby 2

print(sequence0(n=5)) # 46
print(sequence1(n=5))

print(equation(x=10, p=2)) # -6.347897220681421