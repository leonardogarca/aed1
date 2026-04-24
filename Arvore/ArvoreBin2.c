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
        No* sucessor = atual->direito;
        while(sucessor->esquerdo != NULL){
            sucessor = sucessor->esquerdo;
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

void preOrder(No* no, int* primeiro){
    if(no != NULL){
        if(!(*primeiro)) {
            printf(" "); // Imprime espaço ANTES se não for o primeiro
        }
        printf("%d", no->dado);
        *primeiro = 0; // Desliga a flag: nenhum outro será o primeiro
        
        preOrder(no->esquerdo, primeiro);
        preOrder(no->direito, primeiro);
    }
}

void inOrder(No* no, int* primeiro){
    if(no != NULL){
        inOrder(no->esquerdo, primeiro);
        
        if(!(*primeiro)) {
            printf(" ");
        }
        printf("%d", no->dado);
        *primeiro = 0;
        
        inOrder(no->direito, primeiro);
    }
}

void postOrder(No* no, int* primeiro){
    if(no != NULL){
        postOrder(no->esquerdo, primeiro);
        postOrder(no->direito, primeiro);
        
        if(!(*primeiro)) {
            printf(" ");
        }
        printf("%d", no->dado);
        *primeiro = 0;
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
            if(arvore.raiz != NULL){
                int primeiro = 1;
                preOrder(arvore.raiz, &primeiro);
                printf("\n");
            }
        }
        else if(strcmp(comando, "in-order") == 0){
            if(arvore.raiz != NULL){
                int primeiro = 1;
                inOrder(arvore.raiz, &primeiro);
                printf("\n");
            }
        }
        else if(strcmp(comando, "post-order") == 0){
            if(arvore.raiz != NULL){
                int primeiro = 1;
                postOrder(arvore.raiz, &primeiro);
                printf("\n");
            }
        }
    }
    return 0;
}