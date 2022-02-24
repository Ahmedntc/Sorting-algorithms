#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>



int *array;
int i;

void swap(int x[], int i, int j) {
    int aux = x[i];
    x[i] = x[j];
    x[j] = aux;
}

int * geraVetor(int N){
    srand(time(NULL));

    array = (int *) malloc(N*sizeof (int));
    for(i = 0; i < N; i++){
        array[i] = rand() % N + N;
    }
    printf("\nO vetor tem tamanho igual a %d", N);
    return 0;
    free(array);  
}
//bubble
void bubble_sort(int v[], int n) {
    int i, j;
    bool fez_swap;
    // j é a quantidade de passadas que vou fazer
    for (j = 0; j < n-1; j++) {
        fez_swap = false;
        for (i = 0; i < n-1-j; i++)
            if (v[i] > v[i+1]) {
                swap(v, i, i+1);
                fez_swap = true;
            }
        if (!fez_swap) break;
    }
}

//merge
void merge(int v[], int aux[], int ini, int meio, int fim) {
    int i, esq, dir;
    esq = ini, dir = meio+1;
    // copio sempre o menor entre o da esquerda e o da direita
    for (i = esq; esq <= meio && dir <= fim; i++) {
        if (v[esq] <= v[dir]) 
            aux[i] = v[esq++];
        else
            aux[i] = v[dir++];
    }
    while (dir <= fim)
        aux[i++] = v[dir++];
    while (esq <= meio)
        aux[i++] = v[esq++];

    for (i = ini; i <= fim; i++)
        v[i] = aux[i];
}

void mergesort(int v[], int aux[], int ini, int fim) {
    if (ini == fim)
        // só tem um elemento! já está ordenado
        return; 
    int meio = (ini+fim)/2;
    mergesort(v, aux, ini, meio);
    mergesort(v, aux, meio+1, fim);
    merge(v, aux, ini, meio, fim);
}

void ordena(int v[], int tamanho) {
    int * aux = malloc(tamanho*sizeof (int));
    mergesort(v, aux, 0, tamanho-1);
    free(aux);
}

void imprime(int v[], int tamanho) {
    int i;
    for (i = 0; i < tamanho; i++)
        printf("%d ", v[i]);
    printf("\n");
}

    int main(){
        clock_t t1, t2;
        clock_t t3, t4;
        double  deltaT ;
        int size = 10;
        int *v = malloc(sizeof(size));
        for(int i = 0; i < 10; i++ ){          
            v = geraVetor(size);
            //mede merge
            t1 = clock();
            ordena(array, size);
            t2 = clock();
            deltaT = ((double) (t2-t1)/CLOCKS_PER_SEC);// calculo da diferença do  tempo de execuçao 
            printf("\nO algoritmo de merge demorou %f segundos para ordenar o vetor", deltaT);
            //mede bubble
            t3 = clock();
            bubble_sort(array, size);
            t4 = clock();
            deltaT = ((double) (t4-t3)/CLOCKS_PER_SEC);
            printf("\nO algoritmo de bubble demorou %f segundos para ordenar o vetor\n", deltaT);
            free(v); 

            if( i % 2  == 0)
            {
                size *= 2;
            }
            else
            {
                size *= 5;                
            }    
        }
        return 0;
    }