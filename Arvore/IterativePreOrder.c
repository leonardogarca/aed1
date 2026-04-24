#include<stdio.h>
#include<stdlib.h>


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
        } else {
            atual = atual->direito;
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

void preOrderIterativo(Arvore* arvore){
    if (arvore->raiz == NULL){
        return;
    }

    No* pilha[arvore->quantidade];
    int topo = -1;
    pilha[++topo] = arvore->raiz;

    while (topo >= 0){
        No* atual = pilha[topo--];
        printf("%d\n", atual->dado);
        if (atual->direito != NULL){
            pilha[++topo] = atual->direito;
        }
        if (atual->esquerdo != NULL){
            pilha[++topo] = atual->esquerdo;
        }
    }
    return;
}



int main(){
    int n;
    int valor;
    Arvore arvore = criarArvore();
    
    while (scanf("%d", &valor) !=  EOF){

        inserirValor(&arvore, valor);
    }

    preOrderIterativo(&arvore);

    if (arvore.raiz != NULL){
        freeArvore(arvore.raiz);
    }
    return 0;
}
