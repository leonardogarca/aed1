#include<stdio.h>

void print_vetor(int* vetor, int n){
    for(int i = 0; i < n-1; i++){
        printf("%d ", vetor[i]);
    }
    printf("%d\n", vetor[n-1]);
    return;
}

int main() {
    int n = 0;
    scanf("%d", &n);

    int vetor[n];
    for(int i = 0; i < n; i++){
        scanf("%d", vetor+i);
    }

    print_vetor(vetor, n);

    int trocas = 0;

    int chave, i, j;

    for(i=1; i<n; i++){
        chave = vetor[i];
        j = i-1;
        while(j >= 0 && vetor[j] >= chave) {
            vetor[j+1] = vetor[j];
            vetor[j] = chave;
            j--;
            trocas++;
            print_vetor(vetor, n);
        }
    }
    print_vetor(vetor, n);
    printf("Trocas:%d\n", trocas);

    if(trocas == 0){
        printf("MELHOR CASO\n");
    }
    else if(trocas == (((n*n) - n) / 2)){
        printf("PIOR CASO\n");
    }
    else {
        printf("CASO ALEATORIO\n");
    }

    return 0;
}