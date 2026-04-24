#include<stdio.h>
#include<stdlib.h>

typedef struct item{
    int dado;
    struct item* proximo;
} Item;

typedef struct lista{
    Item* inicio;
} Lista;

Lista criarLista(){
    Lista lista;
    lista.inicio = NULL;
    return lista;
}


Item* criarItem(int dado){
    Item* novoItem = (Item*)malloc(sizeof(Item));
    novoItem->dado = dado;
    novoItem->proximo = NULL;
    return novoItem;
}

void inserirItem(Lista* lista, int dado){
    Item* novoItem = criarItem(dado);
    if (lista->inicio == NULL){
        lista->inicio = novoItem;
        return;
    }
    Item* atual = lista->inicio;
    Item* anterior = NULL;
    while (atual != NULL && atual->dado > dado){
        anterior = atual;
        atual = atual->proximo;
    }
    if (atual != NULL && atual->dado == dado){
        free(novoItem);
        return;
    }

    if (anterior == NULL){
        novoItem->proximo = lista->inicio;
       lista->inicio = novoItem;
    } else {
        anterior->proximo = novoItem;
        novoItem->proximo = atual;
    }
}

void printLista(Lista* lista){
    Item* atual = lista->inicio;
    while (atual != NULL){
        printf("%d\n", atual->dado);
        atual = atual->proximo;
    }
    return;
}

typedef struct No{
    int dado;
    struct No* esquerdo;
    struct No* direito;
    struct No* pai;
} No;

typedef struct Arvore{
    No* raiz;
    int quantidade;
} Arvore;

Arvore criarArvore(){
    Arvore arvore;
    arvore.raiz = NULL;
    arvore.quantidade = 0;
    return arvore;
}

No* criarNo(int dado){
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->dado = dado;
    novoNo->pai = NULL;
    novoNo->esquerdo = NULL;
    novoNo->direito = NULL;
    return novoNo;
}

void inserirValor(Arvore* arvore, int valor){
    No* novo = criarNo(valor);
    No* pai = NULL;
    No* atual = arvore->raiz;
    
    while(atual != NULL){
        pai = atual;
        if (valor < atual->dado){
            atual = atual->esquerdo;
        } else if(valor > atual->dado) {
            atual = atual->direito;
        } else {
            free(novo);
            return;
        }
    }

    if (pai != NULL){
        if (valor < pai->dado){
            pai->esquerdo = novo;
        } else {
            pai->direito = novo;
        }
        novo->pai = pai;
    } else {
        arvore->raiz = novo;
    }
    arvore->quantidade++;
}

void freeArvore(No* no){
    if (no != NULL){
        freeArvore(no->esquerdo);
        freeArvore(no->direito);
        free(no);
    }
}


void mostrarNivel(No* no, int nivel, int nivel_atual, Lista* lista){
    if (no == NULL){
        return;
    }
    if (nivel_atual == nivel){
        inserirItem(lista, no->dado);
        return;
    }
    mostrarNivel(no->esquerdo, nivel, nivel_atual + 1, lista);
    mostrarNivel(no->direito, nivel, nivel_atual + 1, lista);
    return;
}

int main(){
    int n;
    int valor;
    Arvore arvore = criarArvore();
    
    while (1){
        scanf("%d", &valor);
        if (valor < 0){
            break;
        }
        inserirValor(&arvore, valor);
    }

    while (scanf("%d", &valor) != EOF){
        Lista lista = criarLista();
        mostrarNivel(arvore.raiz, valor, 0, &lista);
        printLista(&lista);
        Item* atual = lista.inicio;
        while (atual != NULL){
            Item* proximo = atual->proximo;
            free(atual);
            atual = proximo;
        }
    }

    if (arvore.raiz != NULL){
        freeArvore(arvore.raiz);
    }
    return 0;
}
