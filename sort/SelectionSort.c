#include<stdio.h>

void selectionSort(int* vetor, int n){
    for(int i = 0; i < n; i++){
        int menor = vetor[i];
        int menor_indice = i;

        for(int j = i + 1; j < n; j++){
            if(vetor[j] < menor){
                menor = vetor[j];
                menor_indice = j;
            }
        }

        vetor[menor_indice] = vetor[i];
        vetor[i] = menor;
    }
}

void print_vetor(int* vetor, int n){
    for(int i = 0; i < n-1; i++){
        printf("%d ", vetor[i]);
    }
    printf("%d\n", vetor[n-1]);
    return;
}

int main() {
    while(1){
        int n = 0;
        scanf("%d", &n);
        if(n == 0){
            break;
        }

        int vetor[n];
        for(int i = 0; i < n; i++){
            scanf("%d", vetor+i);
        }
        selectionSort(vetor, n);
        print_vetor(vetor, n);
    }
    return 0;
}