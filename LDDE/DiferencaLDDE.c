#include<stdio.h>
#include<stdlib.h>

typedef struct No{
    int valor;
    struct No* proximo;
    struct No* anterior;
} No;

typedef struct Lista{
    No* inicio;
    No* fim;
} Lista;

No* criarNo(int valor){
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->valor = valor;
    novoNo->proximo = NULL;
    novoNo->anterior = NULL;
    return novoNo;
}

Lista criarLista(){
    Lista lista;
    lista.inicio = NULL;
    lista.fim = NULL;
    return lista;
}

void listaInserir(Lista* lista, int valor){
    No* novoNo = criarNo(valor);
    if(lista->inicio == NULL){
        lista->inicio = novoNo;
        lista->fim = novoNo;
        return;
    }
    No* atual = lista->inicio;
    while(atual != NULL && atual->valor < valor){
        atual = atual->proximo;
    }
    
    if(atual != NULL && atual->valor == valor){
        free(novoNo);
        return;
    }

    if(atual == NULL){
        lista->fim->proximo = novoNo;
        novoNo->anterior = lista->fim;
        lista->fim = novoNo;
    } else if(atual == lista->inicio){
        novoNo->proximo = lista->inicio;
        lista->inicio->anterior = novoNo;
        lista->inicio = novoNo;
    } else {
        novoNo->proximo = atual;
        novoNo->anterior = atual->anterior;
        novoNo->anterior->proximo = novoNo;
        atual->anterior = novoNo;
    }
    return;
}

void listaRemover(Lista* lista, int valor){
    No* atual = lista->inicio;
    while(atual != NULL && atual->valor != valor){
        atual = atual->proximo;
    }
    if(atual == NULL){
        return; // Valor não encontrado, nada a remover
    }
    if(atual == lista->inicio){
        lista->inicio = atual->proximo;
        if(lista->inicio != NULL){
            lista->inicio->anterior = NULL;
        } else {
            lista->fim = NULL; // Lista ficou vazia
        }
    } else if(atual == lista->fim){
        lista->fim = atual->anterior;
        lista->fim->proximo = NULL;
    } else {
        atual->anterior->proximo = atual->proximo;
        atual->proximo->anterior = atual->anterior;
    }
    free(atual);
    return;
}

void listaImprimir(Lista* lista){
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

void listaImprimirReversa(Lista* lista){
    No* atual = lista->fim;
    while(atual != NULL){
        printf("%d", atual->valor);
        if (atual->anterior != NULL){
            printf(" ");
        } else {
            printf("\n");
        }
        atual = atual->anterior;
    }
}

Lista listaDiferenca(Lista* a, Lista* b){
    Lista resultado = criarLista();
    No* atualA = a->inicio;
    No* atualB = b->inicio;
    
    while(atualA != NULL && atualB != NULL){
        if(atualA->valor < atualB->valor){
            listaInserir(&resultado, atualA->valor);
            atualA = atualA->proximo;
        } else if(atualA->valor > atualB->valor){
            atualB = atualB->proximo;
        } else {
            atualA = atualA->proximo;
            atualB = atualB->proximo;
        }
    }
    
    while(atualA != NULL){
        listaInserir(&resultado, atualA->valor);
        atualA = atualA->proximo;
    }
    
    return resultado;
}

void liberarLista(Lista* lista){
    No* atual = lista->inicio;
    while(atual != NULL){
        No* temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    lista->inicio = NULL;
    lista->fim = NULL;
}

int main(){
    Lista a = criarLista();
    Lista b = criarLista();
    char comando;
    char listaEscolhida;
    int valor;
    
    while(scanf(" %c %c", &comando, &listaEscolhida) != EOF){
        Lista* lista = (listaEscolhida == 'A') ? &a : &b;
        if(comando == 'I'){
            scanf("%d", &valor);
            listaInserir(lista, valor);
        } else if(comando == 'E'){
            scanf("%d", &valor);
            listaRemover(lista, valor);
        }
    }
    
    Lista resultado = listaDiferenca(&a, &b);
    listaImprimir(&resultado);
    listaImprimirReversa(&resultado);
    liberarLista(&resultado);
    resultado = listaDiferenca(&b, &a);
    listaImprimir(&resultado);
    listaImprimirReversa(&resultado);
    liberarLista(&resultado);
    liberarLista(&a);
    liberarLista(&b);

    return 0;
}