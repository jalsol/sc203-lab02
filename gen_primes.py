import Crypto.Util.number

start = 8
limit = 64

for i in range(start, limit + 1, 4):
    for _ in range(67):
        print(Crypto.Util.number.getPrime(i))
    print()
