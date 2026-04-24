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

void removerValor(Arvore* arvore, int valor){
    No* atual = arvore->raiz;
    while(atual != NULL && atual->dado != valor){
        if (valor < atual->dado){
            atual = atual->esquerdo;
        } else {
            atual = atual->direito;
        }
    }

    if (atual == NULL){
        return;
    }

    if (atual->esquerdo != NULL && atual->direito != NULL){
        No* antecesso = atual->esquerdo;
        while(antecesso->direito != NULL){
            antecesso = antecesso->direito;
        }
        atual->dado = antecesso->dado;
        atual = antecesso;
    }

    No* filho = (atual->esquerdo != NULL) ? atual->esquerdo : atual->direito;
    if (filho != NULL){
        filho->pai = atual->pai;
    }

    if (atual->pai == NULL){
        arvore->raiz = filho;
    } else if (atual == atual->pai->esquerdo){
        atual->pai->esquerdo = filho;
    } else {
        atual->pai->direito = filho;
    }

    free(atual);
    arvore->quantidade--;
    return;
}

void freeArvore(No* no){
    if (no != NULL){
        freeArvore(no->esquerdo);
        freeArvore(no->direito);
        free(no);
    }
}

void preOrder(No* no){
    if (no != NULL){
        printf("%d\n", no->dado);
        preOrder(no->esquerdo);
        preOrder(no->direito);
    }
}

void maxArvore(Arvore* arvore){
    if (arvore->raiz == NULL){
        return;
    }
    No* atual = arvore->raiz;
    while (atual->direito != NULL){
        atual = atual->direito;
    }
    printf("%d\n", atual->dado);
    return;

}

int main(){
    int n;
    int valor;
    Arvore arvore = criarArvore();
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++){
        scanf("%d", &valor);
        inserirValor(&arvore, valor);
    }

    maxArvore(&arvore);

    if (arvore.raiz != NULL){
        freeArvore(arvore.raiz);
    }
    return 0;
}
