#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>
//#include "omp.h"



int prenable(short int *reines,short int ligne,short int nb)
{

    {
        short int i;
        //int j;
        for (i = 0; i<nb; i++){
            if (ligne == reines[i]){
                return 0;
            }
        }
        short int diagPlus[nb];
        short int diagMoins[nb];
        //#pragma omp simd
        for (i = 0; i<nb; i++){
            diagPlus[i] = reines[i]+i;
            diagMoins[i] = reines[i]-i;
        }
        short int lignePlus  = ligne+nb;
        short int ligneMoins = ligne-nb;
        for (i = 0; i < nb; i++) {
            if ( lignePlus == diagPlus[i]) {
                return 0;
            }
            if ( ligneMoins == diagMoins[i]) {
                return 0;
            }
        }

        return 1;
    }
}

void freeTab (short int ** tab, long long maxSize){
    long k;
    for (k=0;k<maxSize;k++){
        free( tab[k] );
    }
    free(tab);
}


void affectation (short int *tab,short int *tab2,short int n){
    short int i;
    for (i=0;i<n;i++){
        tab[i]=tab2[i];
    }
}


void afficheTab (short int **tab, long long maxSize, short int n){
    long k;
    short int i;
    for (k=0;k<maxSize;k++){
            //printf("pos %ld \n",k);
            for (i=0;i<n;i++){
                printf("%d ",tab[k][i]);
            }
            printf("\n");
    }

}



void showtab(short int *tab, const int n)
{
    int i;
    for (i = 0; i < n; i++)
        printf("%d%c", tab[i], i == n - 1 ? '\n' : ' ');
}



void swaptab (short int ** a, short int ** b) {
short int * c = *a;

*a = *b;
*b = c;
}


int main(int argc, const char * argv[]) {

    short int n = 10;
    short int i;
    short int k;
    long long j;
    long long maxSize;
    //short int solution[n];
    maxSize=1;
    for (i = n; i > (short int)(n/2)+1; i--){
        /*
        taille du tableau de travaille supérieure au nombre de solution
        factorial(n)/((factorial(n/2)+1)
         */
        maxSize*=i;
    }
    printf("%lld\n", maxSize);
    short int **sols;
    sols = malloc( n*maxSize*sizeof *sols);
    if(sols == NULL) {         //Pas de libération de mémoire à ce niveau
        printf("sols");
        return -1;            //Exemple de code d'erreur
    }
    short int **newSols;
    newSols = malloc( n*maxSize*sizeof *newSols);
    if(newSols == NULL) {
        printf("newSols");
        return -1;
    }



    for (k=0;k<n;k++){
        sols[k] = calloc(n, n * sizeof(**sols));
        if(sols[k] == NULL) {
            printf("sols[%d]",k);
            return -1;
        }
        sols[k][0]=k+1;

    }
    long long nbSol = n;
    //afficheTab(sols,nbSol,n);

    long long nbnewSols = 0;
    for (i=1;i<n;i++){
        newSols = malloc( n*maxSize*sizeof *newSols);
        if(newSols == NULL) {
            printf("newSols");
            return -1;
        }
        for (j=0;j<nbSol;j++){
            for (k=1;k<n+1;k++){
                //showtab(sols[j], n);
                if (prenable(sols[j],k,i)==1){
                    //printf("%ld\n", k);
                    newSols[nbnewSols] = calloc(n, n * sizeof(**newSols));
                    if(newSols[nbnewSols] == NULL) {
                        printf("newSols[%lld]",nbnewSols);
                        return -1;
                    }
                    //newSols[nbnewSols]=sols[j];
                    affectation(newSols[nbnewSols],sols[j],n);
                    newSols[nbnewSols][i]=k;
                    //showtab(newSols[nbnewSols], n);
                    nbnewSols++;
                }
            }
        }
        //afficheTab(newSols,nbnewSols,n);
        //printf("%ld\n",nbnewSols);
        swaptab((short int **)&newSols,(short int **)&sols);
        freeTab(newSols,nbSol);

        nbSol = nbnewSols;
        nbnewSols = 0;

        //afficheTab(sols,nbSol,n);
    }

    //afficheTab(sols,nbSol,n);
    printf("%lld\n",nbSol);
    freeTab(sols,nbSol);

}
