#include<stdio.h>
#include<stdlib.h>

#define TIPO float
#define FORMATO_L " %f"
#define FORMATO_E "%.2f"

typedef struct {
    TIPO* vetor;
    int tamanho;
    int inicio;
    int fim;
} Fila;

Fila Fila_Criar(int tamanho){
    Fila fila;
    fila.tamanho = tamanho;
    fila.vetor = (TIPO*) malloc(tamanho * sizeof(TIPO));
    fila.inicio = 0;
    fila.fim = 0;
    return fila;
}

void Fila_Enfileirar(Fila *fila, TIPO valor){
    if (((fila->fim + 1) % fila->tamanho) == fila->inicio){
        return;
    }

    fila->vetor[fila->fim] = valor;
    fila->fim = (fila->fim + 1) % fila->tamanho;
    return;
}

void Fila_Desinfileirar(Fila *fila){
    if (fila->inicio == fila->fim){
        return;
    }

    printf(FORMATO_E "\n", fila->vetor[fila->inicio]);
    fila->inicio = (fila->inicio + 1) % fila->tamanho;
    return;
}

int main() {
    int n = 0;
    scanf("%d", &n);

    Fila fila = Fila_Criar(n);

    while(1){
        char comando;
        TIPO valor;
        if(scanf(" %c", &comando) == EOF) {
            break;
        }

        if(comando == 'E'){
            scanf(FORMATO_L, &valor);
            Fila_Enfileirar(&fila, valor);
        } else if (comando == 'D'){
            Fila_Desinfileirar(&fila);
        }
    }

    free(fila.vetor);
    return 0;
}