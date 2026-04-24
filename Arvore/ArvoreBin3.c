#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No{
    int dado;
    struct No* pai;
    struct No* esquerdo;
    struct No* direito;
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
    No* filho = arvore->raiz;
    
    while(filho != NULL){
        pai = filho;
        if(novo->dado >= filho->dado){ 
            filho = filho->direito;
        } else {
            filho = filho->esquerdo;
        }
    }
    
    if(pai != NULL){
        if(novo->dado >= pai->dado){
            pai->direito = novo;
        } else {
            pai->esquerdo = novo;
        }
        novo->pai = pai;
    } else {
        arvore->raiz = novo;
    }
    arvore->quantidade++;
}

void removerValor(Arvore* arvore, int valor){
    No* atual = arvore->raiz;
    
    while(atual != NULL && atual->dado != valor){
        if(valor < atual->dado){
            atual = atual->esquerdo;
        } else {
            atual = atual->direito; 
        }
    }

    if(atual == NULL) return; 

    if(atual->esquerdo != NULL && atual->direito != NULL){
        No* sucessor = atual->esquerdo;
        while(sucessor->direito != NULL){
            sucessor = sucessor->direito;
        }
        atual->dado = sucessor->dado;
        atual = sucessor; 
    }

    No* filho = (atual->esquerdo != NULL) ? atual->esquerdo : atual->direito;

    if(filho != NULL){
        filho->pai = atual->pai;
    }

    if(atual->pai == NULL){
        arvore->raiz = filho;
    } else if(atual == atual->pai->esquerdo){
        atual->pai->esquerdo = filho;
    } else {
        atual->pai->direito = filho;
    }

    printf("%d\n", valor);
    free(atual);
    arvore->quantidade--;
}

void preOrder(Arvore* arvore, No* no){
    if(no != NULL){
        printf("%d\n", no->dado);
        preOrder(arvore, no->esquerdo);
        preOrder(arvore, no->direito);
    }
}

void inOrder(Arvore* arvore, No* no){
    if(no != NULL){
        inOrder(arvore, no->esquerdo);
        printf("%d\n", no->dado);
        inOrder(arvore, no->direito);
    }
}

void postOrder(Arvore* arvore, No* no){
    if(no != NULL){
        postOrder(arvore, no->esquerdo);
        postOrder(arvore, no->direito);
        printf("%d\n", no->dado); 
    }
}

int main(){
    Arvore arvore = criarArvore();
    int valor = 0;
    char comando[20];
    
    while(scanf("%s", comando) != EOF){
        if(strcmp(comando, "insert") == 0){
            scanf("%d", &valor);
            inserirValor(&arvore, valor);
        }
        else if(strcmp(comando, "delete") == 0){
            scanf("%d", &valor);
            removerValor(&arvore, valor);
        }
        else if(strcmp(comando, "pre-order") == 0){
            preOrder(&arvore, arvore.raiz);
        }
        else if(strcmp(comando, "in-order") == 0){
            inOrder(&arvore, arvore.raiz);
        }
        else if(strcmp(comando, "post-order") == 0){
            postOrder(&arvore, arvore.raiz);
        }
    }
    return 0;
}