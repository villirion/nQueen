#include <stdio.h>
#include <stdlib.h>

int diag(int reines[], int nb)
{
    int diagPlus[nb];
    int i;
    int j;
    for (i = 0; i<nb; i++){
            diagPlus[i] = reines[i]+i;
    }
    int diagMoins[nb];
    for (i = 0; i<nb; i++){
            diagMoins[i] = reines[i]-i;
    }
    for (i = 0; i < nb; i++) {
        for (j = i + 1; j < nb; j++) {
            if (diagMoins[j] == diagMoins[i]) {
            return 0;
            }
            if (diagPlus[j] == diagPlus[i]) {
            return 0;
            }
        }
    }
    return 1;

}

void swapVal(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}


void showPerm(int *perm, const int n)
{
    int i;
    for (i = 0; i < n; i++)
        printf("%d%c", perm[i], i == n - 1 ? '\n' : ' ');
}


void initPerm(int *perm, const int n)
{
    int i;
    for (i = 0; i < n; i++){
        perm[i] = i+1;
    }
}

int nextNoConsPerm(int *perm, const int n){
    if (n<4){
        return 0;
    }
    int OK=1;
    int i, j, k;
    do {
        i = n-1;
        while ( (i >0 ) && (perm[i - 1] > perm[i])){
            i--;
        }
        j = i;
        k = n-1;
        while (j < k){
            swapVal(&perm[j],&perm[k]);
            j++;
            k--;
        }
        if (i == 0){
            return 0;
        }else{
            j = i;
            while (perm[j] < perm[i - 1]) {
                j++;
            }
            swapVal(&perm[i - 1],&perm[j]);
            OK=0;
            for (i = 0; i < n-1; i++){
                if ((perm[i] == perm[i+1]+1)||(perm[i] == perm[i+1]-1)){
                    OK=1;
                    break;
                }
            }
        }
    } while (OK==1);
    return 1;

}


int main(int argc, const char * argv[])
{
	int n=12;
    long long indice=0;
    int perm[n];
    initPerm((int *)perm,n);
    while (nextNoConsPerm(perm,n)==1){
        if (diag(perm, n)==1){
            showPerm((int *)perm,n);
            indice++;
        }
    }
    printf("nb de solution = %ld",indice);
    return 0;
}
