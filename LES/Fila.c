#include<stdio.h>
#include<stdlib.h>

#define TIPO int
#define FORMATO_L " %d"
#define FORMATO_E "%d"

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
    fila.inicio = -1;
    fila.fim = -1;
    return fila;
}

void Fila_Enfileirar(Fila *fila, TIPO valor){
    if (fila->fim == fila->tamanho - 1){
        return;
    }

    if (fila->inicio == -1 && fila->fim == -1){
        fila->inicio++;
        fila->fim++;
        fila->vetor[fila->fim] = valor;
        return;
    }

    fila->fim++;
    fila->vetor[fila->fim] = valor;
    return;
}

void Fila_Desinfileirar(Fila *fila){
    if (fila->inicio == -1){
        return;
    }

    printf(FORMATO_E "\n", fila->vetor[fila->inicio]);
    if(fila->inicio == fila->fim){
        fila->inicio = -1;
        fila->fim = -1;
    } else {
        fila->inicio++;
    }
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