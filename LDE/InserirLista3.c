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

void Lista_Inserir(Lista* lista, int valor, int pos){
    No* novo = No_Criar(valor);
    if (pos == 0){
        novo->proximo = lista->inicio;
        lista->inicio = novo;
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
        free(novo);
        return;
    }
    novo->proximo = atual->proximo;
    atual->proximo = novo;
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
    int n = 0;
    scanf("%d", &n);
    Lista lista = Lista_Criar();
    for (int i = 0; i < n; i++){
        int pos = 0;
        int valor = 0;
        scanf("%d %d", &valor, &pos);
        Lista_Inserir(&lista, valor, pos);
    }
    Lista_Imprimir(&lista);
    while (lista.inicio != NULL){
        No* temp = lista.inicio;
        lista.inicio = lista.inicio->proximo;
        free(temp);
    }
    return 0;
}
