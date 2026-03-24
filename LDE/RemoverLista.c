#include<stdio.h>
#include<stdlib.h>

typedef struct No{
    int valor;
    struct No* proximo;
} No;

typedef struct Lista{
    No* inicio;
} Lista;

No* No_Criar(int valor){
    No* novo = (No*)malloc(sizeof(No));
    novo->valor = valor;
    novo->proximo = NULL;
    return novo;
}

Lista Lista_Criar(){
    Lista lista;
    lista.inicio = NULL;
    return lista;
}

void Lista_Remover(Lista* lista, int pos){
    if (pos == 0){
        No* temp = lista->inicio;
        lista->inicio = lista->inicio->proximo;
        free(temp);
        return;
    }
    No* atual = lista->inicio;
    for (int i = 0; i < pos - 1; i++){
        if (atual == NULL){
            break;
        }
        atual = atual->proximo;
    } 
    if (atual == NULL){
        return;
    }
    No* temp = atual->proximo;
    atual->proximo = atual->proximo->proximo;
    free(temp);
    return;
}

void Lista_Inserir_Cauda(Lista* lista, int valor){
    No* novo = No_Criar(valor);
    if (lista->inicio == NULL){
        lista->inicio = novo;
    } else {
        No* atual = lista->inicio;
        while(atual->proximo != NULL){
            atual = atual->proximo;
        }
        atual->proximo = novo;
    }
    return;
}

void Lista_Inserir_Cabeca(Lista* lista, int valor){
    No* novo = No_Criar(valor);
    novo->proximo = lista->inicio;
    lista->inicio = novo;
    return;
}

void Lista_Imprimir(Lista* lista){
    No* atual = lista->inicio;
    while(atual != NULL){
        printf("%d", atual->valor);
        if (atual->proximo != NULL){
            printf(" ");
        }
        atual = atual->proximo;
    }
    printf("\n");
}

int main() {
    int q = 0;
    scanf("%d", &q);
    for (int i = 0; i < q; i++){
        int n = 0;
        scanf("%d", &n);
        if (n <= 0){
            continue;
        }
        Lista lista = Lista_Criar();
        for (int j = 0; j < n; j++){
            int valor = 0;
            scanf("%d", &valor);
            Lista_Inserir_Cauda(&lista, valor);
        }
        int pos = 0;
        scanf("%d", &pos);
        Lista_Remover(&lista, pos);
        Lista_Imprimir(&lista);
        while (lista.inicio != NULL){
            No* temp = lista.inicio;
            lista.inicio = lista.inicio->proximo;
            free(temp);
        }
    }
    return 0;
}