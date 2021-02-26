from numba import cuda
import numpy as np
import numba as nb
import time

cuda.select_device(0)

@cuda.jit(device=True)
def prenable(reines, ligne, nb):
    for i in range(nb):  
        if ligne == reines[i]:
            return True
        if (ligne+nb) == (reines[i]+i):
            return True
        if (ligne-nb) == (reines[i]-i):
            return True
    return False
  
@cuda.jit
def test_newposition(sols, newSols,col):
    solution = cuda.shared.array(shape=n,dtype=np.int8)
    posNewSols = cuda.blockIdx.x * sols.shape[1] + cuda.threadIdx.x
    ligne   = np.int8(cuda.threadIdx.x)+1
    colonne = np.int8(col)
    for i in range(sols.shape[1]):
        solution[i] = sols[cuda.blockIdx.x,i]
    if not prenable(solution,ligne,colonne):
        for i in range(newSols.shape[1]):
            newSols[posNewSols,i] = solution[i]
        newSols[posNewSols,colonne]= ligne
        
tps1 = time.time()

n = 14 ## max avec 32 Go de mémoire

solutions = np.array(np.zeros(shape=(n,n)),np.int8)
for i in range(n):
    solutions[i][0]=i+1
newsolutions =np.array(np.zeros(shape=(n*n,n)),np.int8)
    
nbsols=n
nbThread=n

for i in range(n-1):
    nbBlock=nbsols
    d_dep = cuda.to_device(solutions)
    d_arr = cuda.to_device(newsolutions)
    test_newposition[nbBlock, nbThread](d_dep,d_arr,i+1)
    solutions = d_arr.copy_to_host()
    solutions= np.delete(solutions,np.where(~solutions.any(axis=1))[0], axis=0)
    nbsols = len(solutions)
    newsolutions =np.array(np.zeros(shape=(nbsols*n,n)),np.int8)

tps2 = time.time()
tmp1 = tps2 - tps1

print("time : ",tmp1)    
    
print(solutions)

print(len(solutions))
