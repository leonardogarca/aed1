#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void printVetor(char *vetor[], int n){
    for(int i = 0; i < n-1; i++){
        printf("%s ", vetor[i]);
    }
    printf("%s\n", vetor[n-1]); 
}

void bubbleSort(char *vetor[], int n, int *trocas){
    for(int i = 0; i < n-1; i++){
        for(int j = 0; j < n-i-1; j++){
            if(strcmp(vetor[j], vetor[j+1]) > 0){
                char *temp = vetor[j];
                vetor[j] = vetor[j+1];
                vetor[j+1] = temp;
                (*trocas)++;
                printVetor(vetor, n);
            }
        }
    }
}

int main(){
    int n = 0;
    scanf("%d\n", &n);
    char *vetor[n];
    for(int i = 0; i < n; i++){
        vetor[i] = (char*)malloc(100 * sizeof(char));
        scanf("%s", vetor[i]);
    }
    int trocas = 0;
    printVetor(vetor, n);
    bubbleSort(vetor, n, &trocas);
    printVetor(vetor, n);
    printf("Trocas: %d\n", trocas);
    for(int i = 0; i < n; i++){
        free(vetor[i]);
    }
    return 0;
}