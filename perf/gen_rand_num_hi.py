import random

#upbound = 0x8000000000000000
#upbound= 1000
upbound = 63
for i in range(0,50):
    a = random.randint(1, 2**upbound - 1)
    b = random.randint(1, 2**upbound - 1)
    m = random.randint(1, 2**upbound - 1)
    res = (a * b) % m
    print("%ld %ld %ld %ld" % (a, b, m, res))