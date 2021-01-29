import time

def prenable(reines, ligne):
    if ligne in reines:
        return True
    nb = len(reines)
    diagPlus = [reines[i]+i for i in range(nb)]
    diagMoins = [reines[i]-i for i in range(nb)]
    if ligne+nb in diagPlus or ligne-nb in diagMoins:
        return True
    return False

tps1 = time.time()

n = 10
sols = [[]]
for c in range(1,n+1):
    newSols = []
    for solution in sols:
        for l in range(1,n+1):
            if not prenable(solution,l):
                newSol = solution.copy()
                newSol.append(l)
                newSols.append(newSol)
    sols = newSols
    #print(sols)
    
tps2 = time.time()
tmp2 = tps2 - tps1

print("time : ",tmp1)
print(len(sols)," solutions")
print(sols)