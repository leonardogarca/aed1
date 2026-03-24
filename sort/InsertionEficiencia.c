#include<stdio.h>

void insertionSort(int vetor[], int n, int *trocas) {
    for (int i = 1; i < n; i++) {
        int key = vetor[i];
        int j = i - 1;
        while (j >= 0 && vetor[j] > key) {
            vetor[j + 1] = vetor[j];
            j--;
            (*trocas)++;
        }
        vetor[j + 1] = key;
    }
}

int main() {
    int n = 0;
    scanf("%d", &n);
    int vetor[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &vetor[i]);
    }
    int trocas = 0;
    insertionSort(vetor, n, &trocas);
    printf("%d\n", trocas);
    return 0;
}