from itertools import permutations
import time

def diag(reines):
    nb = len(reines)
    diagPlus = [reines[i]+i for i in range(nb)]
    diagMoins = [reines[i]-i for i in range(nb)]
    if len(set(diagPlus)) == nb and len(set(diagMoins)) == nb:
        return True
    #print(diagPlus,"\n",diagMoins)
    return False

tps1 = time.time()

n = 10
sol = []
l = range(1,n+1)
perm = permutations(l)
for posR in perm:
    if diag(posR):
        sol.append(posR)

tps2 = time.time()
tmp1 = tps2 - tps1

print("time : ",tmp1)
print(len(sol)," solutions")
print(sol)