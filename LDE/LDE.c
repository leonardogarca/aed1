#include<stdio.h>
#include<stdlib.h>

typedef struct No {
    int valor;
    struct No* proximo;
} No;

typedef struct {
    No* inicio;
    int quantidade;
} Lista;

Lista Lista_Criar() {
    Lista lista;
    lista.inicio = NULL;
    lista.quantidade = 0;
    return lista;
}

No* No_Criar(int valor) {
    No* no = (No*) malloc(sizeof(No));
    no->valor = valor;
    no->proximo = NULL;
    return no;
}

void Lista_Inserir(Lista *lista, int valor) {
    if (lista->quantidade == 0) {
        lista->inicio = No_Criar(valor);
        lista->quantidade++;
        return;
    }
    No* atual = lista->inicio;
    No* anterior = NULL;
    while (atual != NULL && atual->valor < valor) {
        anterior = atual;
        atual = atual->proximo;
    }
    if (atual != NULL && atual->valor == valor) {
        return;
    }
    No* novo = No_Criar(valor);
    if (anterior == NULL) {
        novo->proximo = lista->inicio;
        lista->inicio = novo;
    } else {
        anterior->proximo = novo;
        novo->proximo = atual;
    }
    lista->quantidade++;
    return;
}

void Lista_Remover(Lista *lista, int valor) {
    if (lista->quantidade == 0) {
        return;
    }
    No* atual = lista->inicio;
    No* anterior = NULL;
    while (atual != NULL && atual->valor != valor) {
        anterior = atual;
        atual = atual->proximo;
    }
    if (atual == NULL) {
        return;
    }
    if (anterior == NULL) {
        lista->inicio = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }
    free(atual);
    lista->quantidade--;
    return;
}

void Lista_Mostrar(Lista *lista) {
    if (lista->quantidade == 0 || lista->inicio == NULL) {
        return;
    }
    
    No* atual = lista->inicio;
    while (atual != NULL) {
        printf("%d", atual->valor);
        if (atual->proximo != NULL) {
            printf(" ");
        }
        atual = atual->proximo;
    }
    printf("\n");
}

void Lista_Buscar(Lista *lista, int valor) {
    No* atual = lista->inicio;
    while (atual != NULL && atual->valor != valor) {
        atual = atual->proximo;
    }
    if (atual == NULL) {
        printf("NAO\n");
    } else {
        printf("SIM\n");
    }
    return;
}

int main() {
    Lista lista = Lista_Criar();

    while(1){
        char comando;
        int valor;
        if(scanf(" %c", &comando) == EOF) {
            break;
        }

        if(comando == 'I'){
            scanf("%d", &valor);
            Lista_Inserir(&lista, valor);
        } else if (comando == 'R'){
            scanf("%d", &valor);
            Lista_Remover(&lista, valor);
        } else if (comando == 'L'){
            Lista_Mostrar(&lista);
        } else if (comando == 'B'){
            scanf("%d", &valor);
            Lista_Buscar(&lista, valor);
        }
    }

    while (lista.inicio != NULL) {
        No* atual = lista.inicio;
        lista.inicio = lista.inicio->proximo;
        free(atual);
    }
    return 0;
}