#include<stdio.h>

void printVetor(int vetor[], int begin, int end){
    for(int i = begin; i < end; i++){
        printf("%d ", vetor[i]);
    }
    printf("%d\n", vetor[end]);
}

void insertionSort(int vetor[], int n){
    for(int i = 1; i < n; i++){
        printf("Sublista Ordenada: ");
        printVetor(vetor, 0, i - 1);
        printf("Sublista Desordenada: ");
        printVetor(vetor, i, n - 1);
        int key = vetor[i];
        int j = i - 1;
        while(j >= 0 && vetor[j] > key){
            vetor[j + 1] = vetor[j];
            j--;
        }
        vetor[j + 1] = key;
    }
}

int main() {
    int n;
    scanf("%d", &n);
    int vetor[n];
    for(int i = 0; i < n; i++){
        scanf("%d", &vetor[i]);
    }
    insertionSort(vetor, n);
    printf("Sublista Ordenada: ");
    printVetor(vetor, 0, n - 1);
    printf("Sublista Desordenada:\n");
    return 0;
}