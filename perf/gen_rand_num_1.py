import random

'''
upbound_a = 4
upbound_b = 4
upbound_m = 4
for i in range(0,50):
    a = random.randint(1, 2**upbound_a - 1)
    b = random.randint(1, 2**upbound_b - 1)
    m = random.randint(1, 2**upbound_m - 1)
    res = (a * b) % m
    print("%ld %ld %ld %ld" % (a, b, m, res))'''

numOf1 = 63
numOf1Inm = 32
a = 0
b = 0
m = 0
for i in range(0, 50):
    a1List = random.sample(range(0,63), numOf1)
    b1List = random.sample(range(0,63), numOf1)
    m1List = random.sample(range(0,63), numOf1Inm)
    for x in a1List:
        a += 2**x
    for y in b1List:
        b += 2**y
    for k in m1List:
        m += 2**k    
    print("%ld %ld %ld" % (a, b, m))    