from itertools import permutations
import time
import diag
import perm

tps1 = time.time()

n = 10

sol = []
nextPerm = tuple([i for i in range(1,n+1)])
while (nextPerm!=0):
    if diag.diag(nextPerm) == 1:
        sol.append(nextPerm)
    nextPerm = perm.perm(nextPerm)

tps2 = time.time()
tmp1 = tps2 - tps1

print("time : ",tmp1)
print(len(sol)," solutions")
print(sol)
