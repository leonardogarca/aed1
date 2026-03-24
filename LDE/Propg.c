#include<stdio.h>
#include<stdlib.h>

typedef struct No{
    char* valor;
    struct No* proximo;
} No;

typedef struct Fila{
    No* inicio;
    No* fim;
} Fila;

No* No_Criar(char* valor){
    No* novo = (No*)malloc(sizeof(No));
    novo->valor = valor;
    novo->proximo = NULL;
    return novo;
}

Fila criarFila(){
    Fila nova;
    nova.inicio = NULL;
    nova.fim = NULL;
    return nova;
}

void enfileirar(Fila* fila, char* valor){
    No* novo = No_Criar(valor);
    if (fila->inicio == NULL){
        fila->inicio = novo;
        fila->fim = novo;
    } else {
        fila->fim->proximo = novo;
        fila->fim = novo;
    }
}

No* desenfileirar(Fila* fila){
    if (fila->inicio == NULL){
        return NULL;
    }
    No* temp = fila->inicio;
    fila->inicio = fila->inicio->proximo;
    if (fila->inicio == NULL){
        fila->fim = NULL;
    }
    return temp;
}

void mostrarFila(Fila* fila){
    No* atual = fila->inicio;
    while(atual != NULL){
        printf("%s", atual->valor);
        if (atual->proximo != NULL){
            printf(" ");
        } else {
            printf("\n");
        }
        atual = atual->proximo;
    }
}

No* primeiro(Fila* fila){
    return fila->inicio;
}

No* ultimo(Fila* fila){
    return fila->fim;
}

int filaVazia(Fila* fila){
    return fila->inicio == NULL;
}

No* desempilhar(Fila* fila){
    if (fila->inicio == NULL){
        return NULL;
    }
    if (fila->inicio == fila->fim) {
        No* temp = fila->inicio;
        fila->inicio = NULL;
        fila->fim = NULL;
        return temp;
    }

    No* temp = fila->fim;
    No* atual = fila->inicio;
    while(atual->proximo != temp){
        atual = atual->proximo;
    }
    atual->proximo = NULL;
    fila->fim = atual;
    return temp;
}

void mostrarFilaReversa(Fila* fila, No* no){
    if (no == NULL){
        return;
    }
    mostrarFilaReversa(fila, no->proximo);
    printf("%s", no->valor);
    if (no == primeiro(fila)){
        printf("\n");
    } else {
        printf(" ");
    }
}

int main() {
    Fila fila = criarFila();

    while(1){
        char comando;
        if (scanf(" %c", &comando) == EOF){
            break;
        }

        if (comando == 'E'){
            char* valor = (char*)malloc(50 * sizeof(char));
            scanf("%s", valor);
            enfileirar(&fila, valor);
        } else if (comando == 'D'){
            No* removido = desempilhar(&fila);
            if (removido != NULL){
                printf("[%s]\n", removido->valor);
                free(removido->valor);
                free(removido);
            }
        } else if (comando == 'T'){
            No* p = ultimo(&fila);
            if (p != NULL){
                printf("(%s)\n", p->valor);
            }
        } else if (comando == 'X'){
            mostrarFilaReversa(&fila, fila.inicio);
        } else if (comando == 'B'){
            mostrarFila(&fila);
        }
    }
    No* atual = fila.inicio;
    while(atual != NULL){
        No* temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    return 0;
}
