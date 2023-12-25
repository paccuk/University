from math import (
    log,
    sin,
    cos,
    pi,
)


# def convert_time(sec):
#     return f'{hour} godzin, {minute} minut, {sec} sekund'
# print(convert_time(30))
# =====================================================
def convert_temp(kelvin_temp):
    return kelvin_temp - 273.15

# print(convert_temp(1000))
# =====================================================
def f(x, n=10, k=2): 
    return log((x**2 + 5), n) * (k + 1) * x

# print(f(2, k=7))
# =====================================================
f = lambda x: sin(x + 1) + cos(x**4)
result = [f(x) for x in range(-5, 3)]

# print(result)
# =====================================================
def unlimited_sum(*args: int) -> int:
    sum_result = 0
    for num in args:
        sum_result += num
    return sum_result

# print(unlimited_sum(*range(100)))
# =====================================================
def figure_value(fig_type, **kwargs):
    match fig_type:
        case 'kula':
            return (4 / 3) * pi * kwargs['r']**3
        
        case 'prostopadloscian':
            return kwargs['a'] * kwargs['b'] * kwargs['c']
        
        case 'waliec':
            return kwargs['r']**2 * kwargs['h'] * pi
        
        case 'stozek':
            return (1 / 3) * pi * kwargs['r']**2 * kwargs['h']

# print('Obietosc kuli wynosi:', round(figure_value('kula', r=3), 2))
# print('Obietosc prostopadloscianu wynosi:', round(figure_value('prostopadloscian', a=3, b=7, c=2.4), 2))
# print('Obietosc walca wynosi:', round(figure_value('waliec', r=4, h=7.7), 2))
# print('Obietosc stozka wynosi:', round(figure_value('stozek', r=2.56, h=9.1), 2))
# =====================================================
def divide_array(v1, v2, v3, v4):
    return v1, v2, v3, v4
# print(divide_array(*(1, 2, 3, 4)))

v1, v2, v3, v4 = (1, 2, 3, 4)
# print(v1, v2, v3, v4)
# =====================================================
def factorial_iter(num):
    num_factorial = 1
    for i in range(1, num + 1):
        num_factorial *= i
    return num_factorial
# print(factorial_iter(10))

def factorial_recursion(num):
    if num == 2: return num
    return factorial_recursion(num - 1) * num

# print(factorial_recursion(10))
# =====================================================
def T(n):
    if n == 0 or n == 1: return 0
    elif n == 2: return 1
    elif n > 2:
        return T(n-1) + T(n-2) + T(n-3)
    
print(T(5))