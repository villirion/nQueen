def diag(reines):
    nb = len(reines)
    diagPlus = [reines[i]+i for i in range(nb)]
    diagMoins = [reines[i]-i for i in range(nb)]
    if len(set(diagPlus)) == nb and len(set(diagMoins)) == nb:
        return True
    return False

noDouble=[]

for n in range(4,52):
    if n%2==0:
        exception = n-2
        if exception%6==0:
            ligne1 = list(range(2, n+1, 2))  
            ligne2 = list(range(1, n, 2))
            ligne2 = [ligne2[1]]+[ligne2[0]]+ligne2[3:]+[ligne2[2]]
            reines = ligne1 + ligne2
             
        else:

            reines = list(range(2, n+1, 2)) + list(range(1, n, 2))
    else:
        exception = n-3
        if exception%6==0:
            ligne1 =  list(range(1, n-2, 2))
            ligne2 =  list(range(2, n-1, 2))

            reines = [n-2]+[n]+ligne1 +[n-1] + ligne2    
        else:
            reines = list(range(1, n+1, 2)) + list(range(2, n, 2))
    print(n,reines, diag(reines))
    if diag(reines) == False:
        noDouble+=[n]
