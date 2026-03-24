#include<stdio.h>
#include<stdlib.h>

typedef struct No{
    int valor;
    struct No* proximo;
} No;

typedef struct Lista{
    No* inicio;
    No* fim;
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
    lista.fim = NULL;
    return lista;
}

void Lista_Inserir_Cauda(Lista* lista, int valor){
    No* novo = No_Criar(valor);
    if (lista->inicio == NULL){
        lista->inicio = novo;
        lista->fim = novo;
    } else {
        lista->fim->proximo = novo;
        lista->fim = novo;
    }
    return;
}

void Lista_Remover_Cabeca(Lista* lista){
    if (lista->inicio == NULL){
        return;
    }
    No* temp = lista->inicio;
    printf("<%d>\n", temp->valor);
    lista->inicio = lista->inicio->proximo;
    free(temp);
    if (lista->inicio == NULL){
        lista->fim = NULL;
    }
    return;
}

void Lista_Imprimir(Lista* lista){
    No* atual = lista->inicio;
    while(atual != NULL){
        printf("%d", atual->valor);
        if (atual->proximo != NULL){
            printf(" ");
        } else {
            printf("\n");
        }
        atual = atual->proximo;
    }
}

int main() {
    Lista lista = Lista_Criar();
    while (1){
        char comando;
        if(scanf(" %c", &comando) == EOF){
            break;
        }

        if (comando == 'E'){
            int valor;
            scanf("%d", &valor);
            Lista_Inserir_Cauda(&lista, valor);
        } else if (comando == 'D'){
            Lista_Remover_Cabeca(&lista);
        } else if (comando == 'M'){
            Lista_Imprimir(&lista);
        }
    }

    No* atual = lista.inicio;
    while (atual != NULL){
        No* temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    return 0;
}