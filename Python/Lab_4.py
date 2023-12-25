from collections import namedtuple
from random import randint, uniform, sample

def analizujProstokat(prostokat):
    obwod = 2 * (abs(prostokat.x1 - prostokat.x2) + abs(prostokat.y1 - prostokat.y2))
    pole = abs(prostokat.x1 - prostokat.x2) * abs(prostokat.y1 - prostokat.y2)

    return f"Obwod: {obwod}\nPole: {pole}"


# print(analizujProstokat(namedtuple('prostokat', ['x1', 'y1', 'x2', 'y2'])))
# prostokat = namedtuple('prostokat', ['x1', 'y1', 'x2', 'y2'])
# print(analizujProstokat(prostokat(1, 1, 3, 3)))

# print([i for i in range(1, 1002, 2)])

l = list(range(1, 10))
l_copy = l[:]
l_copy[4] = 12
# print(l, l_copy)

randint_list = [randint(1, 10) for i in range(10)]
uniform_list = [uniform(1, 10) for i in range(10)]

res = randint_list + uniform_list
print(res)
print(sample(res, 3))

def levenstein(s1,s2):
    n = range(0,len(s1)+1)
    for y in range(1,len(s2)+1):
        l,n = n,[y]
        for x in range(1,len(s1)+1):
            n.append(min(l[x]+1,n[-1]+1,l[x-1]+((s2[y-1]!=s1[x-1]) and 1 or 0)))
    return n[-1]

print(levenstein('kot', 'kociol'))