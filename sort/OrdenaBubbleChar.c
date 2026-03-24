#include<stdio.h>

void printVetor(char vetor[], int n){
    for(int i = 0; i < n - 1; i++){
        printf("%c ", vetor[i]);
    }
    printf("%c\n", vetor[n - 1]);
}

void bubbleSort(char vetor[], int n, int *trocas){
    for(int i = 0; i < n - 1; i++){
        for(int j = 0; j < n - i - 1; j++){
            if(vetor[j] > vetor[j + 1]){
                char temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
                (*trocas) += 1;
                printVetor(vetor, n);
            }
        }
    }
}

int main(){
    int n = 0;
    scanf("%d", &n);
    char vetor[n];
    for(int i = 0; i < n; i++){
        scanf(" %c", &vetor[i]);
    }
    int trocas = 0;
    printVetor(vetor, n);
    bubbleSort(vetor, n, &trocas);
    printVetor(vetor, n);
    printf("Trocas: %d\n", trocas);
    return 0;

}