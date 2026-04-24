#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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
            printf("Chave %d ja existe na arvore!\n", valor);
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

void imediatamenteMaior(Arvore* arvore, int valor){
    No* atual = arvore->raiz;
    while (atual != NULL && atual->dado != valor){
        if (valor < atual->dado){
            atual = atual->esquerdo;
        } else {
            atual = atual->direito;
        }
    }
    if (atual == NULL) return;
    if (atual->direito != NULL){
        atual = atual->direito;
        while (atual->esquerdo != NULL){
            atual = atual->esquerdo;
        }
        printf("%d\n", atual->dado);
        return;
    }

    printf("nao ha imediatamente maior que %d\n", valor);
    
    return;
}

void imediatamenteMenor(Arvore* arvore, int valor){
    No* atual = arvore->raiz;

    while (atual != NULL && atual->dado != valor){
        if (valor < atual->dado){
            atual = atual->esquerdo;
        } else {
            atual = atual->direito;
        }
    }

    if (atual == NULL) return;

    if (atual->esquerdo != NULL){
        atual = atual->esquerdo;
        while (atual->direito != NULL){
            atual = atual->direito;
        }
        printf("%d\n", atual->dado);
        return;
    }

    printf("nao ha imediatamente menor que %d\n", valor);

    return;
}



int main(){
    Arvore arvore = criarArvore();
    int valor = 0;
    char comando[30];
    
    while(scanf("%s", comando) != EOF){
        if(strcmp(comando, "insert") == 0){
            scanf("%d", &valor);
            inserirValor(&arvore, valor);
        }
        else if(strcmp(comando, "immediately-greater") == 0){
            scanf("%d", &valor);
            imediatamenteMaior(&arvore, valor);
        }
        else if(strcmp(comando, "immediately-less") == 0){
            scanf("%d", &valor);
            imediatamenteMenor(&arvore, valor);
        }
    }
    return 0;
}
