#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>

short int n = 15;
int tab[15];

int prenable(short int *reines,short int ligne,short int nb){
    short int i;
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
            for (i=0;i<n;i++){
                printf("%d ",tab[k][i]);
            }
            printf("\n");
    }

}


void showtab(short int *tab, const int n){
    int i;
    for (i = 0; i < n; i++)
        printf("%d%c", tab[i], i == n - 1 ? '\n' : ' ');
}


void swaptab (short int ** a, short int ** b) {
short int * c = *a;

*a = *b;
*b = c;
}


void *my_thread_process (void * arg) {
    short int numtrd = *((int *) arg);
    short int i;
    short int k;
    long long j;
    long long maxSize;
    maxSize=1;
    for (i = n; i > (short int)(n/2)+1; i--){
        maxSize*=i;
    }
    short int **sols;
    sols = malloc( maxSize*sizeof *sols);
    if(sols == NULL) {         //Pas de libération de mémoire à ce niveau
        printf("sols");
    }
    short int **newSols;
    newSols = malloc( maxSize*sizeof *newSols);
    if(newSols == NULL) {
        printf("newSols");
    }

    sols[0] = calloc(n, n * sizeof(**sols));
    sols[0][0] = numtrd;

    long long nbSol = 1;

    long long nbnewSols = 0;
    for (i=1;i<n;i++){
        newSols = malloc( maxSize*sizeof *newSols);
        if(newSols == NULL) {
            printf("newSols");
        }
        for (j=0;j<nbSol;j++){
            for (k=1;k<n+1;k++){
                if (prenable(sols[j],k,i)==1){
                    newSols[nbnewSols] = calloc(n, n * sizeof(**newSols));
                    if(newSols[nbnewSols] == NULL) {
                        printf("newSols[%lld]",nbnewSols);
                    }
                    affectation(newSols[nbnewSols],sols[j],n);
                    newSols[nbnewSols][i]=k;
                    nbnewSols++;
                }
            }
        }
        swaptab((short int **)&newSols,(short int **)&sols);
        freeTab(newSols,nbSol);

        nbSol = nbnewSols;
        nbnewSols = 0;
    }
    tab[numtrd-1] = nbSol;
    freeTab(sols,nbSol);
    pthread_exit (0);
}


int main(int argc, const char * argv[]) {
    srand( (unsigned int)time( NULL ) );
    short int nbthread=n;
    short int i;
    short int ints[nbthread];
    pthread_t thr[nbthread];
    void *ret;
    for (i=0;i <nbthread ;i ++){
        ints[i] = i+1;
        if (pthread_create (&thr[i], NULL, my_thread_process, &ints[i] ) < 0) {
            fprintf (stderr, "pthread_create error for thread %d\n", 1);
            exit (1);
        }
    }
    for  (i=0;i <nbthread ;i ++){
        (void)pthread_join (thr[i], &ret);
    }

    long int somme = 0;
    for  (i=0;i <nbthread ;i ++){
        somme += tab[i];
    }
    printf("%ld\n",somme);
}
